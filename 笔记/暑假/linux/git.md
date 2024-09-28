0. git
```cpp
版本控制器

1. working directory 工作目录
2. stage(indx) 暂存区
3. repository(HEAD) Git仓库HEAD指针指向

三种文件状态
1. 已修改 modified
2. 已暂存 staged
3. 已提交 committed
```
1. git配置
```cpp
root@64fd23ff8155:~# git config --global user.name whopxx
root@64fd23ff8155:~# git config --global user.email 2074447320@qq.com

root@64fd23ff8155:~# git config --list
user.name=whopxx
user.email=2074447320@qq.com
```
2. 实践
```cpp
root@64fd23ff8155:~# mkdir myproject   # 创建项目文件
root@64fd23ff8155:~/myproject# git init  #初始化
Initialized empty Git repository in /root/myproject/.git/
root@64fd23ff8155:~/myproject# vim README.md # 创建第一个md文件
root@64fd23ff8155:~/myproject# git add README.md  # 添加到暂存区 第一步
root@64fd23ff8155:~/myproject# git commit -m "add a readme file" # 将暂存区提交到git仓库 第二步
[master (root-commit) 539fc65] add a readme file
 1 file changed, 1 insertion(+)
 create mode 100644 README.md
```
3. 查看状态 `git status`
```cpp
root@64fd23ff8155:~/myproject# git status
  (use "git add <file>..." to update what will be committed) # 使用add加入暂存区
  (use "git restore <file>..." to discard changes in working directory) # 恢复，覆盖回去，尚未加入暂存区的修改全部撤销
        modified:   README.md
no changes added to commit (use "git add" and/or "git commit -a")

root@64fd23ff8155:~/myproject# git add README.md 
root@64fd23ff8155:~/myproject# git status
On branch master
Changes to be committed:
  (use "git restore --staged <file>..." to unstage) # 反悔，将暂存区恢复到先前状态，从暂存区里移除
        modified:   README.md

root@64fd23ff8155:~/myproject# git commit -m "add a sentence"
[master 90be19c] add a sentence
 1 file changed, 1 insertion(+)

root@64fd23ff8155:~/myproject# git status
On branch master
nothing to commit, working tree clean
```
4. 添加开源许可MIT
```cpp
创建 LICENSE(许可证) 文件加入下面内容

Copyright <YEAR> <COPYRIGHT HOLDER>

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
```
5. 查看历史提交 `git log`
```cpp
root@64fd23ff8155:~/myproject# git log
commit 24c6ecaa621b8295fc9a01d735d11a54ee7f0a8a (HEAD -> master) # 为每次提交提供的id，可以找到对应版本
Author: whopxx <2074447320@qq.com>                 # 作者
Date:   Tue Jul 18 23:24:14 2023 +0800             # 记录

    change LICENSE

commit 49f7618d4929689650b54bfe69cbb839b63ca047
Author: whopxx <2074447320@qq.com>
Date:   Tue Jul 18 23:14:36 2023 +0800

    add LICENSE

commit 90be19c72433efa75184f8861cc7488af2e3cbbe
Author: whopxx <2074447320@qq.com>
Date:   Tue Jul 18 23:05:52 2023 +0800

    add a sentence

commit 539fc650ebbd86218dcdbe61d29b31c4d0bdba05
Author: whopxx <whopxx>
Date:   Tue Jul 18 22:54:20 2023 +0800

    add a readme file
```
6. 回到过去`git reset`
```cpp
git reset --soft head~1：撤销上一次提交 commit，但不撤消暂存区的内容 
git reset head~：撤销上一次提交 commit，同时撤销暂存区的内容 
git reset --hard HEAD^ 或 git reset --hard HEAD~：将代码回滚到上一个版本
git reset --hard 版本id号(前几位即可)：回滚到某一特定版本

知道id号的话还可以实现版本前滚
```
7. 比较文件内容`git diff`
```cpp
git diff XX：查看工作区的XX文件相对于暂存区修改了哪些内容

root@64fd23ff8155:~/myproject# vim README.md 
root@64fd23ff8155:~/myproject# git diff
diff --git a/README.md b/README.md # 拷贝到a和b中进行对比
index 93c9711..3c00261 100644 # 文件id 和 文件类型权限
--- a/README.md                        # --- 暂存区文件
+++ b/README.md                        # +++ 工作目录的文件
@@ -1,2 +1,3 @@                        # - 是旧文件， + 是新文件 数字分别表示开始的行号
 This is my first project!
-i add a sentence!
+i add a sentencei!
+i add another sentence!

git diff 版本id1 版本id2：比较不同版本快照
git diff --cached 比较暂存区和git仓库快照
```
8. 修改上一次提交说明`--amend`
```cpp
root@64fd23ff8155:~/myproject# git commit a.cpp -m "change"
[master 90dd9c1] change
 1 file changed, 5 insertions(+)
 create mode 100644 a.cpp

root@64fd23ff8155:~/myproject# git commit --amend
[master 5617c18] changed again
 Date: Thu Jul 20 00:30:42 2023 +0800
 1 file changed, 5 insertions(+)
 create mode 100644 a.cpp
```
9. 删除文件`git rm <文件名>`
```cpp
只是删除工作目录和暂存区域的文件，也就是取消跟踪，在下次提交时不纳入版本管理。
```
10. git分支
```cpp
创建分支
git checkout -b branch_name：创建并切换到branch_name这个分支
git branch branch_name：创建新分支
root@64fd23ff8155:~/myproject# git branch feature
root@64fd23ff8155:~/myproject# git log --oneline
1acecc7 (HEAD -> master, feature) # HEAD目前指向master

切换分支
git checkout branch_name：切换到branch_name这个分
root@64fd23ff8155:~/myproject# git checkout feature
Switched to branch 'feature'
root@64fd23ff8155:~/myproject# git log --oneline
1acecc7 (HEAD -> feature, master) change

修改文件
root@64fd23ff8155:~/myproject# vim README.md 
root@64fd23ff8155:~/myproject# git add README.md 
root@64fd23ff8155:~/myproject# git commit -m "changed in branch"
[feature 1b7869a] changed in branch
 1 file changed, 1 insertion(+)
root@64fd23ff8155:~/myproject# git log --oneline
1b7869a (HEAD -> feature) changed in branch
1acecc7 (master) change

切回主分支
root@64fd23ff8155:~/myproject# git checkout master
Switched to branch 'master'
root@64fd23ff8155:~/myproject# git log --oneline
1acecc7 (HEAD -> master) change

再次修改文件
root@64fd23ff8155:~/myproject# vim a.cpp
root@64fd23ff8155:~/myproject# git add a.cpp 
root@64fd23ff8155:~/myproject# git commit -m "add"
[master 42c4f55] add
 1 file changed, 1 insertion(+)
 create mode 100644 a.cpp

查看分支情况
root@64fd23ff8155:~/myproject# git log --oneline --graph --all
* 42c4f55 (HEAD -> master) add
| * 1b7869a (feature) changed in branch
|/  
* 1acecc7 change
* b9c1267 add
* 49f7618 add LICENSE
* 90be19c add a sentence
* 539fc65 add a readme file
```
11. git分支的合并和删除
```cpp
合并
git merge branch_name：将分支branch_name合并到当前分支上

删除
git branch -d branch_name：删除本地仓库的branch_name分支

合并分支
git merge branch_name：将分支branch_name合并到当前分支上
root@64fd23ff8155:~/myproject# git merge feature
Merge made by the 'ort' strategy.
 README.md | 1 +
 1 file changed, 1 insertion(+)
root@64fd23ff8155:~/myproject# git log --oneline --graph --all
*   946050b (HEAD -> master) Merge branch 'feature' get together
|\  
| * 1b7869a (feature) changed in branch
* | 42c4f55 add
|/  
* 1acecc7 change
* b9c1267 add
* 49f7618 add LICENSE
* 90be19c add a sentence
* 539fc65 add a readme file

删除分支(快照依然存在)
git branch -d branch_name：删除本地仓库的branch_name分支
root@64fd23ff8155:~/myproject# git branch -d feature
Deleted branch feature (was 1b7869a).
root@64fd23ff8155:~/myproject# git log --oneline --graph --all
*   946050b (HEAD -> master) Merge branch 'feature' get together
|\  
| * 1b7869a changed in branch
* | 42c4f55 add
|/  
* 1acecc7 change
* b9c1267 add
* 49f7618 add LICENSE
* 90be19c add a sentence
* 539fc65 add a readme file
```
12. 匿名分支
```cpp
可以用于测试且不会影响正常使用

root@64fd23ff8155:~/myproject# git checkout HEAD~
Note: switching to 'HEAD~'.

You are in 'detached HEAD' state. You can look around, make experimental
changes and commit them, and you can discard any commits you make in this
state without impacting any branches by switching back to a branch.

If you want to create a new branch to retain commits you create, you may
do so (now or later) by using -c with the switch command. Example:

  git switch -c <new-branch-name>

Or undo this operation with:

  git switch -

Turn off this advice by setting config variable advice.detachedHead to false

HEAD is now at 1acecc7 change
root@64fd23ff8155:~/myproject# git log --oneline --graph --all
* 42c4f55 (master) add
* 1acecc7 (HEAD) change
* b9c1267 add
* 49f7618 add LICENSE
* 90be19c add a sentence
* 539fc65 add a readme file
root@64fd23ff8155:~/myproject# vim tmp.txt
root@64fd23ff8155:~/myproject# git add tmp.txt 
root@64fd23ff8155:~/myproject# git commit tmp.txt -m "test"
[detached HEAD 37f6b4f] test
 1 file changed, 1 insertion(+)
 create mode 100644 tmp.txt
root@64fd23ff8155:~/myproject# git log --oneline --graph --all
* 37f6b4f (HEAD) test
| * 42c4f55 (master) add
|/  
* 1acecc7 change
* b9c1267 add
* 49f7618 add LICENSE
* 90be19c add a sentence
* 539fc65 add a readme file
root@64fd23ff8155:~/myproject# git checkout master
Warning: you are leaving 1 commit behind, not connected to
any of your branches:

  37f6b4f test

If you want to keep it by creating a new branch, this may be a good time
to do so with:

 git branch <new-branch-name> 37f6b4f

Switched to branch 'master'
root@64fd23ff8155:~/myproject# git log --oneline --graph --all
* 42c4f55 (HEAD -> master) add
* 1acecc7 change
* b9c1267 add
* 49f7618 add LICENSE
* 90be19c add a sentence
* 539fc65 add a readme file
```
13. git账户
```cpp
https://git.acwing.com/ 随便选一个仓库

root@64fd23ff8155:~/myproject# git remote add origin git@git.acwing.com:Whopxx/myproject.git
root@64fd23ff8155:~/myproject# git push -u origin master
The authenticity of host 'git.acwing.com (47.93.222.173)' can't be established.
ED25519 key fingerprint is SHA256:NQoghu+U5VYcK4/123ZJBcY/+dXBLwXSlW8mIks5ck8.
This key is not known by any other names
Are you sure you want to continue connecting (yes/no/[fingerprint])? yes
Warning: Permanently added 'git.acwing.com' (ED25519) to the list of known hosts.
Enumerating objects: 18, done.
Counting objects: 100% (18/18), done.
Compressing objects: 100% (13/13), done.
Writing objects: 100% (18/18), 2.02 KiB | 2.02 MiB/s, done.
Total 18 (delta 2), reused 0 (delta 0), pack-reused 0
To git.acwing.com:Whopxx/myproject.git
 * [new branch]      master -> master
Branch 'master' set up to track remote branch 'master' from 'origin'.
```
14. 分支命令
`git branch branch_name`：创建新分支
git branch：查看所有分支和当前所处分支
`git checkout -b branch_name`：创建并切换到branch_name这个分支
`git checkout branch_name`：切换到branch_name这个分支
`git merge branch_name`：将分支branch_name合并到当前分支上
`git branch -d branch_name`：删除本地仓库的branch_name分支
`git push --set-upstream origin branch_name`：设置本地的branch_name分支对应远程仓库的branch_name分支
`git push -d origin branch_name`：删除远程仓库的branch_name分支
`git checkout -t origin/branch_name`： 将远程的branch_name分支拉取到本地
`git pull` ：将远程仓库的当前分支与本地仓库的当前分支合并
`git pull origin branch_name`：将远程仓库的branch_name分支与本地仓库的当前分支合并
`git branch --set-upstream-to=origin/branch_name1 branch_name2`：将远程的branch_name1分支与本地的branch_name2分支对应

15.  远程仓库
`git remote add origin git@git.acwing.com`:xxx/XXX.git：将本地仓库关联到远程仓库(这里的origin是一个远程仓库名的别名，可以根据需要自行命名。后面的`git@github.com:username/repository.git`是远程仓库的地址。根据你的实际情况，将其替换为你所使用的远程仓库地址即可)
`git push -u `(第一次需要-u以后不需要) ：将当前分支推送到远程仓库
`git push origin branch_name`：将本地的某个分支推送到远程仓库
`git clone git@git.acwing.com:xxx/XXX.git`：将远程仓库XXX下载到当前目录下
`git push --set-upstream origin branch_name`：设置本地的branch_name分支对应远程仓库的branch_name分支
`git push -d origin branch_name`：删除远程仓库的branch_name分支
`git checkout -t origin/branch_name`： 将远程的branch_name分支拉取到本地
`git pull` ：将远程仓库的当前分支与本地仓库的当前分支合并
`git pull origin branch_name`：将远程仓库的branch_name分支与本地仓库的当前分支合并
`git branch --set-upstream-to=origin/branch_name1 branch_name2`：将远程的branch_name1分支与本地的branch_name2分支对应

16.  stash暂存
`git stash`：将工作区和暂存区中尚未提交的修改存入栈中
`git stash apply`：将栈顶存储的修改恢复到当前分支，但不删除栈顶元素
`git stash drop`：删除栈顶存储的修改
`git stash pop`：将栈顶存储的修改恢复到当前分支，同时删除栈顶元素
`git stash list`：查看栈中所有元素