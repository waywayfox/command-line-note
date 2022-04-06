# Learn Vimscript the Hard Way
# Echoing Messages
echo 跟 echom 都會印出東西，不過echo會直接消失，若是你想印出點東西來debug的話，echom會是比較好的選擇，因為你的script會越來越大
你可以用`:messages` 來檢查印出來的東西。

 來檢查印出來的東西。


## Setting Options
Vim 裡面有兩種options,一種是boolean option(只會有on/off)，另一種則接受值。
所有boolean option都是同樣的設定方法，`:set <name>`跟`:set no<name>`
你可以用`:set number!`來toggle options，或用`:set number?`來查詢option的狀態。


## abbreviations
Vim裡面，你可以定義縮寫，它有點像keymapping, 但只用在insert, replace跟cmd mode。
你可以用來處理錯字或是一些常用的輸入。
`iabbrev adn and`
`iab ms Microsoft`
`:iabbrev @@    steve@stevelosh.com`
當你在insert mode時，當你輸入任何非keyword的字元，它就會檢查並替換。
`:set iskeyword?` 你可以用這個來查詢keyword是哪些。


## autocmd
`:autocmd <event> <pattern> <command>`
你可以使用autocmd對各個FileType的文件進行特別的處理，結合mapping跟abbrev，創造自己的snippet跟快捷鍵。
當你建立不同的autocmd時，就算你指定同樣的事件，它也並不會覆蓋掉之前的。
需要注意的是，當你`source ~/.vimrc`的時候，它其實是重新讀了一次那些autocmd，會讓你重複定義這些autocmd，太多次甚至可能讓vim變慢。
為了解決這個問題，你可以把autocmd集結成augroup

## Operator-Pending Mapping
除了一般的mapping之外，你還可以定義自己想要的範圍。
`:onoremap p i(` 這代表說你把p這個範圍重新定成inner ()。
`onoeremap b /return<cr>` 這個則是把b換成現在到return前的東西。
`onoremap in( :<c-u>normal! f(vi(<cr>` 你也可以這樣來獲取範圍，<c-u>是刪除目前輸入的command，因為當他在選取時，其實會進入visual mode，所以先把選取範圍全刪掉，在用normal!執行選取的指令。
在設立mapping時，記住他有兩種規則，它最後進行動作的範圍，是(1)visual mode選則的範圍，跟(2)初始位置跟新位置中間的所有文字。
要注意normal! 沒辦法辨認出特殊字元，像是`<cr>`。有幾個可以繞過這個問題的方法，其中一個就是使用`execute`
所以下面這一行指令，會先把\r換成enter，而不是單純的看成4個字元。使用`:h pattern-overview`來查訊更多轉換。
`:onoremap ih :<c-u>execute "normal! ?^==\\+$\r:nohlsearch\rkvg_"<cr>`


## status line
status line是顯示在最下面的那個狀態欄，你可以自己定義它。
`:set statusline=%f\ -\ FileType:\ %y` 它會把對應的資料放進你想要的地方並顯示出來。
不過更好編寫的方式是分成數行來寫，比較好管理。
```
:set statusline=%f
:set statusline+=\ -\
:set statusline+=FileType:
:set statusline+=%y
```
`%=`可以讓你換到右邊。

## variable
你可以使用let來設定變數，也可以用這個方法來抓到設定的option跟register。
在使用option時要在前面加上`&`，若是你想要的是local option，則是使用`&l:`。
`let &number = 1`
`let &l:number = 1`
使用register時是用`@`
`:let @a = "asuka!"`
另外你要搜尋的字串存在`@/`裡面。
如果你要定義local的變數，則需要在前面加上`b:`,
代表給只給這個buffer用，去查internal-variables找更多其他可用的前綴。
`:let b:hello = "world"`


## conditions
```
if <>

elseif <>

else

endif
```
要注意，==的行為跟你的設定是有關的，假如你設定`:set ignorecase`那它就會無視大小寫。
永遠不要相信使用者的設定，你該使用`==?`無視大小寫跟`==#`分辨大小寫來進判斷。
雖然在比較數字時沒差，不過你該永遠使用`==#`來做判斷。
`:h expr4`查詢更多比較符號。


## functions
function的名稱一定要大寫開頭。
`:call Meow()`你可以這樣呼叫你寫的function。

```
function GetAsuka()
  echom "asuka1"
  return "asuka"
endfunction
```
假如你沒有指定它回傳什麼，它就會回傳0。
假如你要複寫已經存在的function，使用`:function! <functionName>()`。
要取得你傳進來的參數，永遠要在前面加上`a:`才行。
你也可以用下面的方式抓取你要的參數
```
:function Varg(...)
:  echom a:0 " 2
:  echom a:1 " asuka
:  echo a:000 ["asuka", "fuuka"]
:endfunction

:call Varg("asuka", "fuuka")
```
不過這些只能用在...上面
```
:function Varg2(foo, ...)
:  echom a:foo " asuka
:  echom a:0   " 2
:  echom a:1   " fuuka
:  echo a:000  " ["fuuka", "fina"]
:endfunction

:call Varg2("asuka", "fuuka", "fina")
```
你沒辦法直接修改傳進來的參數，不過你可以這樣做
```
:function AssignGood(foo)
:  let l:foo_tmp = a:foo
:  let l:foo_tmp = "Yep"
:  echom l:foo_tmp
:endfunction

:call AssignGood("test")
```


## String
注意在你使用
`echo`跟`echom`時，特殊符號會有時會有不同的顯示方式，例如`\n`。
你可以使用單引號，來印出確切你打了什麼，打兩個單引號在裡面表示一個單引號。
`echo 'that''s right'`
`:h expr-quote`查詢更多特殊符號。
你可以用在insert mode使用i_CTRL_V，這可以讓你直接輸入你下一個打的特殊字元。



## normal
normal會連map一起算進去，如果你不想要你打的東西被map的話，要加上!才行。
你該永遠使用`normal!`。
在使用normal時，如果你要undo你的指令，它會一次全部undo，你可以用下面這東西來避免，如果你需要的話。
CTRL-G u	break undo sequence, start new change	     *i_CTRL-G_u*



