" 1. Vim general setting
set nu
set ts=4
set softtabstop=4
set shiftwidth=4
set expandtab
set autoindent
set cursorline
set laststatus=2

" 2. Vundle
set nocompatible              " be iMproved, required
filetype off                  " required
" set the runtime path to include Vundle and initialize
set rtp+=~/.vim/bundle/Vundle.vim
call vundle#begin()
  Plugin 'file://${HOME}/.vim/bundle/YouCompleteMe'
  Plugin 'file://${HOME}/.vim/bundle/cmake4vim'
  Plugin 'preservim/nerdtree'
  " Plugin 'puremourning/vimspector'
call vundle#end()            " required
filetype plugin indent on    " required

" 3. YouCompleteMe setting
nnoremap <leader>d :YcmCompleter GoToDefinition<CR>
nnoremap <leader>g :YcmCompleter GoTo<CR>

" 4. NERDTree
" Start NERDTree and put the cursor back in the other window.
autocmd VimEnter * NERDTree | wincmd p
" Exit Vim if NERDTree is the only window remaining in the only tab.
autocmd BufEnter * if tabpagenr('$') == 1 && winnr('$') == 1 && exists('b:NERDTree') && b:NERDTree.isTabTree() | quit | endif

" 5. vimspector
let g:vimspector_enable_mappings = 'HUMAN'
packadd! vimspector
syntax enable

" 6. cmake4vim
let g:cmake_vimspector_support = 1
let g:cmake_build_dir = "build"
