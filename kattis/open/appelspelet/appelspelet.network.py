import requests
r = requests.get('https://httpbin.org/basic-auth/user/pass', auth=('user', 'pass'))
if r.status_code == 200:
    print("alf")
else:
    print("beata")
