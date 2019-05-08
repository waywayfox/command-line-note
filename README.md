# git-note


相關於git log

--name-status 顯示新增、更動、刪除的檔案列表。

相關於git merge

git merge --no-ff <branch>  #不使用fast forward，在master為最新版本時，一般狀況merge會把所有branch的commit拉到master，這時可以使用--no-ff在merge時合併整個branch的commit，變回原本merger的情況。

查看目前remote端的路徑
git remote -v


讓自己本地端的修改 疊在遠端的版本
git checkout <remote branch>
git pull #取得最新的版本
git checkout <local branch> #切回自己的分支
git rebase <remote branch> #將自己目前分支修改的部分轉到


git res