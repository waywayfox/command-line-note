# Learn Vimscript the Hard Way

## Echoing Messages
echo 跟 echom 都會印出東西，不過echo會直接消失，若是你想印出點東西來debug的話，echom會是比較好的選擇，因為你的script會越來越大
你可以用`:messages` 來檢查印出來的東西。

 來檢查印出來的東西。


## Setting Options
Vim 裡面有兩種options,一種是boolean option(只會有on/off)，另一種則接受值。
所有boolean option都是同樣的設定方法，`:set <name>`跟`:set no<name>`
你可以用`:set number!`來toggle options，或用`:set number?`來查詢option的狀態。
`:setlocal` 可以讓你只針對當前的buffer進行設定，不過若這個options只有globla，就依然會對所有buffer起作用。


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
你也可以把function存在variable裡面，不過這個變數一定要大寫開頭。
```
:let Myfunc = function("Append")
```
也可以被存在list中
```
:let funcs = [function("Append"), function("Pop")]
:echo funcs[1](['a', 'b', 'c'], 1)
```

## String
注意在你使用
`echo`跟`echom`時，特殊符號會有時會有不同的顯示方式，例如`\n`。
你可以使用單引號，來印出確切你打了什麼，打兩個單引號在裡面表示一個單引號。
`echo 'that''s right'`
`:h expr-quote`查詢更多特殊符號。
你可以用在insert mode使用i_CTRL_V，這可以讓你直接輸入你下一個打的特殊字元。



## normal execute
normal會連map一起算進去，如果你不想要你打的東西被map的話，要加上!才行。
你該永遠使用`normal!`。
在使用normal時，如果你要undo你的指令，它會一次全部undo，你可以用下面這東西來避免，如果你需要的話。
CTRL-G u	break undo sequence, start new change	     *i_CTRL-G_u*

你可以結合execute搭配normal，因為normal並不會認出特殊字元，execute則會，至於特殊字元你可以`:h expr-quote`，
下面作法可以讓你打出一些特出字元組合。
\<xxx>	Special key named "xxx".  e.g. "\<C-W>" for CTRL-W.
下面這一行會在這一行最後面加上分號
```
:execute "normal! mqA;\<esc>`q"
```

你可以類似這樣的方來搜尋，在預設模式下，你需要使用\+來表示多個字元，這裡使用兩個\\是因為他在execute裡面，需要用兩個\來表示一個。
```
  :execute "normal! gg/for .\\+ in .\\+:\<cr>"
```

之前我們有提到，可以用單引號來表示確切的字，所以你可以這樣用
```
:execute "normal! gg" . '/for .\+ in .\+:' . "\<cr>"
```


## Regular expression
查詢`:h magic`跟`:h pattern-overview`來知道更多。


## grep
首先grep這個指令，可以搜尋文件中的pattern，並把結果放進quickfix windows裡面，讓你可以快速換到那些地方，有點像是全域搜索，
<cword>跟<cWORD>是個特殊符號，會抓到現在游標的字，兩種抓的範圍不同。
下面的指令雖然在一般的單字可以用，但是假如單字裡有'的話，就會失敗。
`:nnoremap <leader>g :execute "grep -R '<cWORD>' ."<cr>`
這裡使用shellescape來嘗試，不過還是無法成功，因為它會在你轉換<cWORD>之前就先呼叫shellescape了，這讓它只是在外面加了''。
查詢`:h escape()`跟`:h shellescape()`獲得更多資訊。
`
:nnoremap <leader>g :execute "grep -R " . shellescape("<cWORD>") . " ."<cr>
`
要解決這個問題，我們可以使用expand這個function，它會把裡面的特殊符號先進行轉換，這樣我們就可以順利的把我們游標所在的字轉換成安全的表示了。
`
:nnoremap <leader>g :execute "grep! -R " . shellescape(expand("<cWORD>")) . " ."<cr>:copen<cr>
`
最後可以寫出這樣的結果，grep!是不要跑到第一個結果，copen則是打開quickfix windows，假如有多個結果，用:cp跟:cn來切換。
經過測試後用vertical copen並不是一個好選擇，因為我的螢幕太小除了檔名前面外看不到其他資訊。

但我們不只要把它變成一個搜尋游標下單字的mapping，而是要把它變成一個operator。
下面逐行解說他下面的東西再做什麼。
前兩行的mapping，會在兩種模式下你按下<leader>g時觸發你定義的function。g@後面會讀取你的motion。
<SID>會根據每個script有不同的值，可以用來更好的分別它屬於那一個script，當你有很多plugin時避免衝突。
在function中，我們先存下當前的unnamed register，之後在貼回去。
接著我們就判斷它傳進來的type，我們只接受char跟v兩種模式的grep因為其他模式就不是應該用grep的東西了。
總之我們將兩者複製下來，它沒有標示目標，所以就被存進@@裡。
之後我們就呼叫grep，並把quickfix window打開。

```
nnoremap <leader>g :set operatorfunc=<SID>GrepOperator<cr>g@
vnoremap <leader>g :<c-u>call <SID>GrepOperator(visualmode())<cr>

function! s:GrepOperator(type)
  let saved_unnamed_register = @@
  if a:type ==# 'v'
    execute "normal! `<v`>y"
  elseif a:type ==# 'char'
    execute "normal! `[v`]y"
  else
    return
  endif

  " after ynak the last select word or range, call grep
  " @@ is unnamed register
  silent execute "grep! -R " . shellescape(@@) . " ."
  copen 10
  let @@ = saved_unnamed_register
endfunction
```

## List
你可以用[<e1>, <e2>]來定義list，就跟普通array的使用方式一樣，支援負數引索
你可以在後面加上範圍來slice這個array
`
:echo ['a', 'b', 'c', 'd', 'e'][0:2]
`
對string也有效，不過要注意string不支援負數index，但是可以用在slice上
`
:echo "abcd"[-1] . "abcd"[-2:]
`
用加號來結合兩個list
`
:echo [1, 3, 5] + [2, 4]
`

下面列出一些支援的function，注意reverse會更新原本的list
`
  :let foo = ['a']
  :call add(foo, 'b')
  :echo foo " ['a', 'b']
  :echo len(foo) " 2
  :echo get(foo, 0, 'default') " a
  :echo get(foo, 100, 'default') " default
  :echo index(foo, 'b') " 1
  :echo index(foo, 'nope') " -1
  :echo join(foo) " a b
  :echo join(foo, '---') " a---b
  :echo reverse(foo) " ['b', 'a']
`


## loop
vim裡面有兩種loop，for跟while，兩種都很簡單，用`:h for`跟 `:h while`去查就好。下面附上簡易的結構。
也可以使用break跟continue。
### for
for 只能用在遍尋object。
```
  :let c = 0
  :for i in [1, 2, 3, 4]
  :  let c += i
  :endfor
```

### while
while 可以設定條件。
```
  :let c = 1
  :let total = 0

  :while c <= 4
  :  let total += c
  :  let c += 1
  :endwhile
```

## Dictionary
基本上就javascript的object，除了["index"]外，用點也可以，要注意一點是他會把你的index換成string，
remove能做的是比較齊全，不過unlet做的事也差不多，看個人喜好，不過unlet會拋出錯誤當你想刪除不存在的index。
另外，Dictionary並不保證順序是你插入的順序。
`
:echo {'a': 1, 100: 'foo',}['a']
:echo {'a': 1, 100: 'foo',}.a
:let foo.b = 200
:let test = remove(foo, 'a')
:unlet foo.b
:echom get({'a': 100}, 'a', 'default')
:echom has_key({'a': 100}, 'a') " 1
:echom has_key({'a': 100}, 'b') " 0
:echo items({'a': 100, 'b': 200}) " [['a', 100], ['b', 200]]
:echo keys({'a': 100, 'b': 200}) " ['a', 'b']
:echo values({'a': 100, 'b': 200}) " [100, 200]
`

## Path
你可以用一些expand來抓住現在的路徑
`
:echom expand('%:p')
`
你也可以用下面這個東西來取得你想要檔案的路徑，後面的表現方式可以查filename-modifiers。
`
  :echom fnamemodify('foo.txt', ':p')
`
simplify()則可以簡化你現在輸入的路徑。
globpath則可以抓到你指定路徑下的檔案，用第二個參數來輸入你想要抓的檔案的pattern，使用wildcard的pattern來辨別，
你可以用split來分離他們。
```
  :echo globpath('.', '*')
  :echo split(globpath('.', '*'), '\n')
  :echo split(globpath('.', '*.txt'), '\n')
```


## Syntax
要進行syntax的判定，有三種方式，一種是直接把個別的keyword分成不同的group，在指定給vim內建的group來分顏色，
另一種則是使用regex來判定，第三種是設定region，也就是設定開頭跟結尾。
```
syntax keyword potionKeyword if elsif else
highlight link potionKeyword Keyword

syntax match potionOperator "\v-\="
highlight link potionOperator Operator

syntax region potionString start=/\v"/ skip=/\v\\./ end=/\v"/
highlight link potionString String
```

查詢group-name來知道更多group
假如同一段文字被對應到多個group，則以下列規則分類，參見 syn-priority。

## folding
有不同的方式可以設定折疊，請參照`:help usr_28`
基本上使用zf可以手動設定折疊，zc跟zo是關和開，zr跟zm是全部的開與關。
其他方式可以參照上面的usr_28。

使用indent時，會根據你的縮排來設定要不要folding，你還可以設定foldlevel要縮多少才會被fold。

使用marker的話就是用一些字元排列來當作開始跟結束的標示，預設是{{{}}}，雖然很彈性，不過會需要增加多餘的行數。

當你使用expr來當作folding的方法時，你要自己定義你的foldexpr，vim會對每一行執行你所寫的function，它需要回傳他的foldlevel，
並跟據foldlevel來製作這些folding，除了數字外，它還有一些特殊的字串來表示folding，你可以查fold-expr。


## Section
一般來說，你可以使用{跟}來進行section的移動，除此之外，[[, ]], [], ][也可以用來進行section的移動，
不過因為它遵照的則是很久之前的檔案了，所以你可以重新定義section的移動，讓你在你想要的filetype更好的移動，
更詳細的例子請參考vim-wayway-potion裡的section，
首先，你需要重新思考你到底需要怎樣的移動方式，是移動到下一空行，移動到下一個function，還是其他移動方式，
跟之前mapping的概念相同，你需要重新定義這些section的移動方式，讓它呼叫你指定的function。
注意這裡我們使用noremap，並沒有用nnoremap是因為我們想要在operator-pending mode也使用它，像是d]]之類的。
另外就是visual mode下的前進跟後退。
```
noremap <script> <buffer> <silent> ]] :call <SID>NextSection(1, 0, 0)<cr>
vnoremap <script> <buffer> <silent> ]] :<c-u>call <SID>NextSection(1, 0, 1)<cr>
```
下面的例子只會讓你移動到下一個foo的位置，不過你可以了解他的概念，基本上利用搜尋的方式前往下一個你設計的pattern，
你也可以用search()之類的，看個人喜好。
```
function! s:NextSection(type, backwards)
    if a:backwards
        let dir = '?'
    else
        let dir = '/'
    endif

    execute 'silent! normal! ' . dir . 'foo' . "\r"
endfunction
```

## External command
你可以使用:!<cmd>來執行外部的指令，用這個，你也可以經由mapping來做出一些方便的設定，
例如，編譯當前的檔案之類的，這樣你就不用每次退出vim編譯完再進來了，
```
function! s:PotionCompileAndRunFile()
  write
  silent !clear
  execute "!" . g:potion_command . " " . bufname("%")
endfunction
```

經過一些方式，例如system()，可以讓你取得command得到的結果，甚至開啟另一個split來存放這個結果。
```
  let bytecode = system(g:potion_command . " -c -V " . bufname("%") . " 2>&1")
  vsplit __Potion_Bytecode__
  call append(0, split(bytecode, '\v\n'))
```




