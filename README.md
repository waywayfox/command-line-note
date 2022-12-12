# 維維狐的git小筆記

## git status

## git commit

`git commit --amend`
更改上一次的commit。

## git log

`git log [<options>] [<revision range>] [[--] <path>…​]`

`git log`
一般顯示近期的commit，

`git log -<number>`
顯示最近 number 筆的commit訊息

`git log -p`
顯示commit 中每個文件所作的改動

`git log --oneline`
只顯示commit中的標題跟SSH碼

`git log --name-status` 顯示新增、更動、刪除的檔案列表。

`git log --follow <file name/directory name>`
顯示除了改名之外有更改過這個檔案的commit。

`git log -L start,end:file`
用來找出檔案中特定名稱的function的commit
例如：git log -L :myfunction:path/to/myfile.c

## git rebase

`git rebase -i <sha1>`
對現在到目標commit之間的commit進行挑選和位置排列


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


## git push

`git push origin :<branch>`
使用空的分支替代remote端的分支，等同於刪掉remote上的branch。

## git remote
`git remote -v` 查看目前remote端的路徑

`git remote set-url origin <remote>`
若是你remote的repository有改名稱，或是你存放的遠端路徑有改變，使用這一條更改。

## git checkout
讓自己本地端的修改 疊在遠端的版本

    git checkout <remote branch>
    git pull #取得最新的版本
    git checkout <local branch> #切回自己的分支
    git rebase <remote branch> #將自己目前分支修改的部分疊加在要疊加的分支上

回復單一檔案或資料夾到之前的版本
git checkout HEAD -- <path/of/file>

切換到github的pull request，你要先檢查那個pull request的ID，就是在#後面的數字，然後BRANCH_NAME選擇你想在local
注意head是小寫。
```
git fetch origin pull/ID/head:BRANCH_NAME
git checkout BRANCH_NAME

git fetch origin pull/24/head:test_branch
git checkout test_branch
```


## git branch

`git branch` 查看所有的分支跟目前所在的分支
`git branch -m <name>` 改變現在所在分支的名稱

## git rm

`git rm --cached <filename>`
把staged的檔案從stage的階段刪掉，還會保留檔案。

## git clean

`git clean`
清除目前所有untracked的檔案，並不會刪除untracked的資料夾。

`git clean -d`
清除目前所有untracked的檔案跟資料夾。

在進行清除時，一定要配合下面3個其中一個進行。

`git clean -f`
強制清除。

`git clean -n`
並不會真的清除，而是列出執行動作後會清除哪些檔案。

`git clean -i`
使用Interactive mode進行刪除。

## git diff

`git diff <branch>`
查看目前的HEAD 跟<branch>之前的差異。


-M[n] --find-rename
可以檢測這個檔案算不算rename，預設是50%，代表50％以上的文件沒有被改變就算是rename。
`git diff -M50%`

## git config

## git submodule

`git submodule foreach --recursive git pull <remote> <branch>`
把目前所有引用的submodule都更新到最新版本

## git stash

`git stash`
將現在改動的檔案修改儲存起來

`git stash apply`
將最近儲存的修改附加上去。

`git stash clear`
刪除所有儲存的修改


## git tag
`git tag` 列出所有tag
查到你想看的tag之後可以用git show來查看相對應的commit。

加入的tag會被記錄在refs/tags/裡面。


-f 強制創建tag，如果舊有的tag存在的話會覆蓋掉之前的。

## git show
讓你可以檢視某個git object。

`git show <object name>`

-s --no-patch 不會顯示diff的部分。
`git show -s --pretty=raw <object name>`



## git ls-files
顯示所有被git追蹤的檔案。
可以在後面加上--來搜尋符合特定pattern的檔案。
`git ls-files -- *.c`


##git ls-tree
可以顯示某次commit時git object的狀態，包含權限，object名稱，檔案名稱等等。
`git ls-tree <commit>`


## Git 小知識

### Git Object

每個git object都有一個名字，他是一個經過SHA1 hash過的40字元的英數字。
運用這個object name，git就可以快速的辨別這是否是同一個object。

除了名字外，每個git object還有另外三個properties，分別是type, size跟conetent。
size基本上就是content的大小。
type 分成4種
* blob 基本上就是file
* tree 基本上就是directory
* commit 指向一個tree，並紀錄著這個時間點它長什麼樣子，裡面包含一些meta-data，像是時間，作者，還有前一個commit等等。
* tag 用來標註某個commit是特別的。

#### Blob
Blob主要是用來儲存檔案中的資料，你可以用git show來顯示某個blob的資料，blob並不會儲存除了內容外的資料，
就連檔名也不會，所以若是兩個檔案的內容完全相同，他們會共用同個blob。
```
git ls-tree -r HEAD
100644 blob 943729d796099ba5b52d142497de5e66b3a65e05    asuka
100644 blob 943729d796099ba5b52d142497de5e66b3a65e05    dir1/fina
100644 blob 943729d796099ba5b52d142497de5e66b3a65e05    fuuka
```

#### Tree
tree放著一堆指向blob跟其他tree的pointer，跟blob一樣，假如兩個tree裡面的內容完全一樣的話，他們會共用同一個sha name。
```
 git ls-tree HEAD
100644 blob 943729d796099ba5b52d142497de5e66b3a65e05    asuka
040000 tree b45716dbb44fce0b55e1b3b12e701dcec9e38d5c    dir1
040000 tree b45716dbb44fce0b55e1b3b12e701dcec9e38d5c    dir2
100644 blob 943729d796099ba5b52d142497de5e66b3a65e05    fuuka

# 修改dir2裡面的一個檔案的內容後
git ls-tree HEAD
100644 blob 943729d796099ba5b52d142497de5e66b3a65e05    asuka
040000 tree b45716dbb44fce0b55e1b3b12e701dcec9e38d5c    dir1
040000 tree da41193f082710a8b63f7f99e952214715af3121    dir2
100644 blob 943729d796099ba5b52d142497de5e66b3a65e05    fuuka
```

#### Commit
commit紀錄著一個tree的狀態。commit並不是紀錄所有改變，而是透過比較跟其parent的那個commit的tree進行比較來得出是否有改變。
```
git show -s --pretty=raw 359ebe6d912c8fdad1c39beb6b70af82a14f3ff8
commit 359ebe6d912c8fdad1c39beb6b70af82a14f3ff8
tree ddc18e433adab842e7a58aaff2e2004c9ab9df7b
parent 9d241a7e1b0cb861c61c4fe94f0e028055dbb6ed
author David.CW.Lu <David.CW.Lu@liteon.com> 1664513986 +0800
committer David.CW.Lu <David.CW.Lu@liteon.com> 1664513986 +0800

    test5
```
tree: tree的狀態。
parent: 前一個commit的SHA1名稱，可能會有多個(merge的狀況)，或是0個，被稱為root commit，通常每個repository至少會有一個root commit。
author: 負責這個commit的人。
committer: 實際創建這個commit的人。
comment: 這個commit的敘述。

### Tag
tag通常會指向一個commit，她會紀錄commit的名稱，tag的名稱，tag的製作人跟tag的說明。
```
git cat-file tag v1.5.0
```





