# 維維的linux command line 小筆記

## hot key

ctrl + 左右鍵 移動到上下一個字
ctrl + a/e 移動到最前或最後
ctrl + h 刪除一個字
ctrl + u/k 刪除當前位置之前之後的所有東西
ctrl + y 貼上你剛才刪掉的東西
ctrl + l 清除畫面，跟clear一樣
ctrl + s/q 暫停，繼續畫面，好像是在遠古時代，電腦的ram不足以支撐整個螢幕的字，
所以需要暫停繼續來控制對方送過來的資料量。


ctrl + shift + t 新tab
ctrl + shift + w 關掉tab
alt 切換tab


alt + f10 最大化視窗
alt + f9 最小化視窗
alt + f4  關掉視窗


## ls
-l 顯示詳細資訊 \
-a 顯示隱藏檔 \
-h 更好讀 \

-F 會加上特殊字元來表示這個檔案的種類
* @ symbolic link
* \* executable
* = socket
* | pipe
* \> door
* / directory

-r 反向輸出 \
-R 遞迴到各個子目錄 \
-t 按照時間 \
-S 按照大小 \
-i 列出Inode \
-d 只列出目錄 \
-n 列出UID跟GID \
-B 隱藏備份


下面的是一些自定義輸出的部份，更詳細的設定就請需要在查吧
--time-style 定義時間輸出格式 \
--format     定義排版 \
--sort       定義排序方式 \
--width      定義輸出寬度 \
--color      要不要顏色輸出

## mkdir

-p 如果路徑中的directory不存在則一起創建
-m 755設定創建的directory的權限


## cat

-n 輸出行號

## cd
`cd /` 回到上一層。
`cd /` 回到root目錄。
`cd ~` 回到家目錄。
`cd -` 回到上一次所在的目錄。



## rm

`rmdir`
可以刪除空的資料夾

`rm <filename>`
刪除檔案

`rm -r <directory>`
刪除整個路徑，包含裡面的內容物。

`rm -rf <directory>`
強制刪除整個路徑，包含裡面的內容物，如果有出現rm: remove write-protected regular file 這種訊息的話可以使用。


## date
顯示當前時間，不過預設它會根據你當前的機器的語言來顯示時間，你可以用下面的方式讓他暫時印出英文，或是直接更改自己所在的語言。
```
echo $(LANG=en_us_8859_1; date '+weekday="%a" month="%b" day="%e" year="%G"')
```

## grep
grep 是用來查詢檔案中是否有指定的字串用的。
```
grep <pattern> <file ...>
```
-i 不區分大小寫 \
-n 顯示行號 \
-r 遞迴查詢目錄，可以搭配--include=來指定檔名的pattern
```
grep -r echo ~/Documents/scripts
grep -r include="*.sh" echo ~/Documents/scripts
```

使用下面三個flag的話，除了顯示出現匹配的那行外，還能顯示前後幾行。
-A (After) 後面 \
-B (Before) 前面 \
-C (Context) 前後
```
grep -r -C1 --include="valid*" cut .
```


## find

-name 可以搜尋特定的名稱，也支援pattern搜尋，
-iname 則可以無視大小寫搜尋

`find <path> -name <filename>`
在路徑下尋找檔名

`find <path> -name *.c`
在路徑下尋找所有.c檔


-type 可以搜尋相關的類型
d 目錄 \
f 普通檔案 \
p pipe檔（FIFO） \
l 連結檔 \
s socket檔

`find <paht>  -type d -name aaa`
在路徑下尋找所有aaa的資料夾


-perm 可以判別權限
`find . -type f -perm 0777`
`find . -type f ! -perm 0777`


-exec 可以對找到的檔案做某些動作
`find <path> -user <user name> -exec rm -fr {} \;`
刪除路徑下所有使用者是<user name>的檔案跟資料夾

`find . -type f -perm 0777 -print -exec chmod 644 {} \;`
將找到權限為777的檔案的權限換成644

-user 用來判斷使用者
`find / -user root -name gtwang.txt`

-group 判斷群組
`find /home -group developer`

-size 判斷大小，用加減來判斷範圍。
`find . -size +50M -size -100M`


-empty 尋找空檔案或空目錄



-print0 假設你要處理有空白字元的檔案，把這個加在最後面，它會使用null來分格輸出。



## df
查看硬碟使用量

## awk
文本處理

-F 指定分隔符



## VM shared folder
`sudo apt install virtualbox-gues-utils` \
`sudo adduser [username] vboxsf` \
`reboot`


## sed
也是用來做文本處理
常用的使用方法
-e 可以在後面指定一串pattern，有點像是vim的操作。
```
echo "a,  b,  c, d, e, f , g, h,i " | sed -e "s/,//g"
a  b  c d e f  g hi
```
-n <num>p 可以照到你想要的那一行
```
sed -n 5p << EOF
aaaa
bbbb
cccc
dddd
eeee
ffff
gggg
EOF
eeee
```

## cut
cut 是一個可以用來擷取字串的指令
最常用的指令是-c 後面接上你要擷取的範圍，要分段也可以用逗點隔開
```
echo "1234567890asdfghjk" | cut -c 2-10
234567890
echo "1234567890asdfghjk" | cut -c 2-5,8-10,12,14
2345890sf
```
假如你要設定是要刪掉的部份，在後面加上--complement
```
echo "1234567890asdfghjk" | cut -c 2-5,8-10,12,14 --complement
167adghjk
```
假如你要拆的資料是用某些符號區分，則用-d表示分隔符, 空格的話你也以用' '來表示。-f代表要取得的欄位，一樣可以用逗點分隔。
```
echo "a,  b,  c, d, e, f , g, h,i " | cut -d , -f 2,4,6-8
  b, d, f , g, h
```
你也可以指令輸出的分隔符使用--output-delimiter=""
```
echo "a,  b,  c, d, e, f , g, h,i " | cut -d , -f 2,4,6-8 --output-delimiter="OwO"
  bOwO dOwO f OwO gOwO h
```

## alias & unalias
對你的command設置別名，
```
alias [-p] [name=[value] ...]
unalias [-a] [name ...]
```
-p可以查看你現在所有設定的別名， \
-a則是刪除所有的別名設定，不過在ubuntu上已經有定義一些預設的別名，請確認你真的不要在刪掉。

設置的別名不能包含變數($1之類的)，必須是純指令。
```
alias la='ls -A'
```
你可以查查你terminal的設定，也許裡面已經有它預設的alias。

## xargs
使用這個指令時，它會進入輸入模式，在你ctrl-d結束之後，它會把你所輸入的東西分割，
並用作為某個指令的參數傳進去，假如你沒有指令指令，它預設是/bin/echo。

預設上，它使用空格跟換行來分割你的輸入。 \
-d 讓你指令分割符。 \
-n 讓你決定一次傳進去的數量，像下面，它一次就只會傳3個參數進去，所以就被分成了2次echo呼叫。
```
echo a b c d e f | xargs -n 3
a b c
d e f
```
-p 會讓你在執行指令前確認要不要執行，輸入y或n來決定。
```
echo a b c d e f | xargs -p -n 3
echo a b c ?...y
a b c
echo d e f ?...n
```
-r 避免空字串 \
-0 使用null來當分隔，假如你需要處理含有空白字元的檔案時可以用 \
-t 則會顯示它執行了哪些指令。 \

若是你想要使用其他指令，只需要把它加在xargs就好，像是find或是grep都能有很好的效果
假如你怕執行到錯誤的指令，可以用上面的-p來確認。
```
find . -name "*.c" | xargs rm -f # delete all .c file
```
使用grep的話，可以像這樣，在找到某些檔案之後，搜尋其中的字。
```
find .-name '*.c' | xargs grep 'stdlib.h'
```

## wc
wc是來計算檔案中的行數，字數及大小(bype)的工具。
基本使用方式就是在後面加上你要計算的檔案
```
wc intro.sh echon.sh
  4  10  68 intro.sh
  9  33 146 echon.sh
 13  43 214 total
```
-l 只計算行數 \
-w 只計算字數 \
-c 只計算大小 \
-m 計算char的數量，假如你有用英文以外的語言的話。 \
-L 找出最長的那行。


## tr
tr可以用來替換，或刪除你所指定的字元。
```
tr [-c] [-d] [-s] [delete pattern] [replace pattern]
```
-c, --complement 不要替換符合第一個pattern的所有東西，其餘的所有刪除。 \
-d 替換所有符合第一個pattern的東西。 \
-s 刪除所有重複的pattern，只保留第一個。 \
你可以用--help來知道用什麼來表示pattern。


替換大小寫
```
echo aijfwoOIJJFNjfoie | tr "[[:lower:]]" "[[:upper:]]"
AIJFWOOIJJFNJFOIE
```
刪掉重複的字母
```
echo aaaaaAAAAAaaBBBbbbBB | tr -s "[a-z]"
aAAAAAaBBBbBB
echo aaaaaAAAAAaaBBBbbbBB | tr -s "[a-z][A-Z]"
aAaBbB
```


##　sort
sort 使用來排序東西的，假如你有一些log紀錄或是資料需要排序，就可以使用。


下面是可以加的flag
-b 忽視行前空白 \
-o 輸出檔案 \
-f 不分大小寫 \
-u 刪除重複的資料，只留下一筆。 \
-r 反向輸出 \
-t 指定分隔號 \
-k 指定分隔之後的區塊 \
-n 把資料當作數字比較 \
-h 把簡單的單位計算進去 \
-R 只是整理資料 \
-M 用月份排序，你可能要把語系設成英文比較好

## uniq
這個指令是用來刪除連續且重複的行數的
-c 顯示重複的數量 \
-d, -D 只顯示重複的行 \
--all-repeated=separate 用空格分開那些重複的行 \
--all-repeated=prepend 在前面加一行空白 \
-u 只顯示沒有重複的行 \
-f 跳過欄位，不會檢查前幾個欄位，用空格或tab來分割。 \
-s 跳過前幾個字 \
-w 只比較前幾個字 \
-i 讓它區分大小寫


## curl

基本用法
`curl [options] [URL...]` \
`crul https://www.google.com`

-o, -O 下載檔案 \
-L redirect \
-X, --request [GET|POST|PUT|DELETE|PATCH] \
-H, --header  指定header \
-i, --include 顯示header \
-d 指定request body \
-v 輸出更多訊息，debug用 \
-u user[:password] 用來驗證，這是BASIC驗證，假如用不同的驗證方式你要加上其他flag，如--ntlm。 \
-b, --cookie 帶cookie \
-A, --user-agent 有時server會阻擋curl或wget的請求，加上user agent來嘗試騙過他們。 \
`-A "Mozilla/5.0 (X11; Linux x86_64; rv:60.0) Gecko/20100101 Firefox/81.0"`


## ln
連結有分硬連結跟軟連結，硬連結會使用相同的inode，基本代表他們是相同的檔案，就算你砍了原檔案，只要還有一個硬連結存在，檔案就還存在。
而軟連結則不是，但也因為inode不同，所以當原檔案消失時，連結檔也再也無法連結到了。

創建一般的硬連結不需要加參數。 \
`ln <file> <link_file>`

-s 創建軟連結則 \
`ln -s <file> <link_file>`

-f 若連結檔已經存在，他會阻止你，使用-f強制覆蓋。 \
`ln -f <file> <link_file>`

軟連結是使用路徑來紀錄原檔案的，所以軟在建立軟連結時，可以使用絕對或相對路徑，不過你在移動軟連結檔案時需要注意，
當初創建時的路徑並不會隨著你的移動而一起改變，所以若你用相對路徑的話，可能會找不到原檔案。


# uname
顯示unix name

-a 顯示全部資訊 \
-v 版本


# du
簡單顯示硬碟用量

`du -d 1 -h <path>`

# diff
`diff a.txt b.txt`

-c 顯示內容
-y 並列顯示不同的部分
-W 欄寬

# ar
可以將多個檔案合成一個檔案，可以用來製作備份或是合成library。
也可以對產生的備份檔進行修改刪除等等動作。

# 其他筆記
linux samba路徑
`/run/user/1000/gvfs/...`












