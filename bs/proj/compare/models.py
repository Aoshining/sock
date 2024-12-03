from django.contrib.auth.models import User
from django.db import models

# Create your models here.
from django.db import models

class Product(models.Model):
    name = models.CharField(max_length=255)
    description = models.TextField()
    category = models.CharField(max_length=255)
    brand = models.CharField(max_length=255)
    price = models.DecimalField(max_digits=10, decimal_places=2)

    def __str__(self):
        return self.name

class Seller(models.Model):
    name = models.CharField(max_length=255)
    description = models.TextField()
    link = models.CharField(max_length=255)

    def __str__(self):
        return self.name

class ProductPrice(models.Model):
    product = models.ForeignKey(Product, on_delete=models.CASCADE)
    seller = models.ForeignKey(Seller, on_delete=models.CASCADE)
    price = models.DecimalField(max_digits=10, decimal_places=2)
    updated = models.DateTimeField(auto_now=True)

    def __str__(self):
        return f"{self.product.name} - {self.seller.name}"

class Review(models.Model):
    product = models.ForeignKey(Product, on_delete=models.CASCADE)
    user = models.ForeignKey(User, on_delete=models.CASCADE)
    rating = models.IntegerField()
    comment = models.TextField()
    created_at = models.DateTimeField(auto_now_add=True)

    def __str__(self):
        return f"{self.product.name} - {self.user.username}"

class ProductImage(models.Model):
    product = models.ForeignKey(Product, on_delete=models.CASCADE)
    image_url = models.URLField()
    is_main = models.BooleanField(default=False)

    def __str__(self):
        return f"Image {self.id} for {self.product.name}"

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