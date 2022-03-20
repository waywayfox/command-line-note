# 維維的linux command line 小筆記

## ls

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



