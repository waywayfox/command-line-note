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
$<num>，表示第幾個參數，從1開始。 \
$? 上一個執行的指令的exit status。 \
$# 傳進的參數的數量。 \
$0 當前的script name \
$\* 所有參數 \
$@ 所有參數


## 字串處理
你可以用下面的方式切開儲存字串的變數，下面是判斷第一個字元是否是/。
字串從第0開始算起，第一個數字是開始位置，第二個則是要擷取的長度，假如是負數，則截到從後面數來第幾個，不加第二項就是起點之後所有內容。
```
"${var:0:1}" = "/"
```
除了上面的方法外，也有更神奇的切割法，bash有許多神奇的字串處理方式，下面這個也能達成同樣的效果。
```
"${var%${var#?}}"
```
${var#pattern} #代表會回傳除了第一個符合pattern的match的其他東西，而這裡的pattern是?，代表任何一個字元，也就是會剩下第一個字元外的所有東西。
${var%pattern} %則會刪除所有在pattern的部份，在這裡的pattern是除了第一個字元之外的所有東西，所以被刪除之後，就剩下第一個字元了。



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
你可以在判斷前面加上!，來表示not，若是你要連接判斷式，-a代表and, -o代表or。


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
test 用來測試判斷式 \
cut 用來擷取字串 \
sed 用來做文字處理，有自己的script \
tr 簡易版的sed，用來做一些替換作用 \
set 用來設置shell的環境
fmt 用來編排文字格式




## 接收參數
一般情況下，你可以用$1, $2之類的表示來抓到傳進來的參數，或是用$\*, $@來抓到所有參數，
不過用這種方法，你需要一開始就確定參數的數量，而且使用者需要照著輸入才行
因此，另一個方式是使用options，就是使用-f,之類的來指定這個東西是屬於哪個參數的。
它需要用到三個東西，while, case 跟 getopts才能達到，像下面這樣
getopts裡面放著你要檢查的flag，在使用case去判斷該把什麼放到哪裡或做什麼事。
冒號:代表說這個flag需要給值，這裡d,t需要指派值，而問號就不用。
它會把分析的結果放在$OPTARG裡面，根據你的需要指派給變數即可。
```
while getopts "d:t:?" opt; do
  case $opt in
    d ) DD="$OPTARG" ;;
    t ) TD="$OPTARG" ;;
    ? ) usage; exit ;;
  esac
done
```

## 算術功能
你可以用$(())來執行基本的數字計算。
echo $(( 1 / 2 ))

## 檔案輸入
你可以使用 << 來表示你想把什麼內容灌到這個指令中，像是你想輸入檔案之類的，
如果你想輸入一個類似檔案的東西，則可以使用EOF來解決，像是下面這樣,
```
bc -q -l << EOF
  scale=$precision
  $*
  quit
EOF
```

## 引入檔案
假如你想要引入你其他寫的command或是function，你可以使用.來達成。
不過要注意你的檔案需要在PATH之中才行。




## DEBUG
在執行檔案時，你可以用-x來讓bash來印出錯誤訊息，或是使用set -x來設置這個設定。





