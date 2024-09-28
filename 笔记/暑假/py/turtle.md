# turtle库--[海龟绘图](https://docs.python.org/zh-cn/3/library/turtle.html)

## start: 

1. `import turtle`:这种导入在引用时需要`turtle.函数`

2. `form turtle import *`:这种导入直接用函数名


## `turtle.mainloop()`

Another step is also required though - as soon as the script ends, Python will also close the turtle's window. Add:

> `t.mainloop()`

to the end of the script. The script will now wait to be dismissed and will not exit until it is terminated, for example by closing the turtle graphics window.

具体操作见文档