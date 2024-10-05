from heapq import merge
from itertools import product

from django.db.models.functions import datetime
from django.shortcuts import render

# Create your views here.
from rest_framework.views import APIView
from rest_framework.response import Response
from django.http import JsonResponse
from django.core import serializers
import json
from .models import *


class DetailProduct(APIView):
    @staticmethod
    def get(request):
        merged_data = {}
        try:
            req = request.query_params.dict()#前端给的params数据
            id = req["id"]
            product_price = ProductPrice.objects.get(product=id)
            review = Review.objects.get(product=id)
            merged_data['product_price'] = json.loads(serializers.serialize("json", product_price))
            merged_data['review'] = json.loads(serializers.serialize("json", review))
            merged_data['error'] = 'success'
        except Exception as e:
            merged_data['error'] = str(e)
        return JsonResponse(merged_data)

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
        return Response(res)
