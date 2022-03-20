
" basic
set number
set history=1000
set clipboard=unnamedplus
set cursorline
set noswapfile
set ruler
" auto indent
set ai
"太長時不換行
set nowrap

" space and tab
set softtabstop=2
set shiftwidth=2
set expandtab
" 顯示特殊字元
set list
set listchars=tab:>·,trail:~,extends:>,precedes:<,space:␣
"eol:¬,

"search
set hlsearch
set ignorecase
set incsearch
set smartcase

" tab
" 必定顯示tab
set showtabline=2
set splitbelow
set splitright


syntax on

filetype on
filetype indent on
filetype plugin on




" nore 是指說不要遞迴mapping
inoremap jk <Esc>

" disable 上下左右
noremap <Up> <Nop>
noremap <Down> <Nop>
noremap <Left> <Nop>
noremap <Right> <Nop>

" 自動補完括號
inoremap " ""<Esc>i
inoremap ' ''<Esc>i
inoremap ` ``<Esc>i
inoremap ( ()<Esc>i
inoremap [ []<Esc>i
inoremap {<CR> {<CR>}<Esc>ko<Tab>






















