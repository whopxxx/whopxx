- requests库
---
```python
pip intstall requests

requests.get/post(url, data, params, headers, timeout)

url: 要下载的目标网页的URL

data: 字典或字符串，一般用于POST方法时提交的数据

params: 用于传递参数的变量、选项或数据结构

headers: 设置user-agent,refer等请求头
 
timeout: 超时时间(单位是秒)
```

```python
import  requests
r = requests.get/post(url) # 接收response响应

r.status_code # 查看状态码，200代表成功

r.encoding # 可以查看当前编码，以及更改编码

r.text # 查看返回的页面内容

r.headers # 查看返回的HTTP的headers

r.url # 查看实际访问的URL

r.content # 以字节的方式返回内容，比如用于下载图片

r.cookies # 服务器端要写入本地的cookies数据
```
---
- Beautiful Soup语法
---
```python
# Beatuiful Soup

# 创建BeautifulSoup对象
from bs4 import BeautifulSoup
soup = BeautifulSoup(
    html_doc,               # HTML文档字符串(text)
    'html.parser',          # HTML解析器
    from_encoding='utf8'    # HTML文档的编码
)

# 搜索节点(find_all, find)
# 方法: find_all(name, attrs=, string)

# 查找所有标签为a的节点
soup.find_all('a')

# 查找所有标签为'a', 链接符合/view/123.html形式的节点
soup.find_all('a', href='/view/123.html')

# 查找所有标签为div, class为abc, 文字为Python的节点
soup.find_all('div', class_='abc', string='Python')
soup.find_all('div', attrs={"class": "abc"})

# 访问节点信息
# 得到节点: <a href='1.html'>Python</a>

# 获取查到的节点的标签名称
soup.name

# 获取查到的a节点的href属性
soup['href']

# 获取查到的a节点的链接文字
soup.get_text
```
---

1. 爬取豆瓣top250电影名
```py
import requests
from bs4 import BeautifulSoup
headers = {
    "User-Agent": "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/114.0.0.0 Safari/537.36 Edg/114.0.1823.86"
}
for num in range(0, 250, 25):
    print(num)
    response = requests.get(f"https://movie.douban.com/top250?start={num}", headers=headers)
    html = response.text
    soup = BeautifulSoup(html, "html.parser")
    titles = soup.findAll("span", attrs={"class": "title"})
    for title in titles:
        s = title.string
        if '/' not in s:
            print(s)
```
2. URL管理器
```python
# url_manager.py
# URl管理器
class UrlManager():
    """
    url 管理器
    """
    def __init__(self):
        self.new_urls = set()
        self.old_urls = set()

    def add_new_url(self, url):
        if url is None or len(url) == 0:
            return
        if url in self.new_urls or url in self.old_urls:
            return
        self.new_urls.add(url)

    def add_new_urls(self, urls):
        if urls is None or len(urls) == 0:
            return
        for url in urls:
            self.add_new_url(url)

    def get_url(self):
        if self.has_new_url():
            url = self.new_urls.pop()
            self.old_urls.add(url)
        else:
            return None

    def has_new_url(self):
        return len(self.new_urls) > 0


if __name__ == "__main__":   # 测试样例
    url_manger = UrlManager()

    url_manger.add_new_url("url1")
    url_manger.add_new_urls(["url1", "uurl2", "url3"])
    print(url_manger.new_urls, url_manger.old_urls)

    print("$-----$")
    url_manger.get_url()
    print(url_manger.new_urls, url_manger.old_urls)

    print("$-----$")
    url_manger.get_url()
    print(url_manger.new_urls, url_manger.old_urls)

    print("$-----$")
    url_manger.get_url()
    print(url_manger.new_urls, url_manger.old_urls)
```
3. Beautifulsoup使用
```python
from bs4 import BeautifulSoup

with open("../HTML/demo.html", encoding="utf-8") as fin:
    html_doc = fin.read()

soup = BeautifulSoup(html_doc, "html.parser")

links = soup.findAll("a")
for link in links:
    print(link.name, link["href"], link.getText())
    # ["href"]这是获得href属性值，getText()是文本内容

"""
a https://www.baidu.com 百度
a https://www.crazyant.net 疯狂的蚂蚁
a https://www.iqiyi.com 爱奇艺
"""

div_node = soup.findAll("div", attrs={"id": "content"})
print(div_node)
"""
[<div class="default" id="content">
<p>段落</p>
<a href="https://www.baidu.com">百度</a><br/>
<a href="https://www.crazyant.net">疯狂的蚂蚁</a><br/>
<a href="https://www.iqiyi.com">爱奇艺</a>
</div>]
"""
```
```html
<!--demo.html-->
<html>
<head>
    <meta http-equiv="Content-Type" content="text/html;charset=utf-8">
    <title>网页标题</title>
</head>
<body>
  <h1>1</h1>
  <h2>2</h2>
<div id = "content" class="default">
  <p>段落</p>
  <a href="https://www.baidu.com">百度</a><br/>
  <a href="https://www.crazyant.net">疯狂的蚂蚁</a><br/>
  <a href="https://www.iqiyi.com">爱奇艺</a>
</div>
</body>
</html>
```
4. 实战1-爬取近几年天气数据
```python
# 爬取天气
import requests
import pandas as pd
url = "https://tianqi.2345.com/Pc/GetHistory"
headers = {
    "User-Agent": "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/114.0.0.0 Safari/537.36 Edg/114.0.1823.86"
}


def craw_table(year, month):
    params = {
        "areaInfo[areaId]": 71653,
        "areaInfo[areaType]": 2,
        "date[year]": year,
        "date[month]": month
    }
    response = requests.get(url, headers=headers, params=params)
    data = response.json()["data"]
    # ["data"] 是对返回的 JSON 对象进行字典访问，提取其中名为 “data” 的键对应的值。

    # data frame
    df = pd.read_html(data)[0]
    # [0] 表示取返回列表中的第一个表格。

    return df
    # print(df.head())
    # df.head() 是 Pandas DataFrame 对象的一个方法调用，它用于显示 DataFrame 的前几行数据，默认情况下是显示前 5 行。


# df = craw_table(2018, 3)
# print(df)

df_list = []
for year in range(2018, 2023):
    for month in range(1, 13):
        print("爬取:", year, month)
        df = craw_table(year, month)
        df_list.append(df)

pd.concat(df_list).to_excel("西安近几年天气.xlsx", index=False)
"""
在你的代码示例中，pd.concat(df_list) 是使用 Pandas 库的 concat() 函数进行 DataFrame 的连接操作。
df_list 是一个包含多个 DataFrame 对象的列表。concat(df_list) 将这些 DataFrame 对象按行连接为一个新的 DataFrame。
接着，.to_excel("西安近几年天气.xlsx", index=False) 将连接后的 DataFrame 保存为 Excel 文件。
index=False 参数用于指示不将 DataFrame 的索引写入 Excel 文件。
"""
```

