from lxml import etree
from time import sleep

from selenium.common.exceptions import NoSuchElementException
import time

from compare.grab_products.tool import web_driver, num, safe_click


def jd_login(bro):
    try:
        # 等待用户扫描并登录，检查“退出登录”是否出现
        bro.find_element('xpath', '//*[@id="J_user"]/div/div[1]/div/p[2]/span/a[2]')
        # 存储cookie
        cookies = bro.get_cookies()
        # # 关闭浏览器
        # bro.quit()
        return 'success', cookies
    except NoSuchElementException:
        # 处理未找到元素情况
        try:
            qrcode_btn = bro.find_element('xpath', '//*[@id="kbCoagent"]/ul/li[2]/a')
            safe_click(bro, qrcode_btn)
        except NoSuchElementException:
            print('已在二维码页面')
        bro.refresh()
        try:
            qrcode_img = bro.find_element('xpath', "//*[@id='tpl_for_page']/span[1]/div[1]/div[4]/div[1]/img").get_attribute('src')
            return 'fail', bro, qrcode_img
        except NoSuchElementException:
            return 'fail', bro, ''

def jd_crawler(name, bro):
    goods_info = []
    # 标签定位
    search_input = bro.find_element('id', value='key')
    # 搜索关键词
    search_input.clear()
    search_input.send_keys(name)
    # 点击搜索按钮
    btn = bro.find_element('class name', value='button')
    safe_click(bro, btn)
    sleep(1)
    # 执行一组js程序滚动页面置底
    bro.execute_script('window.scrollTo(0,document.body.scrollHeight)')
    sleep(1)
    # 数据解析
    tree = etree.HTML(bro.page_source)
    goods_li_list = (tree.xpath('//div[@id="J_goodsList"]/ul/li'))
    i = 0
    for li in goods_li_list:
        i += 1
        if i > 20:
            break
        # 图片
        goods_img = li.xpath('.//div[@class="p-img"]/a/img/@src')
        if not goods_img:
            goods_img = li.xpath('.//div[@class="p-img"]/a/img/@data-lazy-img')
        goods_img = 'https:' + goods_img[0]
        # 商品标题
        goods_title = ''.join(li.xpath('.//div[@class="p-name p-name-type-2"]/a/em//text()'))
        # 商品价格
        goods_price = li.xpath('.//div[@class="p-price"]/strong/i/text()')[0]
        if num(goods_price) == '':
            continue
        # 销量
        goods_sales = li.xpath('.//div[@class="p-commit"]/strong/a/text()')
        if not goods_sales:
            goods_sales.append('未知')
        goods_sales = goods_sales[0].strip()
        # 店铺名
        goods_shop = li.xpath('.//div[@class="p-shop"]/span/a/@title')
        if not goods_shop:
            goods_shop.append('未知')
        goods_shop = goods_shop[0]
        # 商品链接
        goods_link = 'https:' + ''.join(li.xpath('.//div[@class="p-name p-name-type-2"]/a/@href'))
        # 平台
        goods_platform = '京东'
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