0. opp
```py
# 封装
"""
封装(Encapsulation): 封装是指将数据和操作数据的方法进行封装,在一个类
中将相关的数据和方法组织在一起。通过封装可以隐藏数据的具体实现细节,只公
开必要的接口供外部访问和使用。封装提供了数据的安全性和组织性,同时也方便
了代码的维护和扩展。
"""

# 继承
"""
继承(Inheritance): 继承是指通过定义一个新的类去继承（包含）一个已存在
的类的特性和行为。被继承的类称为父类或基类,新定义的类称为子类
或派生类。子类会继承父类的属性和方法,同时也可以在子类中新增属性
和方法,或对已继承的属性和方法进行重写或修改。继承实现了代码的重用性,
可以减少代码的冗余，并且提供了多态的基础。
"""

# 多态
"""
多态(Polymorphism): 多态性是指同一个方法或操作可以在不同的对象上产生不同的
行为。多态性可以通过继承和接口实现。在继承中,子类可以重写父类的方法,从而实现
相同的方法产生不同的行为。多态性提高了代码的灵活性和可扩展性,使得程序可以根据
上下文的不同选择相应的方法。
"""
```

1. 类
```py
class cat:
    def __init__(self,name):
        self.name = name
    def eat(self):
        print(f"{self.name}嘎嘎吃")
    def drink(self):
        print(f"{self.name}嘎嘎喝")



def main():
    a = cat("Tom")
    a.eat()
    a.drink()
    # Tom嘎嘎吃
    # Tom嘎嘎喝

if __name__ == "__main__":
    main()
```

2. 封装
```py
class gun:
    def __init__(self, name):
        self.name = name # 枪名
        self.bullet = 0 #子弹数
    def add_bullet(self, count):
        self.bullet += count
    def shoot(self):
        if self.bullet <= 0:
            print("[%s]没有子弹了..." % self.name)
            return
        self.bullet -= 1
        print("[%s]突突突...[%d]" % (self.name , self.bullet))

class soldier:
    def __init__(self, name):
        self.name = name
        self.gun = None # 初始没用枪
    def fire(self):
        if self.gun is None:
            print("[%s]还没有枪" % self.name)
            return
        print("冲啊...[%s]" % self.name)
        self.gun.add_bullet(10)
        self.gun.shoot()


def main():

    a = gun("ak47")
    a.add_bullet(2)
    a.shoot() # [ak47]突突突...[1]
    a.shoot() # [ak47]突突突...[0]
    a.shoot() # [ak47]没有子弹了...
    xu = soldier("许三多") # None
    xu.fire()
    print(xu.gun)
    xu.gun = a
    print(xu.gun) # <__main__.gun object at 0x000001FC69023EB0>
    xu.fire() 
    # 冲啊...[许三多]
    # [ak47]突突突...[9]
if __name__ == "__main__":
    main()
```
3. 私有属性和方法
```py
# oop精髓 
"""
私有属性和私有方法(不希望对外公开)
在定义时属性名或属性方法前加两个下划线__
"""
class women:
    def __init__(self, name) -> None:
        self.name = name
        self.__age = 18
    def secret1(self):
        print("%s 的年龄是 %d" % (self.name, self.__age))
    def __secret(self):
        print("%s 的年龄是 %d" % (self.name, self.__age))

xiaofang = women("小芳")
xiaofang.secret1() # 小芳 的年龄是 18
print(xiaofang.__age) # AttributeError: 'women' object has no attribute '__age' 私有属性不能再外界直接访问
xiaofang.__secret() # AttributeError: 'women' object has no attribute 'secret'

class A:
    def __init__(self, x) -> None:
        self.__x = x
a = A(250)
print(a._A__x) #250
print(a.__dict__) # {'_A__x': 250}
print(a.__x) # AttributeError: 'A' object has no attribute '__x'
# 访问方法 ._类名__属性

```
4. 继承
```py
# 继承
class A():
    x = 520
    def hello(self):
        print("nihao")
class B(A):
    ...

b = B()
print(isinstance(b, A)) # True b是A的子类
print(isinstance(b, B)) # True b是B的子类

## 多重继承

class C:
    ...
class D(A, C):
    ...
d = D()
d.hello() # nihao 最左边优先
```
5. 构造
```py
# 构造函数
class C:
    def __init__(self, x, y) -> None:
        self.x = x
        self.y = y
    def add(self):
        return self.x + self.y
c = C(2,3)
print(c.__dict__)
# {'x': 2, 'y': 3}
# =====================================
# 重写 覆盖
class D(C):
    def __init__(self, x, y, z) -> None:
        C.__init__(self, x, y)
        self.z = z
    def add(self):
        return C.add(self) + self.z
d = D(2,3,4)
print(d.add()) # 9

# =====================================
class Parent:
    def __init__(self, name):
        self.name = name

    def greet(self):
        print("Hello, I'm", self.name)

class Child(Parent):
    def __init__(self, name, age):
        super().__init__(name)  # 调用父类的构造函数
        self.age = age

    def greet(self):
        super().greet()  # 调用父类的greet方法
        print("I'm", self.age, "years old")

child = Child("Alice", 10)
child.greet()
```

6. 节省空间
```py
"""
舍得之道

__slots__()是在Python中用于限制对象属性的特殊方法。
它可以用于自定义类,以指定类的实例只能具有特定的属性。

通常情况下,Python对象的属性可以随时动态地添加、修改和删除。
然而,有时我们希望在定义类时限制对象的属性,以避免意外的属性赋值或节省内存空间。

使用__slots__()方法,您可以定义一个属性名称的列表,将允许的属性名称限制在这个列表中。
这样一来,该类的实例只能具有这些属性,任何其他属性都将引发AttributeError异常。

"""
class Person:
    __slots__ = ['name', 'age']
    
    def __init__(self, name, age):
        self.name = name
        self.age = age

person = Person('Alice', 25)
person.name  # 输出: 'Alice'
person.age   # 输出: 25

person.address = '123 Main St'  # 试图添加一个未在__slots__中定义的属性
# 引发 AttributeError: 'Person' object has no attribute 'address'

"""
需要注意的是,__slots__()方法只对当前类的实例起作用,不影响子类的实例。
如果子类也想使用属性限制,需要在子类中重新定义__slots__()方法。
"""
```
7. 导入模块的方法
```py
# 导入模块
"""hello.py
def say():
    print("hello, i love u")
"""

# 1
import hello 
hello.say() #hello, i love u

# 2
from hello import say
# from hello import * 这样导入注意名字冲突,如果冲突会覆盖
say() #hello, i love u

# 3
import hello as e # 重命名
e.say() # hello, i love u
```
8. 包
```py
# 导入包
"""
-PK #文件夹#
   __init__.py #py文件#  # 导入包会自动调用该函数
    import PK.hello # 所以可以提前在这里导入
    print("我被调用啦")
   hello.py #py文件#
    def say():
        print("hello")
"""
import PK # __init__.py中导入过其他的模块
# import PK.hello
PK.hello.say()
# 我被调用啦
# hello
```
9. `__all__`()属性
```python
"""
`__all__`是一个特殊的变量（也可以是一个列表或元组），用于定义模块中可被导入的公开接口（公开的变量、函数或类）。

在Python中，以双下划线开头和结尾的名称通常具有特殊的含义。`__all__`用于定义模块中的公共接口，以告诉解释器哪些对象是该模块的公开API，可以被其他模块导入使用。

示例用法如下：
"""
# example.py

def public_function():
    pass

def _private_function():
    pass

public_variable = 123
_private_variable = 456

__all__ = ['public_function', 'public_variable']
"""
在上述示例中，`public_function`、`public_variable`是希望被其他模块导入使用的公开接口，而`_private_function`、`_private_variable`是不希望被外部模块直接访问的内部对象。

当其他模块导入`example`模块时，只有在`__all__`列表中列出的对象会被导入。如果没有定义`__all__`变量，则默认情况下，所有以非下划线开头的名称都被视为公开接口。

请注意，尽管在约定上`__all__`是一个列表，但实际上它可以是任何可迭代对象，例如元组。
"""
# GPT
```
# 继续在无涯的雪海中挣扎吧！