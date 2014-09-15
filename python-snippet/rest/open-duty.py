import urllib2
import json
from xml.etree.ElementTree import XML 
import xml.dom.minidom

# conn = httplib.HTTPConnection("http://10.86.196.10:8001")
# args=urllib.urlencode({'username':'root', 'password':'toor'})
# headers={'Content-type':'application/json', 'Accept':'application/json'}
# r1 = conn.request("get", "/api/users", args)
# r2 = conn.getresponse()
# print r1,r2.status,r2.reason,r2
#    values = {"auth":{"passwordCredentials":{"username":"root","password":"toor"}}}
#    params = json.dumps(values)
#    headers = {"Content-Type":"application/json","Accept": "application/json"}
