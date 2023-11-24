# 維維的socket筆記


## 什麼是socket

socket 是使用UNIX file descriptors 這個標準來跟其他程式溝通的一種方式。
所以說，在你需要在網路進行溝通時，你就需要一個file descriptor來幫妳做溝通的橋樑。


## Internet socket
Internet socket分成兩種，Stream Socket跟Datagram Socket。

Stream Socket是可靠的，他會保證你送的東西按照順序送達目標，因為他使用TCP，你需要先建立連線，才能開始送東西。
而Datagram Socket 則是使用UDP，所以你不一定需要建立穩定的連線，創建一個socket，給他一個目標IP，然後就送出，管他有沒有送到。


下面是一些基本的會用到的資料結構。
``` C
struct addrinfo {
    int ai_flags; // AI_PASSIVE, AI_CANONNAME 等。
    int ai_family; // AF_INET, AF_INET6, AF_UNSPEC
    int ai_socktype; // SOCK_STREAM, SOCK_DGRAM
    int ai_protocol; // 用 0 當作 "any"
    size_t ai_addrlen; // ai_addr 的大小，單位是 byte
    struct sockaddr *ai_addr; // struct sockaddr_in 或 _in6
    char *ai_canonname; // 典型的 hostname
    struct addrinfo *ai_next; // 鏈結串列、下個節點
};

struct sockaddr {
    unsigned short sa_family; // address family, AF_xxx
    char sa_data[14]; // 14 bytes of protocol address
};

struct sockaddr_in {
    short int sin_family; // Address family, AF_INET
    unsigned short int sin_port; // Port number
    struct in_addr sin_addr; // Internet address
    unsigned char sin_zero[8];// 與 struct sockaddr 相同的大小
};

struct in_addr {
    uint32_t s_addr; // that's a 32-bit int (4 bytes)
};
```

轉換字串至address struct, pton代表presentation to network。

```C

struct sockaddr_in sa;
struct sockaddr_in6 sa6;
inet_pton(AF_INET, "192.0.2.1", &(sa.sin_addr));
inet_pton(AF_INET6, "2001:db8:63b3:1::3490", &(sa6.sin6_addr));

char ip4[INET_ADDRSTRLEN]; // 儲存 IPv4 字串的空間
struct sockaddr_in sa; // 假裝這會由某個東西載入
inet_ntop(AF_INET, &(sa.sin_addr), ip4, INET_ADDRSTRLEN);
printf("The IPv4 address is: %s\n", ip4);

```

## 連線開始
### 事前準備
首先我們需要擁有目標的資料，當你遇到錯誤時，通常他們會回傳-1，並把errno設定成對應的錯誤，你可以用此來debug。
```C
int getaddrinfo(const char *node, // 例如： "www.example.com" 或 IP
                const char *service, // 例如： "http" 或 port number
                const struct addrinfo *hints,
                struct addrinfo **res);
```


下面是取得yahoo.com所對應的所有ip，當然在大部分的狀況下，你得到這些目標資料的struct就可以拿來做一些連線之類的事了。

```C
  struct addrinfo hints, *res, *p;
  int status;
  char ipstr[INET6_ADDRSTRLEN];

  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;

  if ((status = getaddrinfo("yahoo.com", NULL, &hints, &res)) != 0)
  {
    fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(status));
    return 1;
  }

  for (p = res; p != NULL; p = p->ai_next)
  {
    void *addr;
    char *ipver;

    if(p->ai_family == AF_INET)
    {
      struct sockaddr_in *ipv4 = (struct sockaddr_in *)p->ai_addr;
      addr = &(ipv4->sin_addr);
      ipver = "IPv4";
    }
    else
    {
      struct sockaddr_in6 *ipv6 = (struct sockaddr_in6 *)p->ai_addr;
      addr = &(ipv6->sin6_addr);
      ipver = "IPv6";
    }

    inet_ntop(p->ai_family, addr, ipstr, sizeof ipstr);
    printf(" %s: %s\n", ipver, ipstr);
  }
  freeaddrinfo(res);
```
### 創建socket
PF是指protocol family，而AF是address family。雖然說兩個值一樣，混用也不會有問題。不過socket是要指定protocol，所以用得是PF。
```C
int socket(int domain, // PF_INET, PF_INET6
           int type,   // SOCK_STREAM, SOCK_DGRAM
           int protocol); //option, tcp, udp
```

當你跟上面的範例一樣取得你想要進行的連線的資料時，就可以呼叫socket來創建了。
```C
int s;
s = socket(res_item->ai_family, res_item_socktype, res_item->ai_protocol);
```

### bind port
假如你是server而你想要listen機器上某個port，你會需要把這個socket綁在某個port上面，讓他來listen它。

```C
int bind(int sockfd, struct sockaddr *my_addr, int addrlen);
```
你從上面的socket()得到回傳的fd之後，就可以用得到的res來進行bind了。
記得要確認你要bind的port沒有被其他人使用。
```C
bind(sockfd, res_item->ai_addr, res_item->ai_addrlen);
```
假如你想重新啟動server，但卻發現bind失敗時，可能是上一次執行的東西還佔據這個port，你可以等一段時間讓他自己清除掉，或是這樣做
```C
int yes = 1;
setsockopt(listener, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));
```

### connect
終於我們可以開始連線了，拿你剛才創建socket得到的fd，還有用getaddrinfo拿到的資訊，就可以輕鬆連接到對方了。
要注意，假如你是client，你不會需要bind，因為kernel會自己幫我們選一個local port來處理連線。
```C
int connect(int sockfd, struct sockaddr *serv_addr, int addrlen);
connect(sockfd, res->ai_addr, res->ai_addrlen);
```

### listen & accept
假如你是server，當你bind好某個port，那你就可以開始監聽這個port了，除了你使用的fd外，你還要設定backlog，代表你能接受多少等待的request。
當你accept時他會給你一個新的fd，你會需要他用在之後的send跟recv。
```C
int listen(int sockfd, int backlog);
int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
```

### send & recv
接下來我們就可以開始接送資料了。
send 會回傳實際送的長度，因為你送的東西可能很大，假如沒辦法一次送完，你可能會需要用個迴圈來多次send之類的。
recv也差不多，只是會把資料讀到buf裡面，假如他回傳0的話，代表這個連線已經中止了。

假如你想要使用datagram socket，你可以使用sendto跟recvfrom，基本上使用方式跟上面兩個差不多，只是你要同時附上目標的資料而已。
```C
int send(int sockfd, const void *msg, int len, int flags);
sendto(int sockfd, const void *msg, int len, unsigned int flags, const struct sockaddr *to, socklen_t tolen);
int recv(int sockfd, void *buf, int len, int flags);
int recvfrom(int sockfd, void *buf, int len, unsigned int flags, struct sockaddr *from, int *fromlen);
```




























