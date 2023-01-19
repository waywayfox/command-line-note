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

## Make
你在有些地方可能會看到cc，cc是屬於unix的，gcc是linux的 。
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
在這個階段，會將剛才pre-processing的.i檔轉換成組合語言，它又分成scan, parsing, semantic analysis, source code optimization。 scan會把程式碼裡的所有東西分成不同的token, 像是keyword, variable, operator。
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
在makefile中所執行的指令會被印出來，你可以在指令前面加上@防止它被印出來。

#### flag
make 預設為使用目錄下makefile這個檔案去建置整個程式。
-f 指定檔案，預設檔案是makefile
-C 切換directory，相當於cd 之後在make，不過不用切換資料夾。

--dry-run 只會印出要執行的指令，不會真的執行
--touch 會印出你真的有新創建的檔案。

假如你想要替換掉你傳進來的參數，你可以使用override這東西
```
override option_one = lire
print:
	echo $(option_one)
make print option_one=hi
echo lire
lire
```

#### syntax
最基本的語法是
```
target: prerequisites
  recipe
```

你也可以定義多個target，基本上等同於分開的。
```
asuka.o fuuka.o:
  echo $@

# =>
asuka.o:
  echo asuka.o
fuuka.o:
  echo fuuka.o

```
通常target是我們要生成的程式或文件，不過有些時候也有可能是我們想要做的動作，像是clean。
prerequisites是要生成target的先決條件。
recipi是你為了生成target要做的事。
要注意每行recipi的指令都是個別的shell，所以假如你用了類似cd ..之類的，下一行並不會進到上一層目錄。
你可以用;來分隔指令，或是在行尾加上\\來延續一行。
```
print:
	cd ..; pwd
	cd .. ;\
	pwd
	cd ..
	pwd

make print
cd ..; pwd
/home/lu/Documents
cd .. ;\
pwd
/home/lu/Documents
cd ..
pwd
/home/lu/Documents/makefile_test

```

你如果想要在makefile裡面呼叫makefile，你可以使用$(MAKE)，它會自動你把當前的flag傳到下一層。



$@  表示目標文件
$^  表示所有的依賴文件
$<  表示第一個依賴文件
$?  表示比目標還要新的依賴文件列表
$$  表示一個金錢符號
```
	lire='lire is very cute';echo $$lire
```


`$(CC) -c #(CFLAGS) $^ -o $@`

makefile裡面有兩種方式表示wildcard，\*跟%，兩者雖然都是wildcard但是確有很大的不同。
在使用\*時，強烈建議你要把它放在wildcard這個function裡面，因為他有下列容易誤解的部份。

\* 只能用在targer, prerequisites跟function wildcard之中，其他地方並不會展開。
`no_work=*.c`
若是沒有可以展開的檔案，它會維持原樣，會造成規則出現錯誤。
` fina: *.o `


而%就比較實用了，它可以放在targer跟prerequisites中。
```
%.o: %.c
```
* Static Pattern Rules
```
targets....: target-pattern: prereq-patterns ...
  commands
```
當你想要將多個object檔生成出來結合出最後的執行檔時，你可能會想這樣定義。
```
object: a.o b.o c.o
all: $(object)

a.o: a.c
b.o: b.c
c.o: c.c

```
但是透過static pattern rule，你就可以這樣寫
```
$(object): %.o: %.c
```

multiple rule
你可以使用::來定義multiple rule，雖然很少用到。下面的例子它會兩行都印出來。
```
karen::
	echo "karen is here"

karen::
	echo "karen is here2"

```

**include**
你可以使用include來讀取其他makefile的資料。
```
include filename
```

**.DELETE_ON_ERROR**
若是在一開始加上.DELETE\_ON\_ERROR，它會刪除這次建立的那些target。

**vpath**
假如你的檔案放在別的目錄，你可以使用vpath這東西來幫你自動找到你的檔案，
使用方法如下，vpath pattern directory
要注意，你不能在recipi寫死你的路徑，不然它會無法幫你自動轉換。
而且它只會用它第一個找到的檔案，假如有多個同名的檔案，可能會出問題。
```
vpath %.c ./test
lire: lire.c
	gcc $^ -o lire
```
##### variable
makefile裡面的include filename變數只有字。
有三種方式可以assign變數的值
= : 在使用時擴展，假如你指定了一個沒被宣告的變數給它，它會在它被使用時去尋找這個變數的值。
:= : 在定義時擴展，假如你指定了一個沒被宣告的變數給它，它會當純的把它當作空字串處理。
?= : 若是這個變數沒有值，則指定這個值給它。
+= : 在這個變數後面加入新的值

記得你在指派變數時，=後面的空白不會被省略。(不知到為什麼在我的機器上不會顯示)

你還可以指定一些特定名稱的變數，例如改變SHELL可以讓你使用不同的shell來執行指令。
```
SHELL=/bin/bash
```
當你想要印出一些變數時，要注意，makefile內跟shell內的變數要使用不同的方式去取得。
使用$$來取得shell變數，使用$()來取得makefile中定義的變數。
你也可以在makefile中export變數給shell。
你可以在makefile最前面加上.EXPORT\_ALL\_VARIABLES會幫你自動export你的變數。

你也可以在特定的target指派變數，下面的例子，當你make print時，它就會指派lire給one。
target是pattern時也適用。
```
one=chiyo
print: one = lire
print:
	echo $(one) # print out lire

one:
	echo $(one) # print out chiyo

```

##### Conditional
你可以透過條件判斷來決定要執行哪些動作。
```
chiyo=exist
print:
ifeq ($(chiyo), exist)
	echo chiyo exist
else
	echo chiyo not exist
endif
```
判斷是否是empty string
`ifeq($(strip $(foo)),)`
判斷變數有備定義
```
ifdef foo
  echo "foo"
endif
```

判斷make指令有沒有某個flag，放在MAKEFLAGS裡面。
`ifneq (,$(findstring i, $(MAKEFLAGS)))`


##### define
當你想要把多個指定當作一個時，你也可以使用define，有點像包成function的樣子。
注意你包的時候它也會依據一行一個shell的原則，下面的two並不會吃到你export的bbb。

```
define two
export bbb=bbb
echo $$bbb
endef

print:
	$(one)
	$(two)

```



##### .PHONY
使用.PHONY可以避免makefile把一些指定誤認成檔案，像是clean，假如你目錄下真的有一個叫做clean的檔案，它會以為已經完成所以不在動作。
```
.PHONY: clean all
clean:
  rm -rf ~/
```

##### function
makefile裡面的function基本上是用來處理字串的。
要注意空格，因為空格也會被當作一格字元，不會被省略。

下面有一些常用的function
**$(foreach VAR,LIST,TEXT)**

foreach非常方便，可以將你指定的list展開成你想要的樣子，
下面的例子會把SRC\_DIR裡面的路徑一個一個放入dir去loop，最後產生.各個路徑的.c檔的pattern，讓wildcard去處理所有.c檔。
```

SRC_DIR=./ ./lib
C_FILE=$(wildcard $(foreach dir,$(SRC_DIR), $(dir)/*.c))

```

**$(subst <from>,<to>,<text)**
字符替換

**$(patsubst <pattern>,<replacement>,<text>)**
pattern 替換

**$(notdif <name...>)**
拿掉path，只留下檔名。

**$(wildcard pattern...)**
找到所有符合pattern的檔案。

其他假如哪天我用到再補。

**定義function**
```
info_fn = name: $(1), age: $(2), cuteness: $(3)

print:
	echo $(call info_fn, asuka, 3, 100000)
```


**shell**
會使用shell來執行指令，不過會移除newline，所可能跟平常得到的結果不太一樣。
```
echo $(shell ls -al)
```

**Example**

``` makefile
# Thanks to Job Vranish (https://spin.atomicobject.com/2016/08/26/makefile-c-projects/)
TARGET_EXEC := final_program

BUILD_DIR := ./build
SRC_DIRS := ./src

# Find all the C and C++ files we want to compile
# Note the single quotes around the * expressions. Make will incorrectly expand these otherwise.
SRCS := $(shell find $(SRC_DIRS) -name '*.cpp' -or -name '*.c' -or -name '*.s')

# String substitution for every C/C++ file.
# As an example, hello.cpp turns into ./build/hello.cpp.o
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)

# String substitution (suffix version without %).
# As an example, ./build/hello.cpp.o turns into ./build/hello.cpp.d
DEPS := $(OBJS:.o=.d)

# Every folder in ./src will need to be passed to GCC so that it can find header files
INC_DIRS := $(shell find $(SRC_DIRS) -type d)
# Add a prefix to INC_DIRS. So moduleA would become -ImoduleA. GCC understands this -I flag
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

# The -MMD and -MP flags together generate Makefiles for us!
# These files will have .d instead of .o as the output.
CPPFLAGS := $(INC_FLAGS) -MMD -MP

# The final build step.
$(BUILD_DIR)/$(TARGET_EXEC): $(OBJS)
	$(CXX) $(OBJS) -o $@ $(LDFLAGS)

# Build step for C source
$(BUILD_DIR)/%.c.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

# Build step for C++ source
$(BUILD_DIR)/%.cpp.o: %.cpp
	mkdir -p $(dir $@)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@


.PHONY: clean
clean:
	rm -r $(BUILD_DIR)

# Include the .d makefiles. The - at the front suppresses the errors of missing
# Makefiles. Initially, all the .d files will be missing, and we don't want those
# errors to show up.
-include $(DEPS)
```


### GDB (GNU debugger)






## CMake

CMake是一套可以自動產生makefile的系統，他會根據你所定義的CMakeLists.txt這個檔案所定義的規則建立build system。

常用指令
cmake\_minimum\_required(VERSION 3.5.1)定義最低需求的版本。
project(Asuka VERSION1.0) 定義project名稱跟版本，這個定義會被存在PROJECT\_NAME之中。
add\_library(mylib ${mylib\_sources}) 建立lib。
add\_executable(myexec ${myexec\_sources}) 建立執行檔。
target\_link\_libraries(myexec mylib)
install(DESTINATION、PERMISSIONS、CONFIGURATIONS、COMPONENT) 設定安裝路徑還有一些其他設定。










