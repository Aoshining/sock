from time import sleep
import time
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.support import expected_conditions as EC

from compare.grab_products.tool import web_driver, num, safe_click

def his_crawler(bro, link):
    goods_info = []
    # 标签定位
    search_input = bro.find_element('id', value='kValId')
    # 搜索关键词
    search_input.clear()
    search_input.send_keys(link)
    # 点击搜索按钮
    if bro.current_url == 'https://www.hisprice.cn/':
        btn = bro.find_element('xpath', value='//*[@id="main"]/div/div[3]/form/button')
    else:
        btn = bro.find_element('xpath', value='/html/body/div[3]/div[1]/div[1]/form/button')
    safe_click(bro, btn)
    try:
        element = WebDriverWait(bro, 5).until(EC.visibility_of_element_located(('xpath', '//*[@id="titlespId"]')))

        # 商品标题
        goods_title = ''.join(element.text)

        # 商品价格
        element = WebDriverWait(bro, 5).until(EC.visibility_of_element_located(('xpath', '//*[@id="Acontainertooltip"]')))
        goods_price = element.text
        if num(goods_price) == '':
            return []

        # 平台
        goods_platform = ''
        if 'jd' in link:
            goods_platform = '京东'
        if 'vip' in link:
            goods_platform = '唯品会'
        if 'sn' in link:
            goods_platform = '苏宁'

        goods_info.append({
            'img': '',
            'title': goods_title,
            'price': float(goods_price),
            'sales': '尚待查询',
            'shop': '尚待查询',
            'platform': goods_platform,
            'link': link,
            'time': time.strftime('%Y-%m-%d %H:%M', time.localtime())
        })
        return goods_info
    except Exception as e:
        print(e)
        return []