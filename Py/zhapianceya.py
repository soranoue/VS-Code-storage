import requests
import random
import string
import time

for i in range(1,99999999999):
    u=random.randint(100000000, 9999999999)
    p=''.join(random.choice(string.ascii_letters + string.digits) for _ in range(random.randrange(9, 11)))
    headers = {'Accept':'application/json, text/javascript, */*; q=0.01','Accept-Encoding':'gzip, deflate','Accept-Language':'zh-CN,zh;q=0.9,en;q=0.8,en-GB;q=0.7,en-US;q=0.6','Cache-Control':'no-cache','Connection':'keep-alive','Cookie':'PHPSESSID=r5put3rskt7u1l4t4tfqt7deg3','Host':'qq.qqiis.tech','Pragma':'no-cache','Referer':'http://qq.qqiis.tech/wd/shoy.php','User-Agent':'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/116.0.0.0 Safari/537.36 Edg/116.0.1938.62','X-Requested-With':'XMLHttpRequest'}
    response = requests.get(f'http://qq.qqiis.tech/status.php?action=add&u={u}&p={p}&id=&system_str=PC', headers=headers)
    # time.sleep(0.002)
    print(f'第{i}次 账号{u} 密码{p} {response.text}')
    