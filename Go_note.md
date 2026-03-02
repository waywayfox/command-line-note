
# 維維的Go筆記

## command

`go mod init <module_name>` 創建新的Go module，

`go run <file>`
執行一個go檔

`go build -o <output> <file>`
把檔案編譯成執行檔


`go test <path or package name>`
Go有內建的測試模組，可以直接用來測試，
檔名需要是xxx_test.go，並且引用testing這個package。
另外所有的test case需要是個function，且開頭為Test，並接受一個參數t *testing.T，且不用回傳任何東西。

-v 顯示詳細測試結果（verbose）
-cover 顯示測試覆蓋率
-failfast 發生錯誤就停止測試
-coverprofile 產生測試結果的檔案
-html 產生測試結果的 HTML 檔案
-short 跳過有 t.Skip 或 testing.Short() 的函式

t.Parallel() 叫測試可以同時跑其他case，節省時間。


`gofmt`
go 有幫你format的工具，可以告訴你該怎麼改才是正確的格式。還有go預設的indent是用tab。::
-d
	Do not print reformatted sources to standard output.
	If a file's formatting is different than gofmt's, print diffs
	to standard output.
-e
	Print all (including spurious) errors.
-l
	Do not print reformatted sources to standard output.
	If a file's formatting is different from gofmt's, print its name
	to standard output.
-r rule
	Apply the rewrite rule to the source before reformatting.
-s
	Try to simplify code (after applying the rewrite rule, if any).
-w
	Do not print reformatted sources to standard output.
	If a file's formatting is different from gofmt's, overwrite it
	with gofmt's version. If an error occurred during overwriting,
	the original file is restored from an automatic backup.


## Syntax

### var
一般來說宣告變數不需要使用var，但是下面幾種狀況應該要使用
(1) 宣告在最外層的不是常數的變數。
(2) 宣告並初始化單個或多個變數，記住
(3) 你知道這個變數可能會接收不同型別的值。
間單的判別方式，假如你要用這個型別的初始值，就用var，假如你要在定義時指派值，就用:=

### assign

:= 只適用於你想要單次使用這個變數時，如果你要更改這變數的值還是用=。
:= 只會在當前的scope有效。

### function
``` Go
func func_name(paramaters...) <return_list> {
  // comment is same as C
}

```

### Struct
```
type Customer struct {
    Name string
    Email string
}
```















