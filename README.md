# 維維狐的git小筆記

## git status

## git commit

`git commit --amend`
更改上一次的commit。

## git log

`git log`
一般顯示近期的commit，

`git log -<number>`
顯示最近 number 筆的commit訊息

`git log -p`
顯示commit 中每個文件所作的改動

`git log --oneline`
只顯示commit中的標題跟SSH碼

`git log --name-status` 顯示新增、更動、刪除的檔案列表。



## git pull

`git pull`
這條指令是結合了`git fetch`以及`git merge`兩者，將remote端的版本下載到本地端，並合成，
若是在這條分支上已經有本地端地修改的話，則會產生一個新的merge commit。


`git pull --rebase`
將目前remote端的拉下之後，並使用rebase的方式，本地端的修改會被疊加到拉下來的修改上，且不會產生新的merge commit。

## git merge

`git merge --no-ff <branch>`  
不使用fast forward，在master為最新版本時，一般狀況merge會把所有branch的commit拉到master，這時可以使用--no-ff在merge時合併整個branch的commit，變回原本merger的情況。

`git merge --squash <branch>`
使用squash的方式合併，合併所有branch上的commit，疊加在目前所在的分支上，產生像是合併完的結果，但並不會產生新的commit，需要自己手動產生新的commit，

## git remote
`git remote -v` 查看目前remote端的路徑

## git checkout
讓自己本地端的修改 疊在遠端的版本

    git checkout <remote branch>
    git pull #取得最新的版本
    git checkout <local branch> #切回自己的分支
    git rebase <remote branch> #將自己目前分支修改的部分疊加在要疊加的分支上

## git branch

`git branch` 查看所有的分支跟目前所在的分支

## git rm

`git rm --cached <filename>`
把staged的檔案從stage的階段刪掉，還會保留檔案。

## git clean

`git clean` 
清除目前所有untracked的檔案，並不會刪除untracked的資料夾。

`git clean -d`
清除目前所有untracked的檔案跟資料夾。

在進行清除時，一定要配合下面3個其中一個進行。

git clean -f` 
強制清除。

`git clean -n`
並不會真的清除，而是列出執行動作後會清除哪些檔案。

`git clean -i`
使用Interactive mode進行刪除。

##git diff

`git diff <branch>`
查看目前的HEAD 跟<branch>之前的差異。

## git config

