import random

from lxml import etree
from time import sleep

from selenium.common.exceptions import NoSuchElementException
from selenium.webdriver.common.keys import Keys
import time

from compare.grab_products.tool import web_driver, num, safe_click


def vip_login(bro):
    try:
        # 等待用户扫描并登录，检查“搜索键”是否出现
        bro.find_element('xpath', '//*[@id="J-search"]/div[1]/a')
        # 存储cookie
        cookies = bro.get_cookies()
        # # 关闭浏览器
        # bro.quit()
        return 'success', cookies
    except NoSuchElementException:
        try:
            qrcode_url = bro.find_element('xpath', '/html/body/div[2]/div/div[1]/div[2]/div/div[1]/div/a').get_attribute('href')
            bro.get(qrcode_url)
        except NoSuchElementException:
            print('已在二维码界面')
        bro.refresh()
        try:
            qrcode_img = bro.find_element('xpath', "//*[@id='tpl_for_page']/span[1]/div[1]/div[4]/div[1]/img").get_attribute('src')
            return 'fail', bro, qrcode_img
        except NoSuchElementException:
            return 'fail', bro, ''

def vip_crawler(name, bro):
    goods_info = []
    # 标签定位
    search_input = bro.find_element('xpath', '//*[@id="J-search"]/div[1]/input')
    # 搜索关键词
    search_input.clear()
    search_input.send_keys(name)
    # 回车以搜索
    search_input.send_keys(Keys.ENTER)
    sleep(1)
    # 获取页面高度和视口高度
    page_height = bro.execute_script("return document.body.scrollHeight")
    viewport_height = bro.execute_script("return window.innerHeight")
    # 初始化当前滚动位置
    current_position = 0
    # 执行一组js程序滚动页面置底
    while current_position < page_height * 0.2:
        bro.execute_script(f"window.scrollTo(0, {current_position + viewport_height});")
        current_position += viewport_height
        # 等待图片加载
        sleep(2.5)
    # 数据解析
    tree = etree.HTML(bro.page_source)
    goods_li_list = (tree.xpath('//*[@id="J_searchCatList"]/div[@class="c-goods-item  J-goods-item c-goods-item--auto-width"]'))
    i = 0
    for li in goods_li_list:
        i += 1
        if i > 20:
            break
        # 图片
        goods_img = li.xpath('.//a/div[1]/div[1]/img/@src')
        if not goods_img:
            goods_img = li.xpath('.//a/div[1]/div[1]/img/@data-original')
        goods_img = 'https:' + goods_img[0]
        # 商品标题
        goods_title = ''.join(li.xpath('.//a/div[2]/div[2]//text()'))
        # 商品价格
        goods_price = li.xpath('.//a/div[2]/div[1]/div[1]/div[@class="c-goods-item__sale-price J-goods-item__sale-price"]/text()')[0]
        if num(goods_price) == '':
            continue
        # 销量
        goods_sales = '（未知）'
        # 店铺名
        goods_shop = '唯品会官方旗舰店'
        # 商品链接
        goods_link = 'https:' + ''.join(li.xpath('.//a/@href'))
        # 平台
        goods_platform = '唯品会'
        goods_info.append({
            'img': goods_img,
            'title': goods_title,
            'price': float(goods_price),
            'sales': goods_sales,
            'shop': goods_shop,
            'platform': goods_platform,
            'link': goods_link,
            'time': time.strftime('%Y-%m-%d %H:%M', time.localtime())
        })
    return goods_info, bro