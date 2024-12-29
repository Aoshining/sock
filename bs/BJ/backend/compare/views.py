import time
from datetime import timedelta
from time import sleep

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

from .grab_products.his_crawler import his_crawler
from .grab_products.jd_crawler import jd_crawler, jd_login
from .grab_products.sn_crawler import sn_login, sn_crawler
from .grab_products.tool import web_driver
from .grab_products.vip_crawler import vip_login, vip_crawler
from .models import *
from django.contrib.auth.models import User
from decimal import Decimal
import smtplib
from email.mime.text import MIMEText
from email.header import Header
import email
import requests
from django.http import JsonResponse

jd_map = {}
sn_map = {}
vip_map = {}
his_map = {}

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
                Info.check_price_changes(user.id)
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
                if user is None:
                    # 尝试邮箱登录
                    user = User.objects.filter(email=req['username']).first()
                    if user is not None:
                        username = user.username
                        user = authenticate(request, username=username, password=req['password'])
                        if user is not None:
                            # 用户名和密码正确
                            # 为用户生成或获取 Token
                            token, created = Token.objects.get_or_create(user=user)
                            return Response({'token': token.key, 'message': '登录成功'})
                    # 用户名或密码错误
                    return Response({'message': '用户名或密码错误'})
                else:
                    token, created = Token.objects.get_or_create(user=user)
                    return Response({'token': token.key, 'message': '登录成功'})
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
                if User.objects.filter(email=req['email']).exists():
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
                    if req['user_id'] in jd_map:
                        jd_map[req['user_id']].quit()
                        del jd_map[req['user_id']]
                    merged_data['jd'] = 'false'
                try:
                    vip_cookie = vipCookie.objects.get(user_id=req['user_id'])
                    if timezone.now() - vip_cookie.created_at > timedelta(days=0.25):
                        vipCookie.objects.filter(user_id=req['user_id']).delete()
                        raise vipCookie.DoesNotExist
                except vipCookie.DoesNotExist:
                    if req['user_id'] in vip_map:
                        vip_map[req['user_id']].quit()
                        del vip_map[req['user_id']]
                    merged_data['vip'] = 'false'
                try:
                    sn_cookie = snCookie.objects.get(user_id=req['user_id'])
                    if timezone.now() - sn_cookie.created_at > timedelta(days=1):
                        snCookie.objects.filter(user_id=req['user_id']).delete()
                        raise snCookie.DoesNotExist
                except snCookie.DoesNotExist:
                    if req['user_id'] in sn_map:
                        sn_map[req['user_id']].quit()
                        del sn_map[req['user_id']]
                    merged_data['sn'] = 'false'
            elif req['method'] == 'jd_login':
                res = {}
                if req['user_id'] not in jd_map:
                    bro = web_driver()
                    bro.get('https://passport.jd.com/new/login.aspx')
                    res = jd_login(bro)
                else:
                    res = jd_login(jd_map[req['user_id']])
                if res[0] == 'success':
                    jdCookie.objects.create(user_id=req['user_id'], cookie=json.dumps(res[1]))
                    # del jd_map[req['user_id']]
                    merged_data['message'] = '扫码成功'
                elif res[0] == 'fail':
                    jd_map[req['user_id']] = res[1]
                    merged_data['qrcode'] = res[2]
                    merged_data['message'] = '待扫码'
            elif req['method'] == 'jd_search':
                jd_cookie = jdCookie.objects.get(user_id=req['user_id'])
                cookies = json.loads(jd_cookie.cookie)
                if req['user_id'] not in jd_map:
                    bro = web_driver()
                    bro.get('https://www.jd.com/')
                    for cookie in cookies:
                        bro.add_cookie(cookie)
                else:
                    bro = jd_map[req['user_id']]
                merged_data['products'], jd_map[req['user_id']] = jd_crawler(req['name'], bro)
                merged_data['message'] = 'success'
                Info.addProducts(merged_data['products'])
                Info.check_price_changes(req['user_id'])
            elif req['method'] == 'vip_login':
                res = {}
                if req['user_id'] not in vip_map:
                    bro = web_driver()
                    bro.get('https://category.vip.com/suggest.php?keyword=1')
                    res = vip_login(bro)
                else:
                    res = vip_login(vip_map[req['user_id']])
                if res[0] == 'success':
                    vipCookie.objects.create(user_id=req['user_id'], cookie=json.dumps(res[1]))
                    # del vip_map[req['user_id']]
                    merged_data['message'] = '扫码成功'
                elif res[0] == 'fail':
                    vip_map[req['user_id']] = res[1]
                    merged_data['qrcode'] = res[2]
                    merged_data['message'] = '待扫码'
            elif req['method'] == 'vip_search':
                vip_cookie = vipCookie.objects.get(user_id=req['user_id'])
                cookies = json.loads(vip_cookie.cookie)
                if req['user_id'] not in vip_map:
                    bro = web_driver()
                    bro.get('https://www.vip.com/')
                    for cookie in cookies:
                        cookie['domain'] = '.vip.com'
                        bro.add_cookie(cookie)
                    sleep(3)
                else:
                    bro = vip_map[req['user_id']]
                merged_data['products'], vip_map[req['user_id']] = vip_crawler(req['name'], bro)
                merged_data['message'] = 'success'
                Info.addProducts(merged_data['products'])
                Info.check_price_changes(req['user_id'])
            elif req['method'] == 'sn_login':
                res = {}
                if req['user_id'] not in sn_map:
                    bro = web_driver()
                    bro.get('https://passport.suning.com/ids/login?service=https%3A%2F%2Floginst.suning.com%2F%2Fauth%3FtargetUrl%3Dhttps%253A%252F%252Fwww.suning.com%252F&method=GET&loginTheme=b2c')
                    res = sn_login(bro)
                else:
                    res = sn_login(sn_map[req['user_id']])
                if res[0] == 'success':
                    snCookie.objects.create(user_id=req['user_id'], cookie=json.dumps(res[1]))
                    # del sn_map[req['user_id']]
                    merged_data['message'] = '扫码成功'
                elif res[0] == 'fail':
                    sn_map[req['user_id']] = res[1]
                    merged_data['qrcode'] = res[2]
                    merged_data['message'] = '待扫码'
            elif req['method'] == 'sn_search':
                sn_cookie = snCookie.objects.get(user_id=req['user_id'])
                cookies = json.loads(sn_cookie.cookie)
                if req['user_id'] not in sn_map:
                    bro = web_driver()
                    bro.get('https://www.suning.com/')
                    for cookie in cookies:
                        bro.add_cookie(cookie)
                else:
                    bro = sn_map[req['user_id']]
                merged_data['products'], sn_map[req['user_id']] = sn_crawler(req['name'], bro)
                merged_data['message'] = 'success'
                Info.addProducts(merged_data['products'])
                Info.check_price_changes(req['user_id'])
        except Exception as e:
            merged_data['message'] = str(e)
            print(str(e))
        return Response(merged_data)



class Like(APIView):

    @staticmethod
    def get(request):
        merged_data = {}
        try:
            req = request.query_params.dict()
            merged_data['products'] = []
            if Likes.objects.filter(user_id=req['user_id']).exists():
                likes = Likes.objects.filter(user_id=req['user_id'])
                products = json.loads(serializers.serialize("json", likes))
                for product in products:
                    merged_data['products'].append(product['fields'])
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
            if req['method'] == 'like':
                if not Likes.objects.filter(user_id=req['user_id'], link=req['link']).exists():
                    Likes.objects.create(user_id=req['user_id'], img=req['img'], title=req['title'], price=req['price'],
                                     sales=req['sales'], shop=req['shop'], platform=req['platform'], link=req['link'])
                    res = '成功收藏'
                else:
                    res = '已收藏该商品'
            elif req['method'] == 'unlike':
                if Likes.objects.filter(user_id=req['user_id'], link=req['link']).exists():
                    Likes.objects.filter(user_id=req['user_id'], link=req['link']).delete()
                    res = '成功取消收藏'
        except Exception as e:
            res = str(e)
            print(str(e))
        return Response(res)

class Price(APIView):
    @staticmethod
    def get(request):
        payload = []
        try:
            req = request.query_params.dict()
            if Products.objects.filter(link=req['link']).exists():
                products = Products.objects.filter(link=req['link'])
                products_list = json.loads(serializers.serialize("json", products))
                for product in products_list:
                    payload.append(product['fields'])
            if req['user_id'] not in his_map:
                bro = web_driver()
                bro.get('https://www.hisprice.cn/')
                his_map[req['user_id']] = bro
            products_list = his_crawler(his_map[req['user_id']], req['link'])
            if products_list:
                Products.objects.create(img=products_list[0]['img'], title=products_list[0]['title'], price=products_list[0]['price'], sales=products_list[0]['sales'],
                                        shop=products_list[0]['shop'], platform=products_list[0]['platform'], link=products_list[0]['link'], time=products_list[0]['time'])
                payload.append(products_list[0])
                Info.check_price_changes(req['user_id'])
        except Exception as e:
            print(str(e))
        return Response(payload)

class Info(APIView):
    @staticmethod
    def get(request):
        merged_data = {'message': 'failed'}
        try:
            req = request.query_params.dict()
            if req['method'] == 'get_alerts':
                # 获取用户的降价提醒
                alerts = PriceAlert.objects.filter(
                    user_id=req['user_id'],
                    is_read=False
                ).order_by('-time')
                
                alerts_list = json.loads(serializers.serialize('json', alerts))
                merged_data['alerts'] = [
                    {
                        'id': alert['pk'],
                        **alert['fields']  # 展开其他字段
                    } 
                    for alert in alerts_list
                ]
                merged_data['message'] = 'success'
                
        except Exception as e:
            merged_data['message'] = str(e)
            print(str(e))
        return Response(merged_data)

    @staticmethod
    def post(request):
        merged_data = {'message': 'failed'}
        try:
            req = request.data
            if req['method'] == 'update_profile':
                # 获取当前用户
                user = User.objects.get(id=req['user_id'])
                
                # 检查用户名是否已存在（排除当前用户）
                if User.objects.filter(username=req['name']).exclude(id=req['user_id']).exists():
                    merged_data['message'] = '用户名已被使用'
                    return Response(merged_data)
                
                # 验证邮箱格式
                try:
                    validate_email(req['email'])
                except ValidationError:
                    merged_data['message'] = '邮箱格式不正确'
                    return Response(merged_data)
                
                # 检查邮箱是否已存在（排除当前用户）
                if User.objects.filter(email=req['email']).exclude(id=req['user_id']).exists():
                    merged_data['message'] = '邮箱已被使用'
                    return Response(merged_data)
                
                # 更新用户信息
                user.username = req['name']
                user.email = req['email']
                user.save()
                merged_data['message'] = 'success'
                
            elif req['method'] == 'dismiss_alert':
                # 获取提醒记录
                alert = PriceAlert.objects.get(id=req['alert_id'])
                
                # 更新提醒状态
                alert.is_read = True
                alert.save()
                
                # 更新收藏商品的 change 状态
                like = Likes.objects.get(user_id=alert.user_id, link=alert.link)
                like.change = 0  # 重置价格变化状态
                like.save()
                
                merged_data['message'] = 'success'
                
        except Exception as e:
            merged_data['message'] = str(e)
            print(str(e))
        return Response(merged_data)

    @staticmethod
    def send_price_alert_email(user_email, product_title, old_price, new_price, link):
        """发送降价提醒邮件"""
        try:
            # 邮件服务器配置
            smtp_server = "smtp.zju.edu.cn"
            smtp_port = 25
            sender = "3220105775@zju.edu.cn"
            password = "waz20040401"
            
            # 计算降价金额和降价比例
            price_diff = float(old_price) - float(new_price)
            discount_percent = (price_diff / float(old_price)) * 100
            
            # 邮件内容
            html_content = f"""
            <div style="padding: 20px; font-family: Arial, sans-serif;">
                <h2 style="color: #409EFF;">商品降价提醒</h2>
                <p>您关注的商品已降价：</p>
                <p><strong>{product_title}</strong></p>
                <p style="color: #67c23a;">
                    原价：¥{old_price}<br>
                    现价：¥{new_price}<br>
                    降价：¥{price_diff:.2f} (降幅 {discount_percent:.1f}%)
                </p>
                <p>
                    <a href="{link}" style="
                        display: inline-block;
                        padding: 10px 20px;
                        background-color: #409EFF;
                        color: white;
                        text-decoration: none;
                        border-radius: 4px;
                    ">
                        立即查看
                    </a>
                </p>
                <p style="color: #909399; font-size: 12px;">
                    这是一封自动发送的邮件，请勿直接回复。
                </p>
            </div>
            """
            
            # 创建邮件对象
            message = MIMEText(html_content, 'html', 'utf-8')
            
            # 按照 RFC5322 标准设置邮件头
            sender_name = Header('商品降价提醒', 'utf-8').encode()
            message['From'] = email.utils.formataddr((sender_name, sender))
            message['To'] = email.utils.formataddr(('', user_email))
            message['Subject'] = Header(f'您关注的商品 "{product_title}" 降价了！', 'utf-8')
            message['Date'] = email.utils.formatdate(localtime=True)
            message['Message-ID'] = email.utils.make_msgid(domain='zju.edu.cn')
            message['MIME-Version'] = '1.0'
            message['Content-Type'] = 'text/html; charset=utf-8'
            
            # 发送邮件
            with smtplib.SMTP(smtp_server, smtp_port) as server:
                server.starttls()  # 启用 TLS 加密
                server.login(sender, password)
                server.send_message(message)
                
            print(f"降价提醒邮件已发送至 {user_email}")
            
        except Exception as e:
            print(f"发送降价提醒邮件失败: {str(e)}")
            # 可以在这里添加其他错误处理逻辑，比如记录到日志

    @staticmethod
    def check_price_changes(user_id):
        """检查用户收藏商品的价格变化"""
        try:
            # 获取用户收藏的所有商品
            likes = Likes.objects.filter(user_id=user_id)

            # 获取用户邮箱
            user = User.objects.get(id=user_id)
            user_email = user.email
            
            for like in likes:
                # 获取商品最新价格记录
                latest_price = Products.objects.filter(
                    link=like.link
                ).order_by('-time').first()
                
                if latest_price:
                    old_price = Decimal(like.price)
                    new_price = Decimal(latest_price.price)
                    
                    # 更新价格变化状态
                    if new_price < old_price:
                        like.change = -1  # 降价
                        # 创建降价提醒
                        PriceAlert.objects.create(
                            user_id=user_id,
                            img=like.img,
                            title=like.title,
                            old_price=old_price,
                            new_price=new_price,
                            link=like.link,
                            time=time.strftime('%Y-%m-%d %H:%M', time.localtime())
                        )
                        
                        # 发送降价提醒邮件
                        Info.send_price_alert_email(
                            user_email=user_email,
                            product_title=like.title,
                            old_price=old_price,
                            new_price=new_price,
                            link=like.link
                        )
                        
                    elif new_price > old_price:
                        like.change = 1   # 涨价
                    
                    # 更新收藏商品的价格
                    like.price = str(new_price)
                    like.save()
                    
        except Exception as e:
            print(f"检查价格变化时出错: {str(e)}")


    @staticmethod
    def addProducts(products):
        products_list = [
            Products(
                img=product['img'],
                title=product['title'],
                price=product['price'],
                sales=product['sales'],
                shop=product['shop'],
                platform=product['platform'],
                link=product['link'],
                time=product['time'],
            )
            for product in products
        ]
        Products.objects.bulk_create(products_list)

def get_search_suggestions(request):
    keywords = request.GET.get('keywords', '')
    try:
        response = requests.get('https://www.bijia.com/search/get_keywords', {
            'keywords': keywords
        }, headers={
            'Referer': 'https://www.bijia.com',
            'Origin': 'https://www.bijia.com',
            'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/120.0.0.0 Safari/537.36'
        })
        return JsonResponse(response.json())
    except Exception as e:
        return JsonResponse({'error_code': 1, 'error_msg': str(e)})

