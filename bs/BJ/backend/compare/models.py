from django.contrib.auth.models import User
from django.db import models

# Create your models here.
from django.db import models
from django.utils import timezone


class Products(models.Model):
    img = models.URLField(max_length=255)
    title = models.CharField(max_length=255, db_collation='utf8mb4_unicode_ci')
    price = models.DecimalField(max_digits=10, decimal_places=2)
    sales = models.CharField(max_length=50)
    shop = models.CharField(max_length=255)
    platform = models.CharField(max_length=50)
    link = models.URLField(max_length=255)
    time = models.DateTimeField(default=timezone.now)

    def __str__(self):
        return self.title

class Likes(models.Model):
    user = models.ForeignKey(User, on_delete=models.CASCADE)
    img = models.URLField(max_length=255)
    title = models.CharField(max_length=255, db_collation='utf8mb4_unicode_ci')
    price = models.DecimalField(max_digits=10, decimal_places=2)
    sales = models.CharField(max_length=50)
    shop = models.CharField(max_length=255)
    platform = models.CharField(max_length=50)
    link = models.URLField(max_length=255)
    change = models.IntegerField(default=0)

    def __str__(self):
        return self.title

class jdCookie(models.Model):
    user = models.ForeignKey(User, on_delete=models.CASCADE)
    cookie = models.TextField()  # 存储cookie的字段，使用TextField因为它可能很长
    created_at = models.DateTimeField(auto_now_add=True)  # 创建时间

    def __str__(self):
        return f"{self.user.username}'s jd_cookie"

class snCookie(models.Model):
    user = models.ForeignKey(User, on_delete=models.CASCADE)
    cookie = models.TextField()  # 存储cookie的字段，使用TextField因为它可能很长
    created_at = models.DateTimeField(auto_now_add=True)  # 创建时间

    def __str__(self):
        return f"{self.user.username}'s sn_cookie"

class vipCookie(models.Model):
    user = models.ForeignKey(User, on_delete=models.CASCADE)
    cookie = models.TextField()  # 存储cookie的字段，使用TextField因为它可能很长
    created_at = models.DateTimeField(auto_now_add=True)  # 创建时间

    def __str__(self):
        return f"{self.user.username}'s vip_cookie"

class PriceAlert(models.Model):
    user_id = models.IntegerField()
    img = models.URLField(max_length=255)
    title = models.CharField(max_length=255, db_collation='utf8mb4_unicode_ci')
    old_price = models.DecimalField(max_digits=10, decimal_places=2)
    new_price = models.DecimalField(max_digits=10, decimal_places=2)
    link = models.URLField(max_length=255)
    time = models.DateTimeField(default=timezone.now)
    is_read = models.BooleanField(default=False)