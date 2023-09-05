import uiautomator2 as u2
import time
import re

def click_xpah(xpath):
    # 等待元素出现
    result = re.compile(r'\"(.*?)\"').findall(xpath)[0]
    d(resourceId=fr'{result}').wait(timeout=20)
    # 点击按钮
    d.xpath(xpath).click()
def wait_xpath(xpath):
    result = re.compile(r'\"(.*?)\"').findall(xpath)[0]
    if d(resourceId=result).exists:
        pass
    else:
        time.sleep(0.5)
        wait_xpath(xpath)

print(time.strftime('%Y-%m-%d %H:%M:%S', time.localtime()))
# 连接到Android设备
d = u2.connect('a784f35e')
print('设备连接成功')

# 初始化
d.app_stop('com.lptiyu.tanke')
d.app_stop('com.lerist.fakelocation')
d.app_stop('com.fakehost.fl')

# 打开fakehost
d.app_start('com.fakehost.fl')
print('打开fakehost')
click_xpah('//*[@resource-id="com.fakehost.fl:id/button_start_vpn"]')
print('fakehost加载')

# 打开fakelocation
d.app_start('com.lerist.fakelocation')
print('打开fakelocation')
time.sleep(2)
d.click(0.061, 0.072)
click_xpah('//*[@resource-id="com.lerist.fakelocation:id/f_fakeloc_tv_current_address"]')
click_xpah('//*[@resource-id="com.lerist.fakelocation:id/f_route_tv_service_switch"]')
for j in range(0,99):
    if d(resourceId="com.lerist.fakelocation:id/f_route_tv_service_pause").exists and d.xpath('//*[@resource-id="com.lerist.fakelocation:id/f_route_tv_service_pause"]').text == '暂停':
        print('模拟路线服务开启成功', end='\r')
        break
    else:
        print(f'等待开启模拟路线服务 等待次数={j}', end='\r')
        click_xpah('//*[@resource-id="com.lerist.fakelocation:id/f_route_tv_service_switch"]')
        time.sleep(1)

# 打开乐跑
d.app_start('com.lptiyu.tanke')
print('\n打开乐跑')
click_xpah('//*[@resource-id="android.miui:id/app1"]/android.widget.FrameLayout[1]')# 选择第一个应用
click_xpah('//*[@resource-id="com.lptiyu.tanke:id/tv_enterRun"]')
click_xpah('//*[@resource-id="com.lptiyu.tanke:id/dialog_confirm"]')#自由跑
print('开始跑步')
wait_xpath('//*[@resource-id="com.lptiyu.tanke:id/tv_distance_value"]')# 等待元素出现
time.sleep(4)
for i in range(0,9999999999):
    maxmin=0
    distance=d.xpath('//*[@resource-id="com.lptiyu.tanke:id/tv_distance_value"]').text
    pace=d.xpath('//*[@resource-id="com.lptiyu.tanke:id/tv_speed_value"]').text
    ti_me=d.xpath('//*[@resource-id="com.lptiyu.tanke:id/chronometer"]').text
    min=d.xpath('//*[@resource-id="com.lptiyu.tanke:id/chronometer"]').text.split(sep=':')[1]
    print(f'距离{distance} 配速{pace} 用时{ti_me} maxmin={maxmin}      ', end='\r')

    d.click(0.5, 0.5)
    if int(min)>=maxmin:
        print('\n跑步完成')
        break
    else:
        time.sleep(1)
time.sleep(1)
print('正在滑动结束')
d.swipe(0.441, 0.949, 0.442, 0.950 ,duration=3)# 长按结束跑步
click_xpah('//*[@resource-id="com.lptiyu.tanke:id/tv_stoprun"]')
click_xpah('//*[@resource-id="com.lptiyu.tanke:id/dialog_confirm"]')
print('#完成#')

#关闭服务
time.sleep(3)
d.app_stop('com.lerist.fakelocation')
d.app_stop('com.fakehost.fl')
print('服务扫尾')
print(time.strftime('%Y-%m-%d %H:%M:%S', time.localtime()))