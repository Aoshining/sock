from msedge.selenium_tools import EdgeOptions
from msedge.selenium_tools import Edge

# 提取字符串中的连续数字
def draw_num(str_data):
    """
    :param str_data: 字符串类型
    :return: 只含数字的字符串
    """
    num_filter = filter(str.isdigit, str_data)
    num_list = list(num_filter)
    num_str = "".join(num_list)
    return num_str


# 无头浏览与规避检测
def avoid_check():
    """
    :return: 浏览器窗口
    """
    option = EdgeOptions()
    option.use_chromium = True
    option.add_experimental_option('excludeSwitches', ['enable-automation'])
    option.add_argument('--headless')
    option.add_argument('--disable-gpu')
    bro = Edge(options=option)
    return bro