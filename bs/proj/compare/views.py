from heapq import merge
from itertools import product

from django.contrib.auth import authenticate
from django.core.exceptions import ValidationError
from django.core.validators import validate_email
from django.db.models.functions import datetime
from rest_framework.authentication import TokenAuthentication
from rest_framework.authtoken.models import Token
from rest_framework.permissions import IsAuthenticated

# Create your views here.
from rest_framework.views import APIView
from rest_framework.response import Response
from django.core import serializers
import json
from .models import *
from django.contrib.auth.models import User

class Login(APIView):
    @staticmethod
    def get(request):
        res = {'message': '非法用户'}
        token = request.GET.get('token')
        if token:
            try:
                user = Token.objects.get(key=token).user
                res['info'] = json.loads(serializers.serialize("json", [user]))
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
                    return Response({'message': '成功注销'})
                except Token.DoesNotExist:
                    return Response({'message': '无效认证'})
            return Response({'message': '无效认证'})
        return Response({'message': '无效的请求'})


class Dashboard(APIView):
    authentication_classes = [TokenAuthentication]
    permission_classes = [IsAuthenticated]

    @staticmethod
    def get(request):
        merged_data = {}
        try:
            req = request.query_params.dict()  # 前端给的params数据
            products = Product.objects.filter(name__icontains=req["name"])
            merged_data['products'] = json.loads(serializers.serialize("json", [products]))
            merged_data['message'] = 'success'
        except Exception as e:
            merged_data['message'] = str(e)
            print(str(e))
        return Response(merged_data)

class Detail(APIView):
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
