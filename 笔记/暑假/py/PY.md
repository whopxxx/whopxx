### py小技巧


发现一个讲解很细致的博客[枫枫知道](https://docs.fengfengzhidao.com/#/docs/python%E5%9F%BA%E7%A1%80/1-%E5%8F%98%E9%87%8F)

1. 创建二维数组

```python
arr = [i + 1 for i in range(5)]
# [1, 2, 3, 4, 5]

arr = [1e9 for i in range(5)]
# [1000000000.0, 1000000000.0, 1000000000.0, 1000000000.0, 1000000000.0]

arr = [[1, 5]] * 5
print(arr)
arr[0][1] = 10
print(arr)
# [[1, 5], [1, 5], [1, 5], [1, 5], [1, 5]]
# [[1, 10], [1, 10], [1, 10], [1, 10], [1, 10]]
```

2. 推导式
```python
1.列表
arr = ['wd' for i in range(5)]
# ['wd', 'wd', 'wd', 'wd', 'wd']

arr = [x ** 2 for x in range(5)]
# [0, 1, 4, 9, 16]

arr = [i for i in range(10) if i % 2 == 0]
# [0, 2, 4, 6, 8]

2.字典
dic = {k: 1 for k in range(1,6)}
# {1: 1, 2: 1, 3: 1, 4: 1, 5: 1}

3.集合
s = {i for i in range(5)}
# {0, 1, 2, 3, 4}

ps: 
这种方式生成的列表效率远远大于用for循环生成
```
3. 虚数使用
```python
v1 = 1 + 1j
print(abs(v1)) #取模
# 1.4142135623730951

s = set()
for x in range(3):
    for y in range(3):
        v = complex(x, y)
        s.add(v)
print(s)
# {0j, (1+0j), (2+0j), 1j, (1+1j), (2+1j), 2j, (1+2j), (2+2j)}

v = 2 + 3j
print(v.real)
print(v.imag)
# 2.0
# 3.0
```
4. pass和...
```python
def func():
    pass

def func2():
    ...

def func3(n:...) -> ...:
    ...

# 区别 pass 是关键字, ... 是对象
print(...) #Ellipsis
print(func3(...)) #None
```

5. help()函数
```python
# 函数文档
def exchange():
    """
    调用help()函数可以查看这里的内容
    """
    ...
help(exchange)
# Help on function exchange in module __main__:

# exchange()
#     调用help()函数可以查看这里的内容


def func():
    """
    这是注释
    """
    ...

help(func)
# Help on function func in module __main__:

# func()
#     这是注释

help(...)
help(math)
```
6. eval()函数
```python
# eval()函数 解析字符
print(eval("1*2*3*4")) #24

def func(n): 
    """
    实现阶乘
    """
    s = "*".join([str(i + 1) for i in range(n)])
    return eval(s)

print(func(5)) #120

print(eval('__import__("math").sin(3)')) #0.1411200080598672
# 可以偷偷执行代码
print('eval(__import__("os").system("..."))')
```
7. 元组拆包
```python
# 元组拆包
a, *b, c = (1, 2, 3, 4, 5, 6, 7)
print(a) # 1
print(b) # [2, 3, 4, 5, 6]
print(c) # 7

def f(*a, **b):
    print(a)
    print(b)

f()
# ()
# {}
f(1,2,3,dog = 12,cat = 14)
# (1, 2, 3)
# {'dog': 12, 'cat': 14}

```

8. 装饰器
```python
# 装饰器
from typing import Any


def robot(oldf):
    def newf():
        print("+++++++++")
        oldf()
        print("+++++++++")
    return newf

@robot #不带参数
def hello():
    print("hello world")

hello()
# +++++++++
# hello world
# +++++++++

def robot2(oldf):
    def newf(name): #新函数的形式要和旧函数保持一致
        print("+++++++++")
        oldf(name[::-1])
        print("+++++++++")
    return newf


@robot2 #带参数
def hello2(name:str):
    print(f"hellow {name}")

hello2("whopxx")
# +++++++++
# hellow xxpohw
# +++++++++


# eg: 计数器
def counter(oldf):
    count = 0
    def nwef(*arg, **kwargs):
        nonlocal count
        count += 1
        oldf(*arg, **kwargs)
        print(f"这个函数{oldf.__name__}运行了{count}次")
        ...
    return nwef

@counter
def hello3(name:str):
    print(f"hello {name}")

hello3("whopxx")
hello3("whopxx")
hello3("whopxx")

# hello whopxx
# 这个函数hello3运行了1次
# hello whopxx
# 这个函数hello3运行了2次
# hello whopxx
# 这个函数hello3运行了3次


# 保护器
def shield(oldf):
    def newf(*arg, **kwargs):
        try:
            res = oldf(*arg, **kwargs)
            return res
        except Exception as e:
            print(f"函数{oldf.__name__}出错了",oldf, e)
            return None
    return newf
@shield
def hello4():
    print(a)
hello4() # 函数hello4出错了 <function hello4 at 0x00000252554531C0> name 'a' is not defined



# 完整装饰器
def robo2(oldf):
    def newf(*arg, **kwargs):
        print("~~~~")
        res = oldf(*arg, **kwargs)
        return res
    return newf

@robo2
def add(a, b):
    return a + b
print(add(3, 4))
# ~~~~
# 7


# ps:可以多种同时装饰


# 类装饰器
class Check(object):
    def __init__(self, fn):
        self.__fn = fn #初始化
    def __call__(self, *args: Any, **kwds: Any) -> Any:
        print("请登录...")
        self.__fn()

@Check # ==> comment = Check(comment)
def comment():
    print("正在发表评论")
comment()
comment()
# 请登录...
# 正在发表评论
# 请登录...
# 正在发表评论
```

9. 极速递归
```python
# 提高递归效率 极速递归
from functools import lru_cache

@lru_cache
def f(n):
    if n == 1:
        return 1
    if n == 2:
        return 1
    else :
        return f(n - 1) + f(n - 2)

for i in range(1,100):
    print(i, f(i))

# 瞬间递归出结果
# ...
# 95 31940434634990099905
# 96 51680708854858323072
# 97 83621143489848422977
# 98 135301852344706746049
# 99 218922995834555169026
```
10. 字典计时器
```python
# 字典计数器
from collections import Counter
s = "889988998989898"
c = Counter(s)
print(c)
# Counter({'8': 8, '9': 7})
```

11. 小技巧
```python
# 三目运算符
a = 15
print("y") if a == 15 else print("n") # y

# 翻转数组
arr = [1,2,3,4]
print(arr[::-1])

# enumerate 获得索引
arr = ['a','b','c','d','e']
for i, n in enumerate(arr, start= 1):
    print(i, n, end="|")
# 1 a|2 b|3 c|4 d|5 e|
```
12. 自定义排序
```python
# 自定义排序
arr = [(2, 1), (1, 1), (3, 2), (4, 2), (6, 1), (4, 1)]
print(sorted(arr))
# [(1, 1), (2, 1), (3, 2), (4, 1), (4, 2), (6, 1)]

arr.sort(reverse=True)
print(arr)
# [(6, 1), (4, 2), (4, 1), (3, 2), (2, 1), (1, 1)]

from functools import cmp_to_key
def cmp(a, b):
    """
    return -1 b > a
    return 1  a > b
    return 0 a == b
    """
    if a[0] < b[0]:
        return 1
    elif a[0] > b[0]:
        return -1
    else :
        if a[1] > b[1]:
            return 1
        elif a[1] < b[1]:
            return -1
        else :
            return 0

arr.sort(key=cmp_to_key(cmp))
print(arr)
# [(6, 1), (4, 1), (4, 2), (3, 2), (2, 1), (1, 1)]
```
13. 数字的花式写法
```py
# 数字的花式写法
a = 3_000_000_000
a = .5
a = 0.
a = 1e5 # float
a = 10 ** 5 # int
print(1e30 + 1 == 1e30) # True 精度损失
print(1e309) # inf
```
14. 异常处理
```py
import traceback

def f():
    print(1/0)
try:
    f()
except ValueError:
    ...
except NameError:
    ...
except Exception as e:
    print(e)
    # traceback.print_exc() # 更全面
else:
    ...
finally:
    ...

# division by zero
```
15. 二进制枚举和组合数
```py
# 二进制枚举
def func():
    s = ["aa", "bb", "cc", "dd"]
    for n in range(len(s) ** 2):
        th = []
        for i in range(len(s)):
            res = n >> i & 1
            if res == 1:
                th.append(s[i])
        print(th)

func()

from itertools import combinations
def func2():
    s = ["aa", "bb", "cc", "dd"]
    for item in combinations(s, 2):
        print(item)

func2()
# ('aa', 'bb')
# ('aa', 'cc')
# ('aa', 'dd')
# ('bb', 'cc')
# ('bb', 'dd')
# ('cc', 'dd')
```
16. 多层循环压行
```py
import itertools
for x, y, z in itertools.product(range(10),range(10),range(10)):
    if x == y and x == 2:
        break
    print(x,y,z)
```

17. any() 和 all()
```py
# any() 和 all()

print(any([0,0,0,0,0,1])) # True
print(all([1,1,1,1,0,1])) # False

# any() 判断有无T
# all() 判断有无F
```
18. 身份运算符is/is not
```py
a = [1, 2, 3]
b = [1, 2]
print(id(a)) #1448936217856
print(id(b)) #1448936292736
b.append(3)
print(a == b) # True
print(a is b) # False
```

19. 生成器
```py
# 生成器
# 1. yield 替换 return

def counter():
    now = 0
    while now <= 3:
        yield now
        now += 1
f = counter()
for i in f:
    print(i)
# 0
# 1
# 2
# 3
next(f)
# StopIteration

# 2. 生成器表达式
t = (i ** 2 for i in range(3))
for i in t:
    print(i)
# 0
# 1
# 4
```
20. lambda表达式
```py
# lambda表达式
# lambda arg1, arg2, arg3, ... argN : expression

def func(x):
    return x * x
print(func(3))

# 等价于
f = lambda y : y * y
print(f(3))

# 应用
y = [lambda x : x * x, 2, 3]
print(y[0](y[1])) # 4
print(y[0](y[2])) # 9
```
21. 文件操作
```py
# 文件操作1
f = open('first.txt', 'r+')
f.write('i love u')
f.close()
"""
打开文件时,使用'r+'模式会将文件的读写指针放在文件的开头。
在调用f.write('i love u')时,会将文本写入文件的开头位置,
从而覆盖了原来的内容。如果想要在文件末尾添加内容而不覆盖原文件,
可以使用'a'模式打开文件,即f = open('first.txt', 'a')。
这样在调用f.write('i love u')时,将会在文件末尾添加内容而不会覆盖原文件。
记得最后使用f.close()关闭文件。
来自gpt
"""
# 等价于:
with open('first.txt', 'r+')as f:
    f.write('i love u')
# 注意r+从头开始覆盖原文件内容

```
22. 文件操作2
```py
# 文件操作
from pathlib import Path
print(Path.cwd()) # cwd()获得当前工作目录
# cwd : current working directory
p = Path("D:\Web") # 指定路径
print(p)
# D:\Web
# D:\Web
q = p / 'first.txt' # 添加路径
print(q)
# D:\Web\first.txt
print(p.is_dir()) # T
print(q.is_dir()) # F
# is_dir() 判断一个路径是否为文件夹
print(p.is_file()) # F
print(q.is_file()) # T
# is_file() 判断一个路径是否为文件
print(Path('D:/shabi').exists()) # F
print(q.exists()) # T
# exists() 判断路径是否存在
print(q.stem) # first
print(q.suffix) # .txt
# .stem 获得文件名 .suffix 获得文件后缀
print(q.name) # first.txt
# .name 获取路径的最后一部分
print(q.parent) # D:\Web
print(p.parent) # D:\
# 获取父级目录
t = q.parents
for i in t:
    print(i)
# D:\Web
# D:\
# 所有父级目录
...
```
23. 文件操作3
```py
# 文件操作3
import pickle
"""
pickle是Python中的一个模块,用于将Python对象序列化和反序列化。
它的主要作用是实现对象的持久化存储和传输。
具体来说,pickle模块可以将Python对象转化为二进制数据流(序列化),
并将其保存到文件或者将其发送到网络。
反之,它可以从文件或网络中读取二进制数据流,
并将其转化为Python对象(反序列化)。
gpt
"""
x = [1,2,3,4,5]
y = ['a', 'b', 'c']
z = ['i', 'love', 'u']
with open('tmp.dlk', 'wb') as f:
    pickle.dump((x,y,z),f) # 存入

with open('tmp.dlk', 'rb') as f:
    a, b, c = pickle.load(f) # 读取
print(a, b, c, sep = '\n')
# [1, 2, 3, 4, 5]
# ['a', 'b', 'c']
# ['i', 'love', 'u']
```
24. 异常处理
```py
# exception异常
"""
try:
    # 可能会引发异常的代码
except ExceptionType:
    # 处理捕获的异常的代码

在except语句中,ExceptionType是要捕获的异常类型。
如果发生了这个类型的异常,相应的except块就会执行。
如果没有指定具体的异常类型,那么except块将捕获所有异常。

except ExceptionType as e:捕获异常并将其赋值给变量e,以便在except块中进行进一步处理。
except (ExceptionType1, ExceptionType2):捕获多个异常类型。
except ExceptionType1 as e1, ExceptionType2 as e2:捕获多个异常类型,并将它们分别赋值给变量e1和e2。

gpt
"""
try:
    print(1/0)
except:
    print('error')
# error

try:
    print(1/1)
except:
    print('error')
# 1.0

try :
    1/0
except ZeroDivisionError as e:
    print(e) 
# division by zero
```
25. 异常处理2
```py
# exception异常2
"""
try-except-else
"""
try:
    1/0
except:
    print("逮到了")
else:
    print("没逮到")
finally:
    print("逮没逮到都会执行")
# 到了
# 逮没逮到都会执行

"""
try:
    # 可能会引发异常的代码
except ExceptionType:
    # 处理捕获的异常的代码
finally:
    # 收尾
"""
```
26. 最小类模拟字典 
```py
# 最小类模拟字典
class C:
    ...
c = C()
c.x = 1
c.y = 'u'
c.z = [1, 2, 3, 4]
print(c.x, c.y, c.z)
# 1 u [1, 2, 3, 4]
```
