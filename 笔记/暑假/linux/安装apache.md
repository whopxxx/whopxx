1. root@0a7b3aedf28d:~# apt update
2. root@0a7b3aedf28d:~# apt install apache2 (安装)
3. root@0a7b3aedf28d:~# apt install systemctl 
4. root@0a7b3aedf28d:~# systemctl restart apache2 (重启)
5. 现在由于容器没有80端口的映射，所以无法访问
6. 退出 尝试添加80端口映射
7. whopxx@hecs-398945:~$ docker stop whopxx
8. whopxx@hecs-398945:~$ docker export -o apache.tar whopxx
9. whopxx@hecs-398945:~$ docker import apache.tar apache:1.0
10. whopxx@hecs-398945:~$ docker run -p 20022:22 -p 20080:80 --name whoping -itd apache:1.0 bin/bash
11. 服务器开放映射端口
12. whopxx@hecs-398945:~$ docker attach whoping (重新登录)
13. root@64fd23ff8155:~# service ssh status (ssh服务状态)
14. root@64fd23ff8155:~# service ssh restart (ssh重新启动)
15. root@64fd23ff8155:~# systemctl restart apache2 (重启)
16. 浏览器访问 http://139.9.117.26:20080/ 查看状态
17. 部署成功