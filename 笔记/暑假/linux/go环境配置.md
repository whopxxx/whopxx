# Ubuntu中go环境配置

1. 下载压缩包

使用`wget`命令在官方网站选择对应的压缩包进行下载

`wget https://studygolang.com/dl/golang/go1.20.6.linux-amd64.tar.gz`


2. 解压缩

使用`tar`命令解压缩
`sudo tar -C /usr/local/ -xzvf go1.20.6.linux-amd64.tar.gz`

命令:`tar [-c -v -x -f -z -C] 参数1 参数2 ... 参数N`

- `-c`，创建压缩文件，用于压缩模式
- `-v`，显示压缩，解压的过程
- `-x`，解压模式
- `-f`，要创建的文件，或要解压的文件，`-f`选项必须在所有选项中位置处于最后一个
- `-z`，`gzip`模式，不使用`-z`就是普通的`tarball`格式
- `-C`，选择解压的目的地，用于解压模式

3. 配置环境变量

`sudo vim /etc/profile`

最后面加入以下内容

```go
export GOROOT=/usr/local/go
export GOPATH=/usr/local/gopath
export PATH=$PATH:$GOROOT/bin
```

`source /etc/profile`命令立即生效


环境变量`env`

- `$`可以取出环境变量`echo $变量名`
- 临时设置，语法：`export 变量名=值`
- 永久设置
  - 针对当前用户，配置在当前用户的`~/.bashrc`文件中
  - 针对所有用户，配置在系统的`/etc/profile`文件中
  - 配置完成后用`source 配置文件`的形式，进行立刻生效
自定义文件最后添加内容形如`export PATH=$PATH:~/workspace`

4. 配置go代理
```go
go env -w GO111MODULE=on
go env -w GOPROXY=https://goproxy.io,direct
```

5. `go env`检查
```go
GO111MODULE="on"
GOARCH="amd64"
GOBIN=""
GOCACHE="/home/whopxx/.cache/go-build"
GOENV="/home/whopxx/.config/go/env"
GOEXE=""
GOEXPERIMENT=""
GOFLAGS=""
GOHOSTARCH="amd64"
GOHOSTOS="linux"
GOINSECURE=""
GOMODCACHE="/usr/local/gopath/pkg/mod"
GONOPROXY=""
GONOSUMDB=""
GOOS="linux"
GOPATH="/usr/local/gopath"
GOPRIVATE=""
GOPROXY="https://goproxy.io,direct"
GOROOT="/usr/local/go"
GOSUMDB="sum.golang.org"
GOTMPDIR=""
GOTOOLDIR="/usr/local/go/pkg/tool/linux_amd64"
GOVCS=""
GOVERSION="go1.20.6"
GCCGO="gccgo"
GOAMD64="v1"
AR="ar"
CC="gcc"
CXX="g++"
CGO_ENABLED="1"
GOMOD="/dev/null"
GOWORK=""
CGO_CFLAGS="-O2 -g"
CGO_CPPFLAGS=""
CGO_CXXFLAGS="-O2 -g"
CGO_FFLAGS="-O2 -g"
CGO_LDFLAGS="-O2 -g"
PKG_CONFIG="pkg-config"
GOGCCFLAGS="-fPIC -m64 -pthread -Wl,--no-gc-sections -fmessage-length=0 -fdebug-prefix-map=/tmp/go-build360974333=/tmp/go-build -gno-record-gcc-switches"
```

6. 创建go项目

```go
mkdir hello_go
touch main.go
go mod init hello_go (形成go.mod文件)
```

## go mod
```go
go mod是一个包管理工具，也就是管理那些你的这个项目中所依赖的库包。
作为官方的包依赖管理工具，已经被广泛的用在了各个开源的项目中。

go mod init 应用名称(项目名称)  ，执行该命令，会在应用过的根目录下(家目录)，生成go.mod文件。

我们在进行go语言项目开发的时候，会依赖3种类型的库包：
   (1)内置的标准库包，在goroot/src目录下，也就是我们安装目录的src目录下(类似于python的bin目录)
   (2)第三方库包（git上开源的）
   (3)项目中的库包，也就是项目中的其他目录。自己调用自己写的函数方法
   
如果是go之前的版本，会先将项目中所依赖的库包通过go get命令下载到本地的gopath目录下，然后在需要的时候就到对应的gopath目录下去查找。
但是这种做法是有很大的问题的，具体是啥问题，这里就不多说了。
然后为了解决这个问题,go.mod就闪亮登场了。

使用go mod 来管理项目，我们就不需要非得把go语言的项目放在$gopath指定目录下了，而是可以在磁盘的任何位置新建一个项目。
```

## ps:

```go
在上面中，我们通过 go mod init xxx命令生成了go.mod文件之后，这只是一个空的文件，
其中依赖的各种包还没有生成，可以使用以下2种命令获取：
  <1>go get 包名
      如果依赖包比较多，那么 go get 就比较麻烦了。可以使用另外一个命令：
  <2>go mod tidy
      这个命令将会扫描所有我们写的.go文件中import到的库包，并生成对应的记录到go.mod文件里。

```