#  基于docker创建ubuntu:22.04容器并实现ssh连接
首先需要确保服务器上有docker并有相关的镜像
第一次学linux自己~~搜资料~~摸索的，可能有问题，请及时指出
### 按照下面的命令执行即可
```cpp
docker run -itd -p 20022:22 --name whopxx ubuntu:22.04
```
>  主要是 **-p**参数进行端口映射  也可以映射端口多个例如
>  docker run -itd -p 20022:22 -p 20080:80 --name whopxx ubuntu:22.04
>  如果你的镜像是export 来的，似乎还需要在后面加上什么 如 bin/bash
>  容器名称自己随便起

### 创建后继续下面指令
```cpp
docker attach whopxx
```
> 进入容器内部
```cpp
root@xxxxxxx:~# passwd  (添加密码)
root@xxxxxxx:~# apt-get update
root@xxxxxxx:~# apt install vim
root@xxxxxxx:~# apt install tmux
root@xxxxxxx:~# apt install ssh
```
> 安装必要的软件

```cpp
到服务器开放对应端口(只是连接的话22端口映射的端口打开即可
```
```cpp
root@xxxxxxx:~# vim /etc/ssh/sshd_config
找到 #PermitRootLogin prohibit-password
修改为 PermitRootLogin yes
```
> 开放root连接权限

```cpp
root@xxxxxxx:~# service ssh status  (ssh服务开启状态)
root@xxxxxxx:~# service ssh restart (重启ssh服务)
ctrl + p   ctrl + q 退出容器
```
```cpp
尝试连入容器
whopxx@xxxxxxx:~$ ssh root@xxx.xx.xxx.xx -p 20022 (连入对应端口)
输入密码 连接成功
```