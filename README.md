# 維維狐的git小筆記

##git status

##git commit


##git log

`git log --name-status` 顯示新增、更動、刪除的檔案列表。

##git merge

`git merge --no-ff <branch>`  
不使用fast forward，在master為最新版本時，一般狀況merge會把所有branch的commit拉到master，這時可以使用--no-ff在merge時合併整個branch的commit，變回原本merger的情況。

##git remote
`git remote -v` 查看目前remote端的路徑

##git checkout
讓自己本地端的修改 疊在遠端的版本

    git checkout <remote branch>
    git pull #取得最新的版本
    git checkout <local branch> #切回自己的分支
    git rebase <remote branch> #將自己目前分支修改的部分疊加在要疊加的分支上

##git branch

`git branch` 查看所有的分支跟目前所在的分支
