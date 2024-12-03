from datetime import timedelta

from django.contrib.auth import authenticate
from django.core.exceptions import ValidationError
from django.core.validators import validate_email
from django.db.models.functions import datetime
from django.utils import timezone
from rest_framework.authentication import TokenAuthentication
from rest_framework.authtoken.models import Token
from rest_framework.permissions import IsAuthenticated

# Create your views here.
from rest_framework.views import APIView
from rest_framework.response import Response
from django.core import serializers
import json

from .grab_products.jd_crawler import jd_crawler, jd_login
from .grab_products.sn_crawler import sn_login, sn_crawler
from .grab_products.tool import avoid_check
from .grab_products.vip_crawler import vip_login, vip_crawler
from .models import *
from django.contrib.auth.models import User

jd_map = {}
sn_map = {}
vip_map = {}

class Login(APIView):
    @staticmethod
    def get(request):
        res = {'message': '非法用户'}
        token = request.GET.get('token')
        if token:
            try:
                user = Token.objects.get(key=token).user
                res['info'] = json.loads(serializers.serialize("json", [user]))[0]['fields']
                res['info'].update({'id': user.id})
                res['message'] = '成功获取用户信息'
            except Token.DoesNotExist:
                res['message'] = '无效认证'
            except Exception as e:
                res['message'] = str(e)
                print(str(e))
        return Response(res)

    @staticmethod
    def post(request):
        req = request.data
        if req['method'] == 'login':
            try:
                user = authenticate(request, username=req['username'], password=req['password'])
                if user is not None:
                    # 用户名和密码正确
                    # 为用户生成或获取 Token
                    token, created = Token.objects.get_or_create(user=user)
                    return Response({'token': token.key, 'message': '登录成功'})
                else:
                    # 用户名或密码错误
                    return Response({'message': '用户名或密码错误'})
            except Exception as e:
                print(str(e))
                return Response({'message': str(e)})
        elif req['method'] == 'register':
            try:
                try:
                    validate_email(req['email'])
                except ValidationError:
                    return Response({'message': '邮箱格式不正确'})
                if User.objects.filter(username=req['username']).exists():
                    return Response({'message': '用户名已存在'})
                if User.objects.filter(username=req['email']).exists():
                    return Response({'message': '邮箱已被注册'})
                User.objects.create_user(req['username'], req['email'], req['password'])
                return Response({'message': '注册成功'})
            except Exception as e:
                return Response({'message': str(e)})
        elif req['method'] == 'logout':
            token = req['token']
            if token:
                try:
                    # 尝试找到并删除 Token
                    Token.objects.get(key=token).delete()
                    return Response({'message': '成功退出登录'})
                except Token.DoesNotExist:
                    return Response({'message': '无效认证'})
            return Response({'message': '无效认证'})
        return Response({'message': '无效的请求'})


class Dashboard(APIView):
    # authentication_classes = [TokenAuthentication]
    # permission_classes = [IsAuthenticated]

    @staticmethod
    def get(request):
        merged_data = {}
        req = request.query_params.dict()  # 前端给的params数据
        try:
            if req['method'] == 'check':
                merged_data['jd'] = 'true'
                merged_data['vip'] = 'true'
                merged_data['sn'] = 'true'
                try:
                    jd_cookie = jdCookie.objects.get(user_id=req['user_id'])
                    if timezone.now() - jd_cookie.created_at > timedelta(days=1):
                        jdCookie.objects.filter(user_id=req['user_id']).delete()
                        raise jdCookie.DoesNotExist
                except jdCookie.DoesNotExist:
                    merged_data['jd'] = 'false'
                try:
                    vip_cookie = vipCookie.objects.get(user_id=req['user_id'])
                    if timezone.now() - vip_cookie.created_at > timedelta(days=0.25):
                        vipCookie.objects.filter(user_id=req['user_id']).delete()
                        raise vipCookie.DoesNotExist
                except vipCookie.DoesNotExist:
                    merged_data['vip'] = 'false'
                try:
                    sn_cookie = snCookie.objects.get(user_id=req['user_id'])
                    if timezone.now() - sn_cookie.created_at > timedelta(days=1):
                        snCookie.objects.filter(user_id=req['user_id']).delete()
                        raise snCookie.DoesNotExist
                except snCookie.DoesNotExist:
                    merged_data['sn'] = 'false'
            elif req['method'] == 'jd_login':
                res = {}
                if req['user_id'] not in jd_map:
                    bro = avoid_check()
                    bro.get('https://passport.jd.com/new/login.aspx')
                    res = jd_login(bro)
                else:
                    res = jd_login(jd_map[req['user_id']])
                if res[0] == 'success':
                    jdCookie.objects.create(user_id=req['user_id'], cookie=json.dumps(res[1]))
                    del jd_map[req['user_id']]
                    merged_data['message'] = '扫码成功'
                elif res[0] == 'fail':
                    jd_map[req['user_id']] = res[1]
                    merged_data['qrcode'] = res[2]
                    merged_data['message'] = '待扫码'
            elif req['method'] == 'jd_search':
                jd_cookie = jdCookie.objects.get(user_id=req['user_id'])
                cookies = json.loads(jd_cookie.cookie)
                merged_data['products'], cookies = jd_crawler(req['name'], cookies)
                merged_data['message'] = 'success'
            elif req['method'] == 'vip_login':
                res = {}
                if req['user_id'] not in vip_map:
                    bro = avoid_check()
                    bro.get('https://category.vip.com/suggest.php?keyword=1')
                    res = vip_login(bro)
                else:
                    res = vip_login(vip_map[req['user_id']])
                if res[0] == 'success':
                    vipCookie.objects.create(user_id=req['user_id'], cookie=json.dumps(res[1]))
                    del vip_map[req['user_id']]
                    merged_data['message'] = '扫码成功'
                elif res[0] == 'fail':
                    vip_map[req['user_id']] = res[1]
                    merged_data['qrcode'] = res[2]
                    merged_data['message'] = '待扫码'
            elif req['method'] == 'vip_search':
                vip_cookie = vipCookie.objects.get(user_id=req['user_id'])
                cookies = json.loads(vip_cookie.cookie)
                merged_data['products'], cookies = vip_crawler(req['name'], cookies)
                merged_data['message'] = 'success'
            elif req['method'] == 'sn_login':
                res = {}
                if req['user_id'] not in sn_map:
                    bro = avoid_check()
                    bro.get('https://passport.suning.com/ids/login?service=https%3A%2F%2Floginst.suning.com%2F%2Fauth%3FtargetUrl%3Dhttps%253A%252F%252Fwww.suning.com%252F&method=GET&loginTheme=b2c')
                    res = sn_login(bro)
                else:
                    res = sn_login(sn_map[req['user_id']])
                if res[0] == 'success':
                    snCookie.objects.create(user_id=req['user_id'], cookie=json.dumps(res[1]))
                    del sn_map[req['user_id']]
                    merged_data['message'] = '扫码成功'
                elif res[0] == 'fail':
                    sn_map[req['user_id']] = res[1]
                    merged_data['qrcode'] = res[2]
                    merged_data['message'] = '待扫码'
            elif req['method'] == 'sn_search':
                sn_cookie = snCookie.objects.get(user_id=req['user_id'])
                cookies = json.loads(sn_cookie.cookie)
                merged_data['products'], cookies = sn_crawler(req['name'], cookies)
                merged_data['message'] = 'success'
        except Exception as e:
            merged_data['message'] = str(e)
            print(str(e))
        return Response(merged_data)



class Like(APIView):
    authentication_classes = [TokenAuthentication]
    permission_classes = [IsAuthenticated]

    @staticmethod
    def get(request):
        merged_data = {}
        try:
            req = request.query_params.dict()#前端给的params数据
            product_price = ProductPrice.objects.filter(product_id = req["id"])
            review = Review.objects.filter(product_id = req["id"])
            merged_data['product_price'] = json.loads(serializers.serialize("json", [product_price]))
            merged_data['review'] = json.loads(serializers.serialize("json", [review]))
            merged_data['message'] = 'success'
        except Exception as e:
            merged_data['message'] = str(e)
            print(str(e))
        return Response(merged_data)

    @staticmethod
    def post(request):
        res = ''
        try:
            req = request.data#前端给的json包数据
            Review(product_id=req["product_id"],user_id=req["user_id"],user_name=req["user_name"],
                   grade=req["grade"],comment=req["comment"],create_time=datetime.datetime.now().strftime('%Y-%m-%d %H:%M')).save()#保存数据
            res = 'success'
        except Exception as e:
            res = str(e)
            print(str(e))
        return Response(res)
