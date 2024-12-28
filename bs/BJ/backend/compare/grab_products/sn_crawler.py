from lxml import etree
from time import sleep

from selenium.common.exceptions import NoSuchElementException
import time

from compare.grab_products.tool import web_driver, num, safe_click


def sn_login(bro):
    try:
        # 等待用户扫描并登录，检查“搜索键”是否出现
        bro.find_element('xpath', '//*[@id="searchSubmit"]')
        # 存储cookie
        cookies = bro.get_cookies()
        # # 关闭浏览器
        # bro.quit()
        return 'success', cookies
    except NoSuchElementException:
        # 处理未成功登录情况
        try:
            qrcode_btn = bro.find_element('xpath', '/html/body/div[2]/div[1]/div/div[5]/div[1]/a[2]')
            safe_click(bro, qrcode_btn)
        except NoSuchElementException:
            print('已在二维码页面')
        bro.refresh()
        try:
            qrcode_img = bro.find_element('xpath', "//*[@id='tpl_for_page']/span[1]/div[1]/div[4]/div[1]/img").get_attribute('src')
            return 'fail', bro, qrcode_img
        except NoSuchElementException:
            return 'fail', bro, ''

def sn_crawler(name, bro):
    goods_info = []
    # 标签定位
    search_input = bro.find_element('id', value='searchKeywords')
    # 搜索关键词
    search_input.clear()
    search_input.send_keys(name)
    # 点击搜索按钮
    btn = bro.find_element('id', value='searchSubmit')
    safe_click(bro, btn)
    sleep(1)
    # 执行一组js程序滚动页面底部
    bro.execute_script('window.scrollTo(0,document.body.scrollHeight)')
    sleep(1)
    # 数据解析
    tree = etree.HTML(bro.page_source)
    goods_li_list = (tree.xpath('//div[@id="product-list"]/ul/li'))
    i = 0
    for li in goods_li_list:
        i += 1
        if i > 20:
            break
        # 图片
        goods_img = li.xpath('.//div[@class="img-block"]/a/img/@src')
        goods_img = 'https:' + goods_img[0]
        # 商品标题
        goods_title = ''.join(li.xpath('.//div[@class="title-selling-point"]/a//text()')).replace('\n', '')[0:127]
        # 商品价格
        goods_price = ''.join(li.xpath('.//div[@class="price-box"]/span/text()')).replace('\n', '') + \
                      ''.join(li.xpath('.//div[@class="price-box"]/span/i[2]/text()')).replace('\n', '')
        if num(goods_price) == '':
            continue
        # 销量
        goods_sales = li.xpath('.//div[@class="info-evaluate"]/a/i/text()')
        if not goods_sales:
            goods_sales.append('未知')
        goods_sales = goods_sales[0]
        # 店铺名
        goods_shop = li.xpath('.//div[@class="store-stock"]/a/text()')
        if not goods_shop:
            goods_shop.append('未知')
        goods_shop = goods_shop[0]
        # 商品链接
        link_str = li.xpath('.//div[@class="title-selling-point"]/a/@sa-data')[0]
        link_list = link_str.split(',')
        link_shop_id = num(link_list[2])
        link_prd_id = num(link_list[1])
        goods_link = 'https://product.suning.com/' + link_shop_id + '/' + link_prd_id + '.html'
        # 平台
        goods_platform = '苏宁'
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