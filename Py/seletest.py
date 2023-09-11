#import time
from selenium import webdriver
from selenium.webdriver.edge.service import Service
from selenium.webdriver.common.by import By
import random
from selenium.webdriver.support.select import Select
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.support import expected_conditions as EC
def fuck():
    wd.find_element(By.CSS_SELECTOR, r'#g_u > div:nth-child(2)').click()
    for i in range(0,random.randint(6, 10)):
        wd.find_element(By.CSS_SELECTOR, fr'#key4 > ul:nth-child({random.randint(1, 3)}) > li:nth-child({random.randint(1, 3)})').click()

    wd.find_element(By.CSS_SELECTOR, r'#g_p > div:nth-child(2)').click()
    for i in range(0,random.randint(6, 9)):
        wd.find_element(By.CSS_SELECTOR, fr'#key1 > ul:nth-child({random.randint(1, 3)}) > li:nth-child({random.randint(2, 8)})').click()

    wd.find_element(By.CSS_SELECTOR, r'#go').click()


for k in range(1,9999):
    print(f'第{k}组第0次开始')
    wd = webdriver.Edge()
    wd.get(r'http://qq.qqiis.tech/wd/shoy.php')
    fuck()
    print(f'第{k}组第0次完成')
    for j in range(1,20):
        wd.execute_script("window.open('');")
        wd.switch_to.window(wd.window_handles[j])
        wd.get(r'http://qq.qqiis.tech/wd/shoy.php')
        fuck()
        print(f'第{k}组第{j}次完成')
    wd.quit()

    #随机生成1到9的随机数
    
