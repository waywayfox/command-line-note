# git-note


相關於git merge

git merge --no-ff <branch>  #不使用fast forward，在master為最新版本時，一般狀況merge會把所有branch的commit拉到master，這時可以使用--no-ff在merge時合併整個branch的commit，變回原本merger的情況。

查看目前remote端的路徑
git remote -v