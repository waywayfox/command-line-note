# CSS Note


## link to HTML
`<link rel="stylesheet" type="text/css" href="../css/style.css">`


## CSS Selectors

### Element
根據你的html tag來選擇。

```
tagName {
  color: red;
}
```

### Class
根據你的class來選擇。

```
.className {
  color: red;
}
```

### ID
根據你的ID來選擇。

```
#IDName {
  color: red;
}
```

### Pseudose Selector
在選擇器中在特別標注出某些狀況，像是hover, first-child, last-child, only-child, link, visisted
```
.className:hover {
  color: red;
}

.className:nth-child(n) {
  color: red;
}
```

### Child selector
你可以用這個指定你要選擇的element的父母。
有加>的話表示他們需要是直接的親子，而沒加表示只要在裡面就行。
```
ul > li {
  color: blue;

}

ul li {
  color: green;
}

```

### Advanced Selector
你可以用下面的方式來表示，緊接在什麼的什麼的style
\+ 代表著下一個，下面的例子是緊接在h2後面的a，就變成紅色。
~ 跟上面一樣，不過他們兩個必須是同一個parent。
```
h2 + a {
  color: red;

}

textarea ~ button {
  color: purple;
}
```
### Attribute Selector
除了上面幾種selector之外，你還可以使用tags所帶的attribute來找到你想要的element。
h2[attr]         含有某種attribute
h2[attr=value]   確切的包含某個attribute，不能有其他的
h2[attr^=value]  attribute的開頭包含指定的值
h2[attr$=value]  attribute的結尾包含指定的值
h2[attr\*=value] 需要包含指定的值
h2[attr|=value]  需要包含指定的值，且這個值要被空格或標點分開。
h2[attr~=value]  需要包含指定的值，且這個值是被空分隔的。

```
img[src^="../img/"] {
  border: 10px solid black;
}
```

## Priority
每一個selector都有優先度，當一個元素有被不同selector指到時，優先度大的會發會效果。
inline > id > class > tag


## Color
雖然有很多種顏色的表示方式，不過記三種就好，name, hex code, rgb。
```
color: blue;
color: #1e90ff;
color: rgb(24, 173, 67);
```

## Back ground
有很多種個property可以指定背景相關的屬性，如background-color或background-image之類的，不過你可以簡單的用backgroung來表示。
另外，url也可以使用多張圖片，在後面用逗點隔開就行。
```
  background: url("../img/lire.png");
  background: red;
  background-repeat: no-repeat; /* 不要用重複的圖片填滿 */
  background-size: 50px 100px;
  background-size: cover;
  background-size: contain;
```
### background-size
你可以用這來調整背景圖片的大小
```
  background-size: 50px 70%; /* 直接設定大小 */
  background-size: cover; /* 等比例縮放到能夠一張填滿的程度，有可能被裁切 */
  background-size: contain; /* 等比例縮放，不裁切 */
```







