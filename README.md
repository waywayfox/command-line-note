# 維維狐的git小筆記

## git help
你可以透過下面指令來查閱git的幫助文件。
```
git help <verb>
git <verb> --help
man git-<verb>

git help config
```
如果你只想要一些簡單的usage，使用-h就好
`git add -h`

## git init
你可以把一個現有的directory納入git的管理下，只要你在那個directory下這樣做。
`git init`

## git clone
從某個server將repository載下來，你可以加上dir如果你不想要clone下來的repository跟它設定的名字一樣。
`git clone <url> [<dir>]`

`git clone -o asuka`
一般來說預設的remote name是origin，你可以用-o來指定你要的名字，像這個你的remote default就會是asuka/master。



## git status
git 的所有檔案有兩種狀態，untracked跟tracked，untracked代表這個檔案並沒有在repository裡面，也可以說這個檔案並沒有前一個版本的紀錄。
而tracked則有三個階段，unmodified，modified跟staged。
你可以使用這個指令來查看現在repository的狀態。
你可以在後面加上--short或-s來顯示簡單的狀態，他會有兩列，左邊是stage area，右邊是working area。


## ignore file
通常有會有一些你絕對不想追蹤的檔案出現，例如node\_module或是build產生的一些.o檔，你可以在repository下建立一個.gitignore。
在簡單的狀況下你可能只會有一個.gitignore，但是專案一大之後，你可能會想要在個別的資料夾下設定各自的.gitignore。
大部分情況你可以在網路找到你的語言所需要的ignore file，不過如果你想自己寫的話，
下面是一些簡單的語法
使用\#當作comment
預設上這個他會對每個規則遞迴到每個資料夾。 在最前面加上\\表示不需要遞迴執行這項規則。
在最後面加上\\表示這規則是個資料夾。
使用**可以表示巢狀的資料夾

使用!來進行逆向指定。
下面附上gitpro裡面的範例。

```
// ignore all .a files
*.a
// but do track lib.a, even though you're ignoring .a files above
!lib.a
// only ignore the TODO file in the current directory, not subdir/TODO
/TODO
// ignore all files in any directory named build
build/
// ignore doc/notes.txt, but not doc/server/arch.txt
doc/*.txt
// ignore all .pdf files in the doc/ directory and any of its subdirectories
doc/**/*.pdf

```

## git add
當你剛clone一個repository下來時，所有檔案都是tracked跟unmodified的，當你改動檔案，這個檔案就是modified，而當你add一個檔案，它就會變成staged狀態，代表說你打算把這個檔案記錄在下一個版本中。
git add有三個功能，追蹤某個檔案，stage修改的檔案，將某個檔案標記為resolve。當你下了git add這個指令，代表你想把這個瞬間這個檔案的樣子記錄下來，放進歷史的紀錄中。

## git reset
當你想要將在stage狀態的檔案恢復到原來的狀態，你可以使用reset。
在2.23.00版之後改成restore

`git reset HEAD <file>`
將檔案從stage狀態移除，不會改動你的修改。

`git reset --hard`
假如你使用--hard，不僅檔案會被移出stage狀態，還會將檔案恢復到指定commit的狀態。


## git commit

`git commit --amend`
更改上一次的commit。

`git commit -m <message>`
使用單行作為commit的message。

`git commit -a -m <message>`
假如你真的很懶，你可以加上-a，這樣他就會把所有已經track的檔案stage之後commit。

## git log

`git log [<options>] [<revision range>] [[--] <path>…​]`

`git log`
一般顯示近期的commit，

`git log -<number>`
顯示最近 number 筆的commit訊息

`git log -p`
顯示commit 中每個文件所作的改動

`git log --stat`
顯示commit中改動的檔案跟行數。

`git log -- <path>`
只顯示有改動到path下的commit。

`git log --oneline`
只顯示commit中的標題跟SHA碼

`git log --pretty=format:"<format>"`
你可以使用format來自訂輸出的格式。
例如
`git log --pretty=format:"%h - %an, %ar : %s"`

`git log --decorate`
會顯示branch指在哪個commit。

`git log --name-status` 顯示新增、更動、刪除的檔案列表。

`git log --follow <file name/directory name>`
顯示除了改名之外有更改過這個檔案的commit。

`git log --full-history -- <dir/filename>`
查詢所有有關這個檔案的commit，包含刪除。

`git log --diff-filter=A -- <filename>`
查詢某個檔案創建的commit

另外--diff-filter的選項如下
A = Added \
C = Copied \
M = Modified \
R = Renamed \
T = Changed \

`git log -L start,end:file`
`git log -L :function:file`
查詢改動某個檔案幾行到幾行，或是含有特定字串的commit。
用來找改動function的commit很好用
例如：git log -L :myfunction:path/to/myfile.c

`git log -S <pattern>`
查詢某個有改動某字串的commit。

`git log --all --decorate --oneline --graph`
簡單印出還不錯的log。 `git log --since=<date> --until=<date>`
指定時間

### git shortlog
顯示出範圍內的commit title。


## git format-patch
要製作patch檔的，主要有兩種作法，一種是git diff 產生，另一種是git format-patch，
你可以使用這個產生patch檔，在使用git am或apply來patch這些內容。
跟diff的主要的不同是它含有更多meta資料，一開始是設計來使用mail來傳送的。
主要的使用方法如下。
`git format-patch -<n>`
產生從前n個commit的patch。

`git format-patch <sha>`
產生commit到當前的patch。

`git format-patch --root`
產生從root到當前位置的patch。

`git format-patch -<n> <sha>`
產生某個commit之前n個的patch。

`git format-patch <commit1>...<commit2>`
產生2個commit之間的patch。

`git format-patch -o <filename>`
指定output檔案存放的資料夾。


## git am
用來apply mail傳過來的patch檔的用的。

`git am --abort`
放棄之前的patch的過程，假如之前有失敗你可能會需要用這個來重置狀態。

`git am <file/path>`
apply某個檔案，或是資料夾，假如是資料夾，它會按照編號apply。

## git apply

`git apply <file>`
apply patch檔，記得apply並不會幫你commit。
`git apply --stat <file>`
`git apply --check <file>`
這兩個不會apply patch檔，用來幫你檢查apply後有沒有什麼問題的。





## git pickaxe

## git rebase

`git rebase -i <sha1>`
對現在到目標commit之間的commit進行挑選和位置排列

## git fetch
`git fetch <remote>`
從remote抓取你local沒有的資料。

`git fetch --all`
抓所有remote的資料。

`git rebase --onto <target> <from> <to>`
有很很神奇的用法，可以將from之後1個commit到to之間的commit接到target的部份
下面我有個fina1~3跟fuuka1~3兩個branch，我想把fina12接到fuuka1後面。
所以我就下了`git rebase --onto 40ed5f0 f045302 a6035be`
可以看到結果，從fuuka1後面在長出了一個branch，就是我們要接的fina12，但是因為這像操作，所以fina3消失了。
在進行這個指令時要小心有些commit斷頭。
```
 git glog
* ddf91a3 (HEAD -> fina) fina3
* a6035be fina2
* e017a1b fina1
| * c534949 (fuuka) fuuka3
| * 89f7559 fuuka2
| * 40ed5f0 fuuka1
|/
* f045302 (master) asuka3
* 2104068 asuka2
* c84b920 init
lu@lu-VirtualBox:~/Documents/git_test$ git rebase --onto 40ed5f0 f045302 a6035be
First, rewinding head to replay your work on top of it...
Applying: fina1
Applying: fina2
lu@lu-VirtualBox:~/Documents/git_test$ git glog
* d2aa0ff (HEAD) fina2
* da36599 fina1
| * c534949 (fuuka) fuuka3
| * 89f7559 fuuka2
|/
* 40ed5f0 (fina) fuuka1
* f045302 (master) asuka3
* 2104068 asuka2
* c84b920 init
lu@lu-VirtualBox:~/Documents/git_test$ git glog | grep fina3
lu@lu-VirtualBox:~/Documents/git_test$

```


## git merge

`git merge <branch>`

將branch 合到當前的HEAD。

git 裡面有被稱作upstream的pointer，它指向remote的一個與當前branch相對應的branch，
最常見的就是master跟origin/master，不過你可以對不同的branch設定upstream。
在git 中有個間單的寫法表示upstream，叫做@{upstream}或是@{u}，所以你可以這樣用。
`git merge @{u}`
假如你在master它就等同於
`git merge origin/master`


`git merge --no-ff <branch>`
不使用fast forward，在master為最新版本時，一般狀況merge會把所有branch的commit拉到master，這時可以使用--no-ff在merge時合併整個branch的commit，變回原本merger的情況。

`git merge --squash <branch>`
使用squash的方式合併，合併所有branch上的commit，疊加在目前所在的分支上，產生像是合併完的結果，但並不會產生新的commit，需要自己手動產生新的commit，

`git mergetool`
假如你想要有圖形化的界面來解決merge conflict，你可以用這個，不過有時候會要做些別的設定。


`git merge-base <commit1> <commit2>`
預設的merge是使用3-way merge，它會找出2個commit的base，在用這個base來選擇,merge要選擇哪個，
這個command可以找出base是哪個commit。

## git pull

`git pull`
這條指令是結合了`git fetch`以及`git merge`兩者，將remote端的版本下載到本地端，並合成，
若是在這條分支上已經有本地端地修改的話，則會產生一個新的merge commit。


`git pull --rebase`
將目前remote端的拉下之後，並使用rebase的方式，本地端的修改會被疊加到拉下來的修改上，且不會產生新的merge commit。

`git config --global pull.rebase "true"`
假如你想要你的pull預設就是使用rebase，可以對pull.rebase進行設定。

## git push

`git push <remote> <branch>`
最基礎的用法預設是origin跟master。

`git push origin :<branch>`
使用空的分支替代remote端的分支，等同於刪掉remote上的branch。

`git push --tags`
注意你的tag不會順便推上去，你要加上--tags，或者你也可以單獨推某個tag。

`git push <remote> :refs/tags/<tagname>`
`git push origin --delete <tagname/branch>`
刪掉remote tag的方式跟branch相同，用空的tag代替原有的。

## git remote
`git remote -v` 查看目前remote端的路徑

`git remote add <name> <url>`
增加新的remote。

`git remote rename <oldname> <newname>`
增加新的remote。

`git remote remove <name>`
增加新的remote。

`git remote set-url origin <remote>`
若是你remote的repository有改名稱，或是你存放的遠端路徑有改變，使用這一條更改。

`git remote show <remote>`
查看remote的狀態。


## git checkout
`git checkout <branch>`
切換branch。

在2.23版之後，你也可以使用git switch來切換branch的功能。


讓自己本地端的修改 疊在遠端的版本

    git checkout <remote branch>
    git pull #取得最新的版本
    git checkout <local branch> #切回自己的分支
    git rebase <remote branch> #將自己目前分支修改的部分疊加在要疊加的分支上

回復單一檔案或資料夾到之前的版本
git checkout HEAD -- <path/of/file>
之後改成restore了。

切換到github的pull request，你要先檢查那個pull request的ID，就是在#後面的數字，然後BRANCH_NAME選擇你想在local
注意head是小寫。
```
git fetch origin pull/ID/head:BRANCH_NAME
git checkout BRANCH_NAME

git fetch origin pull/24/head:test_branch
git checkout test_branch
```

` git checkout <tag> `
你可以使用checkout切換到tag的位置，不過你改動並不會被記錄在detach head上，如果妳想保存改動，記得要使用-b真的創建一個branch。

`git checkout --track <remote>/<branch>`
切換到remote的某個branch，並在local建立一個相同名稱的branch，
通常你不加track的話它也會去找你remote有沒有同名稱的branch，用在你有多個remote的情況下。



## git branch

`git branch <name>`
創建新的branch，並指向HEAD，注意你只是創建了它，你還必須checkout到它才行。

`git branch --merged/--no-merged`
顯示當前的branch跟有無被merge到這個branch的其他branch。

`git branch` 查看所有的分支跟目前所在的分支
`git branch --all` 查看所有branch，包括remote的。
`git branch -vv` 查看所有branch，還有他們各自的upstream。

`git branch -m <name>` 改變現在所在分支的名稱，記得你只是改了local的名稱，記得要push。
`git branch -d <name>` 刪除branch。




## git mv
如果你要移動檔案或重新命名的話可以使用這個。

## git rm

`git rm <filename>`
刪掉檔案並把刪除加到stage階段。

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
用來查看目前的改動跟之前的改動有什麼差別。
也可以用來產生patch檔。

`git diff <branch>`
查看目前的HEAD 跟<branch>之前的差異。

`git diff --staged/--cached`
查看當前staged的改動部分。

-M[n] --find-rename
可以檢測這個檔案算不算rename，預設是50%，代表50％以上的文件沒有被改變就算是rename。
`git diff -M50%`

`git diff --check`
查看有沒有多餘的空白在你修改的後面

`git diff <branch1> <branch2> -- file`
查看兩個branch中一個檔案的差異。

## git config

git的config有分成3個層級，system, global, 跟local。
system的設定會apply到所有user上面，global只影響特定user，而local只在當前的repository發生作用。
每一層的設定都會被下一層所覆蓋。


### system
你可以加上--system，就可以讀寫system的
設定，當然你需要有權限才行。


### global
通常放在~/.gitconfig或是~/.config/git/config，你可以加上--globla來讀寫global的設定。


### local
git config是預設的選項。
放在repository裡面的.git/config，你可以加上--local來讀寫global的設定。


###查詢config
你可以單純查詢某個proeprety。
`git config user.name`
或是全部列出來，顯示你的設定跟他們是哪一層級，你不加show --show-origin就只會列出來而已。
`git  config --list --show-origin`


最初你開始使用時，你一定要設定你的名字跟email才行
```
git config --global user.name "waywayfox"
git config --global user.email "waywayfox@example.com"
```

設定文字編輯器，基本上支援蠻多的，有些需要特殊的flag，可以上網查。
```
git config --global core.editor emacs
```

設定default的branch name，像是github是使用main當作default。
`git config --global init.defaultBranch main`

`git config credential.helper`
假如你不想要一直打密碼，你可以使用credential相關的設定，或是直接用SSH。


### Git Aliases
你可以跟shell一樣設定git所使用的alias
```
git config --global alias.co checkout
git config --global alias.br branch
git config --global alias.ci commit
git config --global alias.st status

git config --global alias.unstage 'reset HEAD --'
git config --global alias.kaifuku 'checkout HEAD --'
git config --global alias.last 'log -1 HEAD'
git config --global alias.glog 'log --all --decorate --oneline --graph'
```

`git config --global unset alias.trololo`
刪除alias



## git submodule

`git submodule foreach --recursive git pull <remote> <branch>`
把目前所有引用的submodule都更新到最新版本

## git stash
將目前你track的檔案改動先存起來。

`git stash list`
查看目前的stash。

`git stash`
將現在改動的檔案修改儲存起來，會按照stack的方式儲存，最後的會放在0的位置。

`git stash save '<message>'`
跟stash一樣，不過你可以加上message讓你更好辨識。

`git stash apply [stash@{n}]`
將最近儲存的修改附加上去，加上後面的可以選擇你要哪一個stash。

`git show stash@{n}`
你可以簡單的使用show來查看stash的資料。

`git stash drop`
刪除最後1個stash。

`git stash pop`
基本上就是apply加上drop。

`git stash clear`
刪除所有儲存的修改


## git tag
`git tag` 列出所有tag
查到你想看的tag之後可以用git show來查看相對應的commit。

加入的tag會被記錄在refs/tags/裡面。


-f 強制創建tag，如果舊有的tag存在的話會覆蓋掉之前的。

`git tag -l <pattern>`
使用pattern來搜尋tag。

`git tag <tag>`
創建lightweight tag，你不能給她-a,-m,-s等等flag不然他會創建成annoted。

`git tag -a <tag>`
創見annoted tag

`git tag -m <message>`
加上message。

`git tag -s <sign>`
指定GPG的方式。
查詢tag.gpgSign獲得更多資料。

`git tag -a v1.2 9fceb02`
假如你想為過去的commit加上tag，只要在後面加上他的SHA碼就好。

`git tag -d <tag>`
刪掉tag。

## git describe
用來顯示離當前最近tag。

## git archive
`git archive master --prefix='./' | gzip > ``git describe``.tar.gz`
你可以用這個來製作release，加上--format來指定你的輸出格式。


## git show
讓你可以檢視某個git object。

`git show <object name>`

-s --no-patch 不會顯示diff的部分。
`git show -s --pretty=raw <object name>`



## git ls-files
顯示所有被git追蹤的檔案。
可以在後面加上--來搜尋符合特定pattern的檔案。
`git ls-files -- *.c`


## git ls-tree
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
tag分成兩種，lightweight跟annotated。
lightweight有點像是不會前進的branch，只是單純指向某個commit。
annotated就紀錄更多東西，而且會存進git的database中，通常會建議你使用annotated，因為他有更多資料。

### Rerere
Reuse recorded resolution的簡稱，它可以用來紀錄你每次解決conflict的方式，
久而久之，它會自動幫你解決一些conflict。
你需要在config裡面把rerere.enabled設定成true。
`git rerere`
當你有衝突時，它會嘗試自動幫你解決。


