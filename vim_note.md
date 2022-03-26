# VIM note

## 開啟
`vim -p file` 以分頁方式開啟
`vim -[oO] file` 以分割方式開啟`
`:e <file>` 在裡面開啟檔案



# 移動
`zz` 將目前的所在的游標至中。

## 搜尋
ignorecase 無視case
smartcase 在你搜尋有大寫時，則會無效ignorecase
`:noh` 關掉搜尋顯示的highlight


## 在vim 中使用指定

`:! <command>`
`:r ! <command>` 在目前位置貼上指定內容


## 折疊行
使用`zf`折疊選取行，用`l`展開。
可在後面加ia


## tab and windows
`:new` `vnew` 開啟空的分割視窗。
`:tabe <file>`開啟檔案在分頁
`CTRL-w [sv]` 分割視窗
`CTRL-w [<>+-]` 調整當前分割視窗的長寬


## keymapping
<leader> 預設是`\`，可以讓你更好擴充你的mapping，假如你想要使用的鍵已經被用掉，你可以在前面加個<leader>來使用它。
`map <leader>i >>`像是這樣，因為i已經有人用過了。
`:let mapleader = ","` 你可以這樣更換你的leader key
``<mode>unmap <key>`` 可以解除mapping
`<mode>mapclear` 解除這個模式的所有mapping

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

TODO: silver-searcher


## surround
`S`後面加你要的括號或引號
`ds` 後面加你要刪除的
`cs` 後面加你要改動的跟你要變成的










