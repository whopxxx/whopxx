# docker 简单用法

###### 1. 拉取镜像
```
docker pull balabala
eg: docker pull ubuntu:20.04
```

*注意*:如果出现拉不下来的情况，可以尝试配置阿里云镜像加速
```
cd /etc/apt/  
mv sources.list sources.list.bak 备份
vim sources.list  修改
```
添加以下内容
```cpp
deb http://mirrors.aliyun.com/ubuntu/ focal main restricted universe multiverse
deb-src http://mirrors.aliyun.com/ubuntu/ focal main restricted universe multiverse

deb http://mirrors.aliyun.com/ubuntu/ focal-security main restricted universe multiverse
deb-src http://mirrors.aliyun.com/ubuntu/ focal-security main restricted universe multiverse

deb http://mirrors.aliyun.com/ubuntu/ focal-updates main restricted universe multiverse
deb-src http://mirrors.aliyun.com/ubuntu/ focal-updates main restricted universe multiverse

deb http://mirrors.aliyun.com/ubuntu/ focal-proposed main restricted universe multiverse
deb-src http://mirrors.aliyun.com/ubuntu/ focal-proposed main restricted universe multiverse

deb http://mirrors.aliyun.com/ubuntu/ focal-backports main restricted universe multiverse
deb-src http://mirrors.aliyun.com/ubuntu/ focal-backports main restricted universe multiverse
```
```
sudo apt-get update
```
###### 2. 一些实用命令
```cpp
docker images：列出本地所有镜像
docker rmi ubuntu:20.04：删除镜像 ubuntu:20.04  
docker load -i ubuntu_20_04.tar：将镜像ubuntu:20.04从本地文件ubuntu_20_04.tar中加载出来
docker save -o ubuntu_20_04.tar ubuntu:20.04：将镜像ubuntu:20.04导出到本地文件ubuntu_20_04.tar中
```
###### 2. 拉取镜像


###### 2. 拉取镜像


###### 2. 拉取镜像
###### 2. 拉取镜像