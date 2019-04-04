#!/usr/bin/python
# -*- coding: utf-8 -*-
import json, urllib.request
from urllib.parse import urlencode


# ----------------------------------
# 作文大全调用示例代码 － 聚合数据
# 在线接口文档：http://www.juhe.cn/docs/187
# ----------------------------------

def main():
    # 配置您申请的APPKey
    appkey = "e5d14e2c15608b401dea8e61b82045da"

    # 1.作文分类列表
    request1(appkey, "GET")

    # 2.作文基本信息列表
    request2(appkey, "GET")

    # 3.作文内容接口
    request3(appkey, "GET")


# 作文分类列表
def request1(appkey, m="GET"):
    url = "http://zuowen.api.juhe.cn/zuowen/typeList"
    params = {
        "key": appkey,  # 您申请的APPKEY
        "id": "",  # 1为年级，2为题材，3为字数，4为等级

    }
    params = urlencode(params)
    if m == "GET":
        f = urllib.request.urlopen(str(url), str(params))
    else:
        f = urllib.request.urlopen(str(url), str(params))

    content = f.read()
    print(content)
    res = json.dumps(content)
    if res:
        error_code = res["error_code"]
        if error_code == 0:
            # 成功请求

            print(res["result"])
        else:
            print(
                "%s:%s" % (res["error_code"], res["reason"]))
    else:
        print(
            "request api error")


# 作文基本信息列表
def request2(appkey, m="GET"):
    url = "http://zuowen.api.juhe.cn/zuowen/baseList"
    params = {
        "key": appkey,  # 您申请的APPKEY
        "gradeId": "",  # 年级id
        "typeId": "",  # 题材id
        "wordId": "",  # 字数id
        "level": "",  # 等级id
        "page": "",  # 页数

    }
    params = urlencode(params)
    if m == "GET":
        f = urllib.request.urlopen("%s?%s" % (url, params))
    else:
        f = urllib.request.urlopen(url, params)

    content = f.read()

    res = json.loads(content)
    if res:
        error_code = res["error_code"]
        if error_code == 0:
            # 成功请求
            print(
                res["result"])
        else:
            print(
                "%s:%s" % (res["error_code"], res["reason"]))
    else:
        print(
            "request api error")


# 作文内容接口
def request3(appkey, m="GET"):
    url = "http://zuowen.api.juhe.cn/zuowen/content"
    params = {
        "key": appkey,  # 您申请的APPKEY
        "id": "",  # 作文id

    }
    params = urlencode(params)
    if m == "GET":
        f = urllib.request.urlopen("%s?%s" % (url, params))
    else:
        f = urllib.request.urlopen(url, params)

    content = f.read()
    res = json.loads(content)
    if res:
        error_code = res["error_code"]
        if error_code == 0:
            # 成功请求
            print(res["result"])

        else:
            print("%s:%s" % (res["error_code"], res["reason"]))

    else:
        print("request api error")


if __name__ == '__main__':
    main()
