# -*- coding: utf8 -*-
import requests
from requests.auth import HTTPBasicAuth
from requests.auth import HTTPDigestAuth

url = 'http://127.0.0.1:9001/astyop/open-api/newyear/2021'
res = requests.get(url, auth=HTTPDigestAuth('user', 'astyop'))

print(res)
