from django.urls import path
from . import views

urlpatterns = [
    path('login/', views.Login.as_view()),
    path('dashboard/', views.Dashboard.as_view()),
    path('like/', views.Like.as_view()),
]
