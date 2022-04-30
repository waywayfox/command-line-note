# Shell script note

## 路徑與執行
最簡單的方式，就是使用sh，這可以用來簡單測試這個script。
```
sh hello.sh
```

當你要執行你的script時，你當然可以用sh加上路徑來指定它，但若是你要
因此，你可以把自己放script的地方加進PATH裡，你可以用bash --login來重整，或是乾脆開個新的terminal。

```
export PATH="/home/lu/Documents/bash_practice:$PATH"
```
當你輸入指令時，它會到PATH裡面搜索你這個指令

除此之外，如果你要讓你的script像是普通command一樣執行，你還得幫它加上x的權限 。
```
chmod +x hello.sh
```
在沒有sh的情況下，你還得在script的第一行，加上它要用什麼東西來執行。
在一般情況下大多都是bash，不過假如你有ruby或Go之類的也許會需要。
```
#!/bin/bash
echo "Hello world"
```

你可能會想說sh到底是什麼，你可以用ls -l /bin/sh 去看，也許你會看到它指向dash而不是bash，至於為什麼，有興趣可以自己去查。


## 特殊符號
要使用變數時，你得在前面加上$才行，跟上面嘗試印出PATH一樣，是用`echo $PATH`而不是PATH，
除了這樣的環境變數之外，在function的參數上也有類似的用法。
$<num>，表示第幾個參數，從1開始。
$? 上一個執行的指令的exit status。
$# 傳進的參數的數量。
$0 當前的script name
$\* 所有參數
$@ 所有參數


## 字串切割
你可以用下面的方式切開儲存字串的變數，下面是判斷第一個字元是否是/。
字串從第0開始算起，第一個數字是開始位置，第二個則是要擷取的長度，假如是負數，則截到從後面數來第幾個，不加第二項就是起點之後所有內容。
```
"${var:0:1}" = "/"
```


## 判斷式
bash script跟普通程式語言的判斷式的表達差異很大，
首先，數字跟字串的判斷方式是完全不同的，數字不能使用普通的>,<,=
下面分成數字，字串 ，檔案。
如果你想要判斷數字，要這樣做
```
$var -eq 5
$var -ne 5
$var -gt 5
$var -ge 5
$var -lt 5
$var -le 5
```
在字串的判斷上，你可以使用, =, !=來判斷兩個字串是否 相同，注意 ，就算你使用數字，它還是會把它當作字串來比較的。
```
$var = "asuka"
$var != ""
-z $var # empty string
-n $var # not empty strin
```
若是變數裡存的是個檔案的路徑，則可以用下來方式檢查他的屬性
```
-d $var # exists and is a directory
-e $var # file exist
-r $var # exist and can be read
-s $var # exist and size is greater than 0
-w $var # exist and can be write
-x $var # exist and can be execute
```
你可以在判斷前面加上!，來表示not。

如果你想測試一下判斷式，你可以用test這個指令，查詢test的指令還可以得到比上面更多的判斷，假如你在上面找不到你想要的東西的話。
```
lu@lu-VirtualBox:~$ test 001 = 1
lu@lu-VirtualBox:~$ echo $?
1
lu@lu-VirtualBox:~$ test 001 -eq 1
lu@lu-VirtualBox:~$ echo $?
0
```

下面是if 跟 case的表示方式
```
if [ <condition> ]; then
  # do something
elif []; then
  # do something
else
  # do something
fi

case $var in
  0 ) #dosomething# ;;
  1 ) #dosomething# ;;
esac
```



## 一些其他指令
test 用來測試判斷式
cut 用來擷取字串
sed 用來做文字處理，有自己的script
tr 簡易版的sed，用來做一些替換作用
set 用來設置shell的環境








