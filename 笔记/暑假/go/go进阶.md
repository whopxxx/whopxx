# go并发编程
## Goroutine(协程)
第一次了解这些东西，对这里有很多的名词概念还不是很清除

协程（Coroutine）和线程（Thread）是两种并发执行的概念

协程: 用户态，轻量级线程，栈KB级别
线程: 内核态，线程跑多个协程，栈MB级别

> 我们只需要使用`go`关键字就可以开启goroutine

格式：`go 函数名(参数列表)`


用go语句我们可以实现开启一个新的运行期线程，以一个不同的、新创建的goroutine来执行函数。*同一个程序中的所有goroutine共享同一个地址空间*。

示例:
```go
package main

import (
	"fmt"
	"time"
)

func hello(i int) {
	println("hello goroutine : " + fmt.Sprint(i))
}

func main() {
	for i := 0; i < 5; i++ {
		go func(j int) { //匿名函数
			hello(j)
		}(i)
	}
	time.Sleep(time.Second)
}
```
输出:
hello goroutine : 2
hello goroutine : 3
hello goroutine : 4
hello goroutine : 0
hello goroutine : 1

输出是没有固定的先后顺序的，因为这是几个协程在独立执行

## Channle(通道)
通道（channel）是用来传递数据的一个数据结构。
通道是一种用于在 goroutine 之间进行通信和同步的机制。通过使用通道，可以让一个 goroutine 向另一个 goroutine 发送数据或接收数据。
操作符 `<-` 用于指定通道的方向，发送或接收。如果未指定方向，则为双向通道。

创建方式:
`make(chan 元素类型,[缓冲大小])`

两种类型:
- 无缓冲通道   `make(chan int)` 
- 有缓冲通道   `make(chan int, 2)`

下面是具体使用示例:
无缓冲
```go
ch := make(chan int) // 创建一个无缓冲通道

// 发送操作和接收操作都会阻塞当前 Goroutine
ch <- 42 // 发送数据到通道
x := <-ch // 从通道接收数据
```
有缓冲
```go
ch := make(chan int, 3) // 创建一个容量为 3 的有缓冲通道

// 发送操作不会阻塞，直到通道存满
ch <- 42
ch <- 100
ch <- 200

// 接收操作不会阻塞，直到通道为空
x := <-ch
y := <-ch
z := <-ch
```

示例:
```go
package main

func Cal() {
	src := make(chan int)
	dest := make(chan int, 5)
	go func() {
		defer close(src)
		for i := 0; i < 10; i++ {
			src <- i
		}// 子协程发送0~9数字
	}()
	go func() {
		defer close(dest)
		for i := range src {
			dest <- i * i
		} // 子协程计算输入数字的平方
	}()
	for i := range dest {
		// 复杂操作
		println(i)// 主协程输出最后的平方数
	}
}

func main() {
	Cal()
}
```

`close(channle)`： 用于关闭一个通道

`defer`：Go 函数的关键字 defer 可以提供注册多个延迟调用，只能出现在函数内部，在 defer 归属的函数即将返回时，将延迟处理的语句按 defer 的逆序进行执行，这些调用遵循先进后出的顺序在函数返回前被执行。也就是说，先被 defer 的语句最后被执行，最后被 defer 的语句，最先被执行。

defer 常用于保证一些资源最终一定能够得到释放或者回收。


这里 `defer close(src)`确保函数执行结束时，自动关闭通道。

> go关闭通道的重要性
> 1. 遍历一个未关闭的channel会造成死循环
> 2.  即使关闭了一个非空通道，我们仍然可以从通道里面接收到未读取的数据
> 3. 可以这样理解，close()函数会往channel中压入一条特殊的通知消息，可以用来通知channel接收者不会再收到数据。所以即使channel中有数据也可以close()而不会导致接收者收不到残留的数据
> 4. channel不需要通过close释放资源，只要没有goroutine持有channel，相关资源会自动释放

## Sync
`sync` 是 Go 标准库中用于同步操作的包。

`sync` 包提供了各种同步原语，用于在多个 Goroutine 之间实现同步和协调。其中包含了以下主要的类型和函数：

- `sync.Mutex`：互斥锁，用于在代码中创建临界区（critical section）。通过使用锁，我们可以保证同一时间只有一个 Goroutine 可以访问临界区，从而避免数据竞争和不一致的结果。

示例代码:
```go
package main

import (
	"sync"
	"time"
)

var (
	x    int64
	lock sync.Mutex
)

func addWithLock() {
	for i := 0; i < 2000; i++ {
		lock.Lock()
		x += 1
		lock.Unlock()
	}
}

func addWithoutLock() {
	for i := 0; i < 2000; i++ {
		x += 1
	}
}

func main() {
	x = 0
	for i := 0; i < 5; i++ {
		go addWithoutLock()
	}
	time.Sleep(time.Second)
	print("Without:", x) // Without:6947   无锁
	x = 0
	for i := 0; i < 5; i++ {
		go addWithLock()
	}
	time.Sleep(time.Second) // withl:10000   有锁
	print("withl:", x)
}
```

- `sync.WaitGroup`：等待组，用于等待一组 Goroutine 完成执行。通过 `Add()` 方法添加等待的 Goroutine 数量，然后每个 Goroutine 在结束时调用 `Done()` 方法，最后通过 `Wait()` 方法等待所有 Goroutine 完成。

示例代码:
```go
package main

import (
	"fmt"
	"sync"
)

func hello(i int) {
	println("hello goroutine : " + fmt.Sprint(i))
}

func main() {
	var wg sync.WaitGroup
	wg.Add(5) // 使用 Add() 方法对计数器 + 5，表示要等待 5 个协程完成
	for i := 0; i < 5; i++ {
		go func(j int) { // 使用匿名函数定义协程逻辑
			defer wg.Done() // 在协程执行完成时，计数器 - 1
			hello(j)
		}(i)
	}
	wg.Wait() // 等待计数器归零，即等待所有协程执行完成
}
```

其他安全锁 :
- `sync.RWMutex`：读写锁，可以同时支持多个 Goroutine 进行读操作，但在写操作时只能允许一个 Goroutine 进行。读写锁适用于读多写少的场景，可以提高并发读的性能。

- `sync.Cond`：条件变量，用于在 Goroutine 之间进行条件等待和通知。通过条件变量，我们可以阻塞一个或多个 Goroutine，直到满足某个特定条件才进行唤醒。

- `sync.Once`：只执行一次，用于实现单例模式的初始化。通过 `Do()` 方法，我们可以确保一个函数或代码块只会被执行一次，即使有多个 Goroutine 并发调用。

- 其他函数：`sync.Atomic` 包含了一些原子操作，如原子的加法、比较交换等，用于在并发场景下实现原子性的操作。
