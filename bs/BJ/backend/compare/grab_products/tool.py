from selenium.webdriver import ChromeOptions
from selenium.webdriver.chrome.service import Service
from selenium import webdriver
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.support import expected_conditions as EC
from selenium.webdriver.common.action_chains import ActionChains

# 提取字符串中的连续数字
def num(str_data):
    num_filter = filter(str.isdigit, str_data)
    num_list = list(num_filter)
    num_str = "".join(num_list)
    return num_str


# 无头浏览与规避检测
def web_driver():
    option = ChromeOptions()
    option.add_argument("--no-sandbox")
    option.add_argument("--disable-dev-shm-usage")
    option.add_argument("--disable-blink-features=ImagesEnabled")
    option.add_argument("--disable-javascript")
    option.add_experimental_option('excludeSwitches', ['enable-automation'])
    option.add_argument('--headless')
    option.add_argument('--disable-gpu')
    service = Service(executable_path='E:\Program Files\Google\Chrome\Application\chromedriver.exe')
    bro = webdriver.Chrome(service=service, options=option)
    return bro

# 添加点击元素的辅助函数
def safe_click(driver, element, timeout=10):
    try:
        # 等待元素可见
        WebDriverWait(driver, timeout).until(
            EC.visibility_of(element)
        )
        # 尝试使用 JavaScript 点击
        driver.execute_script("arguments[0].click();", element)
    except Exception as e:
        # 如果 JavaScript 点击失败，尝试其他方法
        try:
            # 滚动到元素位置
            driver.execute_script("arguments[0].scrollIntoView(true);", element)
            # 等待一下让页面稳定
            driver.implicitly_wait(1)
            # 使用 ActionChains 点击
            ActionChains(driver).move_to_element(element).click().perform()
        except Exception as e2:
            print(f"点击失败: {str(e2)}")
            raise