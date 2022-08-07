# VIM note

## 開啟
`vim -p file` 以分頁方式開啟
`vim -[oO] file` 以分割方式開啟
`:e <file>` 在裡面開啟檔案

# 移動
當人你可以用lkjh來移動，或是用}{來進行section的移動，不過還有更多移動。
查詢various-motions得到更多資訊,<number>gg可以移動到指定行數，G可以移動到最後一行。

## 搜尋
ignorecase 無視case
smartcase 在你搜尋有大寫時，則會無效ignorecase
`:noh` 關掉搜尋顯示的highlight
這樣可以搜尋你要的pattern，有更多匹配模式可以查magic。
`/<pattern>`

若是你要取代一些東西，可以查usr_12.txt
最基礎的方式是這樣，%代表所有行，flag放g的話，就能替換所有行裡所有match的部份了。
```
:%s/<origin pattern>/<replace pattern>/<flag>
```

假如在某些搜尋下導致你的vim顯示 有些怪，你可能需要使用redraw。


## Help

搜尋使用
`:h keyword`

若是你的快捷鍵並不是在normal mode下，在前面加上<mode>_<shortcut>
`:h i_CTRL-O`
`CTRL-]` 跳轉到當前游標所在的關鍵字
`CTRL-o` 跳到上一個地方


## 在vim 中使用指定

`:! <command>` \
`:r ! <command>`或 `!}<command>` 在目前位置貼上指定內容

## 折疊行
使用`zf`折疊選取行，用`l`展開。
可在後面加ia
有幾種folding的方式，請參考folding或是vim script的部份。

## tab and windows
`:new`
`vnew` 開啟空的分割視窗。
`:tabe <file>`開啟檔案在分頁
`CTRL-w [sv]` 分割視窗
`CTRL-w [<>+-]` 調整當前分割視窗的長寬

## keymapping
可以讓你更好擴充你的mapping，假如你想要使用的鍵已經被用掉，你可以在前面加個<leader>來使用它。
`map <leader>i >>`像是這樣，因為i已經有人用過了。
`:let mapleader = ","` 你可以這樣更換你的leader key
``<mode>unmap <key>`` 可以解除mapping
`<mode>mapclear` 解除這個模式的所有mapping
`<nop>` 你可以把key mapping到這個東西上，他什麼都不做。
`nnoremap <buffer> <leader>x dd` 在前面加上<buffer>可以讓這個mapping只存在當前buffer, 不過當你這樣做時，使用<localleader>會比較好。

## nerdtree
`:NERDTreeToggle` 切換進入nerdtree的window
在nerdtree window裡面操作
`m` 對檔案進行處理
`[st<CR>]`
`C` 切換到這個目錄

## ctrlp
use `Ctrl-p` to open.
In search mode, use `Ctrl` to toggle file search mode or all path search.
More info: https://github.com/ctrlpvim/ctrlp.vim

## surround
`S`後面加你要的括號或引號
`ds` 後面加你要刪除的
`cs` 後面加你要改動的跟你要變成的

## bookmark
使用bookmark你可以跳到你所記錄的位置，每個buffer都可以在a~z紀錄各自的bookmarks，但是大寫的A~Z是紀錄global的書籤。

你可以用'或是\`來跳轉到書籤位置，差別只在你會停在當初紀錄的位置還是那一行的開頭。

use `m[a-z]` to set the bookmark. \
use `` `[a-z] `` to move to bookmark. \
use `:marks` to check the bookmarks you save. 後面加上字母就可差看單獨的書籤位置。

`` ]` `` 跟`` [` `` 可以跳到下一個或上一個小寫書籤的位置。

下面是一些特殊的marks \
`` `. `` 回到當前buffer上一次改動的地方 \
`` `" `` 回到上一次離開時的位置 \
`` `[0-9] `` 回到上一次離開vim時的檔案，0是上一個，之後以此類推。 \
``` `` ``` 點擊兩次回到上一個地方

`` `] `` 回到前一個或後一個修改或複製的位置 \
`` `> `` 回到上一次visual mode的開頭或結尾

當你砍掉你設置marks的那一行，marks他也會一起被砍掉。
當你:bw 一個buffer時，同時也會刪掉這個buffer的marks。

`:delmarks ab` 刪掉a跟b裡面存的bookmarks \
`:delmarks!` 刪掉所有小寫的bookmarks


## digraph
特殊字元，你可以查詢24.9，在insert mode打<c-k> <組合>來打出你想要的字。




