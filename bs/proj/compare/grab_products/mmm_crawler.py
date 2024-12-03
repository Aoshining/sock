import json
from lxml import etree
from time import sleep
import time
from selenium.webdriver.common.by import By

from compare.grab_products.tool import avoid_check, draw_num

def crawler(name):
    goods_info = []
    # 无头浏览与规避检测
    bro = avoid_check()
    bro.get('https://s.manmanbuy.com/Default.aspx?key=%C7%EB%CA%E4%C8%EB%C4%FA%CF%EB%B1%C8%BD%CF%B5%C4%C9%CC%C6%B7%C3%FB%B3%C6%BB%F2%D0%CD%BA%C5&btnSearch=%CB%D1%CB%F7')
    # 进入登录界面
    # in_btn = bro.find_element(By.XPATH, '//div[@class="loginWxAppHeader"]/img')
    # in_btn.click()
    # up_btn = bro.find_element(By.XPATH, '//div[@class="loginPasswordTab"]/p[text()="密码登录"]')
    # # up_btn.click()
    # bro.execute_script('arguments[0].click();', up_btn)
    element1 = bro.find_element('class name', 'loginWxApp')
    new_style1 = "display:none;"
    element2 = bro.find_element('class name', 'loginPassword')
    new_style2 = "display:block;"
    bro.execute_script("arguments[0].style.cssText = arguments[1];arguments[2].style.cssText = arguments[3];", element1, new_style1, element2, new_style2)
    # 输入用户名与密码进行登录
    user_input = bro.find_element('class name', value='user')
    user_input.send_keys('13207208909')
    password_input = bro.find_element('class name', value='password')
    password_input.send_keys('waz20040401')
    login_btn = bro.find_element('class name', value='logon')
    login_btn.click()
    # 标签定位
    search_input = bro.find_element('id', value='skey')
    # 搜索关键词
    search_input.send_keys(name)
    # 点击搜索按钮
    btn = bro.find_element('class name', value='btnSearch')
    btn.click()
    sleep(2)
    # 执行一组js程序滚动页面置底
    bro.execute_script('window.scrollTo(0,document.body.scrollHeight)')
    sleep(2)
    # 数据解析
    tree = etree.HTML(bro.page_source)
    goods_li_list = (tree.xpath('//div[@class="div1100"]/div[@class="bjlineSmall"]'))
    i = 0
    for li in goods_li_list:
        # 图片
        goods_img = li.xpath('.//div[@class="pic"]/a/img/@src')[0]
        # 商品标题
        goods_title = ''.join(li.xpath('.//div[@class="t"]/a//text()'))
        # 商品价格
        goods_price = li.xpath('.//div[@class="cost"]/div/span[@class="listpricespan"]/text()')[0]
        if draw_num(goods_price) == '':
            goods_price = 0
        # 销量
        goods_sales = li.xpath('.//div[@class="comment"]/a/text()')
        if not goods_sales:
            goods_sales.append('未知')
        goods_sales = ''.join(goods_sales[0])
        # 商品链接
        goods_link = ''.join(li.xpath('.//div[@class="t"]/a/@href'))
        final = avoid_check()
        final.get(goods_link)
        goods_link = final.current_url
        # 平台
        goods_platform = json.loads(li.get('v')).get('sitename')
        i = i + 1
        goods_info.append({
            'img': goods_img,
            'title': goods_title,
            'price': float(goods_price),
            'sales': goods_sales,
            'platform': goods_platform,
            'link': goods_link,
        })
    sleep(5)
    # 关闭无头浏览器
    bro.quit()
    return goods_info