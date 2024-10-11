from django.urls import path
from . import views

urlpatterns = [
    path('login/', views.Login.as_view()),
    path('dashboard/', views.Dashboard.as_view()),
    path('detail/', views.Detail.as_view()),
]
