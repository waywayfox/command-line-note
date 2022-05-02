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

## df
查看硬碟使用量

## awk
文本處理


## VM shared folder
`sudo apt install virtualbox-gues-utils`
`sudo adduser [username] vboxsf`
`reboot`



