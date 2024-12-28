from django.urls import path
from . import views

urlpatterns = [
    path('login/', views.Login.as_view()),
    path('dashboard/', views.Dashboard.as_view()),
    path('like/', views.Like.as_view()),
    path('price/', views.Price.as_view()),
    path('info/', views.Info.as_view()),
    path('search/suggestions/', views.get_search_suggestions, name='search_suggestions'),
]
