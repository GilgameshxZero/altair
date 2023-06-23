import base64
print(base64.b64decode(__file__.split('/')[-1][:-3].encode()).decode())