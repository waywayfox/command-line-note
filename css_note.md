# CSS Note


## link to HTML
`<link rel="stylesheet" type="text/css" href="../css/style.css">`

## Unit
有分兩種單位，絕對跟相對。
絕對單位
* cm
* mm
* in(2.54cm)
* px(1/96in)
* pt(1/72in)
* pc(12pt)

相對單位例如
em 相對於當前element的x倍大小
vw 相對於viewport width的幾%
vh 相對於viewport length的幾%


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
要指定透明度，使用rgba。
```
color: blue;
color: #1e90ff;
color: rgb(24, 173, 67);
background: rgba(39, 168, 3, 0.5);
```

## Back ground
有很多種個property可以指定背景相關的屬性，如background-color或background-image之類的，不過你可以簡單的用backgroung來表示。
另外，url也可以使用多張圖片，在後面用逗點隔開就行。
你可以使用linear-gradient, radial-gradient來製作有漸層的顏色。
用deg來指定角度。
```
  background: url("../img/lire.png");
  background: red;
  background-repeat: no-repeat; /* 不要用重複的圖片填滿 */
  background-size: 50px 100px;
  background-size: cover;
  background-size: contain;
  background: rgba(39, 168, 3, 0.5);
  background: linear-gradient(to right top, green, red, blue);
  background: linear-gradient(160deg, green, red, blue);
  background: radial-gradient(green 20%, red 40%, blue 55%);
  background: radial-gradient(circle, green, red, blue);
```
### background-size
你可以用這來調整背景圖片的大小
```
  background-size: 50px 70%; /* 直接設定大小 */
  background-size: cover; /* 等比例縮放到能夠一張填滿的程度，有可能被裁切 */
  background-size: contain; /* 等比例縮放，不裁切 */
```

## Text

### text manipulation
在文字上顯示線
```
  text-decoration: line-through; /* none, underline, overline, inherit */
```
對所有文字的大小寫做修正
```
  text-transform: capitalize; /* uppercase, lowercase */
```
置中，置左，置右
justify會讓你的所有文字行都使用同樣的行寬，不會因為最後的單字過長就被自動移到下一行。
```
  text-align: center; /* left, right, justify */
```


### Font
字體大小
```
  font-size: 2em;
```

字體粗細，它可以設定的數值跟字體有關，每種字體能設定的數值不同。
```
  font-weight: 100;
```
斜體
```
  font-style: italic; /* normal, oblique */
```
#### Font Family
font family讓你可以設定多種字體，當前面的字體無法使用時，使用後面的字體，用逗點隔開。
要指定自己，你可以直接標示字體名稱，或是使用通用family。

常用的通用familyserif, sans-serif, monosapce, cursive, fantasy等等。

```
  font-family: "Times New Roman", serif;
```

## 邊界

元素的三個邊界基本是下圖所示

```
______________________________________
|              MARGIN                |
|   _______________________________  |
|   |          BORDER             |  |
|   |  _________________________  |  |
|   |  |       PADDING         |  |  |
|   |  |  ___________________  |  |  |
|   |  |  |                 |  |  |  |
|   |  |  |    CONTENT      |  |  |  |
|   |  |  |                 |  |  |  |
|   |  |  ___________________  |  |  |
|   |  |                       |  |  |
|   |  -------------------------  |  |
|   |                             |  |
|   -------------------------------  |
--------------------------------------
```

### Border
style有許多可以選擇：none, dotted, inset, solid, dashed, double.
你可以用border-style來分別指定四個邊的style。
```
  border: size style color;
```

### Margin & Padding
你可以一次用2個或4個值來表示4周的間隔。

```
  padding-right: 40px;
  padding: 20px 30px 0px 50px;
  margin: 80px 30px;
```

## Layout

### Display
主要常用的有
* none 讓這個element看不到，也不會佔空間。
* block 這個element會佔用一個block的空間，會自己佔用一行的空間。
* inline 這個element並不會自己獨占一行，width跟height會無效化。
* contents 這個element只會佔用contents area的空間。
* inline-block 這個element並不會自己獨占一行，不過還是會佔用一個block的空間。
```
  display: inline-block;
```

### Float
float可以用element往某個方向漂浮,直到碰到邊界，或是另一個浮動的element。
常見的設定有none, left, right, inherit。
因為浮動element會重新排列附近的element，若希望哪個元素旁邊不要有浮動element，則要加上clear這個屬性。
```
  float: right;
  clear: both;
```

### Flexbox
要使用flex box，你要先將他的container的display設成flex。 \
使用flex-driection來指定flex container裡面element的排列順序。 \
使用flex-wrap來決定裡面的element要不要換行。 \
使用justify-content來決定裡面的element要置中左右哪一邊，還有間隔方式。 \
使用align-items來決定裡面的element要要靠上靠下，還有排列方式。 \
flex-basis表示這個元素在初始時，佔了多少大小。 \
flex-grow跟flex-shrink是決定說，當你的空間增加或減少，這個element要以多少的比率變大或變小。 \
你可以用flex來總結上面三個。 \
align-self可以用來指定每個element要往哪裡靠。

```
  display: flex;
  flex-direction: row-reverse;
  flex-wrap: wrap;
  justify-content: center;
  /* flex-end, flex-start, space-between, space-around */
  align-items: center;
  /* flex-start, flex-end, baseline, stretch */

  flex-basis: 100px;
  flex-grow: 1;
  flex-shrink: 0;
  flex: grow shrink basis;
  align-self: flex-start;

```


### Grid
要使用grid，先將container的display設成grid。
你可以使用grid-template-columns跟grid-template-rows來訂立有幾個row跟col，還有各自的長度，用auto會平均分配剩下的空間。
假如你需要很多行，可以用repeat來定義，更可以搭配minmax來定義最小最大，這樣可以達成自動根據螢幕大小改變行數。

grid-column跟grid-rows可以指定要佔用多少欄位，表示為 起始/結束，或是 起始/佔用span。
grid-area:可以結合上面兩個

```
  display: grid;
  grid-template-columns: auto auto auto;
  grid-template-rows: 50px 250px;
  grid-template-rows: repeat(6, 1fr);
  grid-template-columns: repeat(auto-fit, minmax(400px, 1fr));
  justify-content: space-evenly;
  /* center, end, start, space-around */
  align-content: space-between;

  grid-column-gap: 80px;
  grid-row-gap: 80px;
  grid-gap: column row;

  grid-column: 1/3;
  grid-row: 1/span2;
  grid-area: row-start / column-start / row-size / column-size
  grid-area: 2 / 1 / span 2 / span 3

```

## Transition
使用transition可以讓你指定的property在發生變化時，使用相對應的transition
你可使用s或ms來指定時間。
要注意每個瀏覽器所支援的transition不同，若是想要在所有瀏覽器上都可以看到變化，則要加上前綴。
```
  transition: property duration function delay;
  -webkit-transition: all 300ms ease-in-out;
  -moz-transition: background 300ms linear;
  -m-transition: font-family 1.5s ease 2s;

```
## Transform
transform可以讓你對element進行縮放，平移，旋轉，傾斜。
下面列出一些常見的。
matric可以讓一次使用多個屬性，不過很難讀，建議不要使用。
還有它跟transition一樣，你可能會需要加上前綴。
```
  transform: trasnlate(120px, 50%);
  transform: scale(2, 0.5);
  transform: rotate(0.5turn);
  transform: scale(0.5) skew(30deg, 20deg);
  transform: trasnlate(120px, 50%);
  transform: trasnlate(1, 2, 3, 4, 5, 6);
```

## Animation
你可能會覺得要幫所要要動畫的element個別寫transition太麻煩了，那你可以使用animation，只要寫一次，然後就可以apply到你想要的element了。
首先你要定義keyframe，如果你只有兩個狀態，你可以使用from跟to就好，如果你想更明確的指定每個階段的狀態，可以用百分比。
```
@keyframes red-to-black {
  from {
    background: red;
  }

  to {
    background: black;
  }

  0% {
    background: red;
    translate(0px, 0px);
  }

  50% {
    background: yellow;
    translate(20px, 20px);
  }

  100% {
    background: black;
    translate(40px, 40px);
  }
}
```

接下來，你需要把keyframe assign給element，然後設定這些東西，你可以用animation總結6種property。
你一樣需要注意瀏覽器有沒有支援。
```
  animation-name: red-to-black; /* 指定keyframe */
  animation-duration: 10s; /* 動畫時間 */
  animation-timing-function: ease-in-out;
  animation-delay: 2s;
  animation-iteration-count: infinite; /* 重複次數 */
  animation-direction: reverse; /* 方向 */
  animation: red-to-black 4s linear 0s 2 reverse

```

















