# Learn Vimscript the Hard Way

# Echoing Messages
echo 跟 echom 都會印出東西，不過echo會直接消失，若是你想印出點東西來debug的話，echom會是比較好的選擇，因為你的script會越來越大
你可以用`:messages` 來檢查印出來的東西。

 來檢查印出來的東西。


 ## Setting Options
Vim 裡面有兩種options,一種是boolean option(只會有on/off)，另一種則接受值。
所有boolean option都是同樣的設定方法，`:set <name>`跟`:set no<name>`
你可以用`:set number!`來toggle options，或用`:set number?`來查詢option的狀態。





