set nocompatible

if has("syntax")
    syntax on            " 语法高亮
endif
colorscheme ron

set ignorecase
set autowrite        " 自动把内容写回文件
set autoindent        " 设置自动对齐(缩进)；使用 noautoindent取消设置
"set smartindent        " 智能对齐方式
set tabstop=4        " 设置制表符(tab键)的宽度
set softtabstop=4     " 设置软制表符的宽度
set shiftwidth=4    " (自动) 缩进使用的4个空格
set cindent            " 使用 C/C++ 语言的自动缩进方式
"set cinoptions={0,1s,t0,n-2,p2s,(03s,=.5s,>1s,=1s,:1s     "设置C/C++语言的具体缩进方式
set showmatch        " 设置匹配模式，显示匹配的括号
set linebreak        " 整词换行
set whichwrap=b,s,<,>,[,] " 光标从行首和行末时可以跳到另一行去
set number            " Enable line number    "显示行号
set history=50        " set command history to 50    "历史记录50条

imap <S-Tab> <Esc><<i
nmap <S-Tab> <Esc><<
nmap <Tab> <Esc>>>
vmap <C-L> <C-V><S-I>//<Esc>
vmap <C-K> <C-V>lx<Esc>

noremap <silent><F5> <Esc>:! clear && g++ -std=c++11 % -o vimout && ./vimout <CR>

