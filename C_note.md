# 維維的C 筆記


## Macro

\#define 用來定義macro，相對地，#undef 用來取消macro。

在macro中，你可能會看見裡面有些#或是##之類的指令，這個其實是可以對要替換的部分做些特殊操作的標示。
像是#可以把後面的引數當作string來處理，就是加上""。
加上##可以讓前面或後面部分當作要置換成引數，這樣一來，你可以用##來連接多個token。

```
#define str(s) #s
#define notstr(s) s
#define A1(x) asukax
#define A2(x) asuka##x
#define A3(x,y,z) x ##_asuka_ ## y ## _fuuka_ ## z
#define debug(fmt, ...) { \
  fprintf(stderr, "(%s:%d) "fmt"\n", __FILE__, __LINE__, ##__VA_ARGS__); \
}

int main() {
  printf("%s\n", str(is very cute));         // printf("%s\n", "is very cute");
  printf("%s\n", notstr(is a little angel)); // printf("%s\n", is a little angel);
  printf("%s\n", A1(cute));                  // printf("%s\n", asukax);
  printf("%s\n", A2(cute));                  // printf("%s\n", asukacute);
  printf("%d\n", A3(aaa, bbb, ccc)); // printf("%d\n", aaa_asuka_bbb_fuuka_ccc);

  return 0;

}
```

## GCC
```
-E                       Preprocess only; do not compile, assemble or link.
-S                       Compile only; do not assemble or link.
-c                       Compile and assemble, but do not link.
-o <file>                Place the output into <file>.
```

單純使用gcc可以把source code編譯成執行檔，預設輸出的檔名為a.out。
`gcc hello.c`
加上-o可以指定輸出的檔案名稱
`gcc -o asuka hello.c`


在程式中，有時會需要根據不同的版本或平台來決定要用哪種行為，這時候可能會使用#ifdef來決定是哪種。
他會檢查你有沒有定義某些東西來決定要不要編譯這一個區塊的code。
你可以普通的使用#define來定義這些東西，或者在gcc的指令中加上-D這個flag。
`gcc -DDEBUG hello.c`

### 編譯過程
要把一個source變成可執行的檔案，途中需要經過四個步驟，pre-processing, compilation, assembly, linking。

#### pre-processing
這個階段主要會展開所有include的檔案，包含處理macro跟define。
1. 刪除所有define,展開所有macro。
2. 處理所有#ifdef等等條件編譯跟#include等等pre-processing的指令。
3. 展開__LINE__跟__FILE__等等，出錯時才能印出些東西。
4. 將行尾有\的部分跟下一行進行拼接。
5. 刪掉所有註解。

最後，這個階段會產生一個.i檔，你可以使用-E這個flag來讓他只執行pre-processing這個階段。
`gcc -Wall -E asuka.c -o asuka.i`

#### compilation
在這個階段，會將剛才pre-processing的.i檔轉換成組合語言，它又分成scan, parsing, semantic analysis, source code optimization。
scan會把程式碼裡的所有東西分成不同的token, 像是keyword, variable, operator。
parsing會把剛才得到的那些token組合成適當的syntax tree。
semantic analysis會分析這個syntax tree是否正確。
source code optimization 會根據你的設定跟編譯器進行optimize。
你可以使用 -S來觀察這個階段的結果。
`gcc -Wall -S asuka.c -o asuka.s`

#### assembly
根據編譯器將組合語言轉換成對應的機器語言，基本上就是對表。
這個階段後，就會產生.o檔。
`gcc -Wall -c asuka.c -o asuka.o`
這個階段的結果已經不是人能理解的了，不過你可以透過objdump, nm來檢查一些東西。

#### linking
把那些.o檔跟你想要引用的那些.a檔之類的全部集合起來產生出一個執行檔。



### Debug
你可以加上下面兩個flag來協助debug
-Wall 顯示warning
-g 打開gdb的功能。


### Makefile

#### make
make 預設為使用目錄下makefile這個檔案去建置整個程式。
-f 指定檔案，預設檔案是makefile
-C 切換directory，相當於cd 之後在make，不過不用切換資料夾。



#### make
$@  表示目標文件
$^  表示所有的依賴文件
$<  表示第一個依賴文件
$?  表示比目標還要新的依賴文件列表

有三個特殊的語法可以在makefile裡面使用，分別是wildcard, notdir, patsubst。
wildcard 會把所有符合pattern的檔案展開。
notdir會把



### GDB (GNU debugger)




