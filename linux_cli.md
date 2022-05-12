# 維維的linux command line 小筆記

## ls
-l 顯示詳細資訊 \
-a 顯示隱藏檔 \
-h 更好讀 \

-F 會加上特殊字元來表示這個檔案的種類
* @ symbolic link
* \* executable
* = socket
* | pipe
* > door
* / directory

-r 反向輸出
-R 遞迴到各個子目錄
-t 按照時間
-S 按照大小
-i 列出Inode
-d 只列出目錄
-n 列出UID跟GID
-B 隱藏備份


下面的是一些自定義輸出的部份，更詳細的設定就請需要在查吧
--time-style 定義時間輸出格式
--format     定義排版
--sort       定義排序方式
--width      定義輸出寬度
--color      要不要顏色輸出


## cd

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

## find
`find <path> -name <filename>`
在路徑下尋找檔名


`find <path> -name *.c`
在路徑下尋找所有.c檔

`find <paht>  -type d -name aaa`
在路徑下尋找所有aaa的資料夾

`find <path> -user <user name> -exec rm -fr {} \;`
刪除路徑下所有使用者是<user name>的檔案跟資料夾


-print0 假設你要處理有空白字元的檔案，把這個加在最後面，它會使用null來分格輸出。



## df
查看硬碟使用量

## awk
文本處理

-F 指定分隔符



## VM shared folder
`sudo apt install virtualbox-gues-utils`
`sudo adduser [username] vboxsf`
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
-p可以查看你現在所有設定的別名，
-a則是刪除所有的別名設定，不過在ubuntu上已經有定義一些預設的別名，請確認你真的不要在刪掉。

設置的別名不能包含變數($1之類的)，必須是純指令。
```
alias la='ls -A'
```
你可以查查你terminal的設定，也許裡面已經有它預設的alias。

## xargs
使用這個指令時，它會進入輸入模式，在你ctrl-d結束之後，它會把你所輸入的東西分割，
並用作為某個指令的參數傳進去，假如你沒有指令指令，它預設是/bin/echo。

預設上，它使用空格跟換行來分割你的輸入。
-d 讓你指令分割符。
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
-r 避免空字串
-0 使用null來當分隔，假如你需要處理含有空白字元的檔案時可以用
-t 則會顯示它執行了哪些指令。

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
-l 只計算行數
-w 只計算字數
-c 只計算大小
-m 計算char的數量，假如你有用英文以外的語言的話。
-L 找出最長的那行。


## tr
tr可以用來替換，或刪除你所指定的字元。
```
tr [-c] [-d] [-s] [delete pattern] [replace pattern]
```
-c, --complement 不要替換符合第一個pattern的所有東西，其餘的所有刪除。
-d 替換所有符合第一個pattern的東西。
-s 刪除所有重複的pattern，只保留第一個。
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

















