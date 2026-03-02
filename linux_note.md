# 維維狐的linux小筆記


## Directory


Program Directory
* bin: binary檔
* sbin: binary檔，只給superuser用
* lib: library檔
* libexec: library檔會用到的執行檔
Document Directory
* doc
* info
* man
* share
Configuration Directory
* etc
* init.d
* rc.d
Hardware directory
* dev: Device files for interfacing with disks and other hardware
* mnt, misc: Mount points: directories that provide access to disks
Runtime directory
* var: 放系統執行中，常態性變動的檔案。
* lock
* log
* mail
* run: PID files, which contain the IDs of running processes; these files are often consulted to track or kill particular processes。
* spool: Files queued or in transit, such as outgoing email, print jobs, and scheduled jobs
* tmp
* proc Operating system state



## User
有兩個有關帳號的重要檔案，分別是/etc/passwd跟/etc/shadow


passwd裡面的格式如下，你可能會看到password的部分是x，這是因為passwd這個檔是大家都可以看到的，所以之後就會把更重要的東西放到shadow裡面了。
`asuka:asuka:600:600:testing:/home/asuka:/bin/sh`
User Name:Password:UID:GID:Remark(註解):Home Directory:Shell
(1) User Name: 系統上的名稱，第一行必須是superuser，接著是系統用的帳號(用來執行sync，shutdown等等的)，最後才是普通使用者的帳號。
(2) Password: 密碼，假如你看到是x的話，則說明密碼資訊被存到shadow裡了。
(3) UID:
    UID裡面有三種規則
    UID == 0: superuser
    UID 1 ~ 500 system user(給一些系統程式用的)
    UID > 500 normal user
(4) GID: 跟UID類似的規則。
(5) Remark: 註解，說明
(6) Home Directory: Home Directory要用絕對路徑
(7) Shell: 使用的shell。

shadow只有superuser 可以讀(700)
格式是
User Name:Password:Last:May:Must:Warn:Expire:Disable:Reserved:
(1) User Name: 跟passwd相同。
(2) Password: 被加密過後的密碼，若是空白的話則代表不用密碼就能登入，若是!或!!則代表這個帳號被鎖住了，不能登入。
(3) Last: 上次更改密碼的時間，大多是1970年經過的天數。
(4) May: 密碼不可修改天數，0表示一直都可以改。
(5) Must: 密碼的有效日期，需要在這個時間內再次更改密碼，如果是99999則表示永久有效。
(6) Warn: 假如有設定Must，則會在這個天數內警告使用者。
(7) Expire: 過期容許時間，就算超過有效期間，這個設定的時間內還是可以用。
(8) Disable: 失效日期，到這日期就強制失效。
(9) Reserved: 保留欄位。

在/etc/group裡面則存有群組資訊
Group Name:Password:GID:Users in Group
(1) Group Name: 群組名稱
(2) Password: 群組密碼，假如是x則跟user一樣，參照gshadow。但通常比較少用群組登入，所以是空白居多。
(3) GID: GID
(4) Users in Group: 所有在這群組的人，用逗號(,)隔開。


### passwd
passwd可以幫你更改有關passwd跟shadow裡的資訊。
`passwd [--option] [USER_NAME]`
-d 刪除密碼
-l 鎖住密碼
-u 解鎖密碼
-f 強制，有時你會需要-fu來強制解鎖密碼
-n 更改May
-x 更改Must
-w 更改Warn
-i 更改Expire
-S 輸出密碼的簡易資訊

```
useradd guest; passwd –d guest ←建立一個不用登入密碼的公用臨時帳號〝guset〞
passwd aaa ←變更帳號〝aaa〞的密碼
passwd -l aaa ←鎖住〝aaa〞帳號(同〝/etc/shadow〞的密碼欄(第二欄)的開頭加上〝!〞或〝!!〞)
passwd -u aaa ←解除〝aaa〞鎖住的帳號(密碼欄開頭的〝!〞或〝!!〞拿掉)
passwd -S bbb ←輸出帳號〝bbb〞的密碼簡易資訊
passwd -x 100 bbb ←設定帳號〝bbb〞有效天數為 100天(同修改〝/etc/shadow〞中的第 5 欄為 100)
```

### useradd
只有superuser可以執行，創建一個使用者，會同時建立一個跟使用者同名的group。
一開始創建的使用者會被鎖住，記得要用passwd來設定密碼，或是用-fu讓他不需要密碼。
-c 註解
-d 指定Home Directory
-g 指定group
-m 同時創建Home Directory
-r 表示這是系統帳號，創建出來的UID會小於500
-s 指定使用的shell

### userdel
刪除使用者
-r 同時刪掉Home directory裡面的所有東西。








