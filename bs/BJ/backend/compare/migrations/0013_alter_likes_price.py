# Generated by Django 4.2.7 on 2024-12-28 22:29

from django.db import migrations, models


class Migration(migrations.Migration):

    dependencies = [
        ('compare', '0012_alter_likes_title_alter_pricealert_title_and_more'),
    ]

    operations = [
        migrations.AlterField(
            model_name='likes',
            name='price',
            field=models.DecimalField(decimal_places=2, max_digits=10),
        ),
    ]
