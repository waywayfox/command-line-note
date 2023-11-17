# 維維的openssl 小筆記

SSL(secure sockets layer)在1995年創立前後出了3個大版本，後來因為安全問題在1999年被TLS1.0取代，基本上就是SSL3.1。

`openssl list` \
`openssl list-standard-commands | list-message-digest-commands | list-cipher-commands | list-cipher-algorithms |
             list-message-digest-algorithms | list-public-key-algorithms`
顯示支援的指令或演算法。在我的mac上是下面那種，可以用man openssl去查。

# Cipher suite
`openssl ciphers -v 'ALL:COMPLEMENTOFALL'`
查看你的openssl所有支援的cipher suites

你會得到類似這樣的結果。 \
`ECDHE-RSA-AES256-SHA384 TLSv1.2 Kx=ECDH     Au=RSA  Enc=AES(256)  Mac=SHA384` \
從左到右分別代表的意思是
1. Suite name
2. Required minimum protocol version
3. Key exchange algorithm
4. Authentication algorithm
5. Encryption algorithm and strength
6. MAC (integrity) algorithm


# Key Generate

openssl常見的key種類有以下4種
種類   | 格式     | 副檔名
-------|----------|--------
Base64 | PEM      | .pem, .crt, .cer, .key
Base64 | PKCS #7  | .p7b, .p7c
Binary | DER      | .cer, .der
Binary | PKCS #12 | .pfx, .p12

現在PKCS7好像已經改用PKCS8了。

`openssl sha256 <file>` \
對檔案進行sha256的hash

`openssl rand -hex/base64 [-out <file>] <number>` \
產生一個隨機的密碼，number是byte。

`openssl genrsa [-out <file>] [<size>]` \
`openssl genrsa -aes256 -out key.pri.enc 4096` \
產生一個rsa private key，建議都要使用-out而不是>來輸出檔案，他們賦予的權限不同。
你可以加上要用什麼方式加密你的key的flag。

`openssl rsa -in <file> -noout -text`
顯示這個rsa key的詳細資料。

`openssl rsa -in <inputfile> -puboout -out <output_file>` \
輸出public key。

`openssl rsa -in key.pri -out key.der -outform DER` \
轉換pem到der。 \
`openssl rsa -in key.der -inform DER -noout -text`

要產生DSA跟ECDSA的key會先需要產生parameter的。

```
openssl dsaparam -out dsa.param 2048
openssl gendsa -des-ede3-cbc -out dsa.pri.enc dsa.param
```
產生DSA key。 \
`openssl dsa -in dsa.pri -pubout -out dsa.pub` \
轉換到公鑰的方式跟rsa大同小異。

`openssl ecparam -list_curves`
顯示ec所支援的curve格式。

```
openssl ecparam -name secp521r1 -out ecdsa.param
openssl ecparam -genkey -in ecdsa.param -noout -out ecdsa.pri
openssl ec -in ecdsa.pri -pubout -out ecdsa.pub
```
產生ecdsa key，第二行有noout是因為不加的話，產生出來的key會包含param的資料。
`openssl ec -in ecdsa.pri -out ecdsa.pri.enc -aes256`
加密用。


## genpkey
genpkey可以創建任何種類的private key。 \
`openssl genpkey -algorithm rsa -pkeyopt rsa_keygen_bits:2048 -out rsa2.pri` \
`openssl pkey -in rsa2.pri -noout -text` \
`openssl genpkey -algorithm ED25519 -out ed25519.pri` \
我的Mac上沒辦法建ed25519。



# 加密與解密
`openssl aes-256-cbc -in asuka.txt -out asuka.enc -e -kfile encryption.key` \
aes-256-cbc是cipher，-e代表encode加密。-kfile代表你key的檔案。
解密也是相同的格式把inout設定好後，把-e換成-d，decode解密就可以了。
你可以加-a，他就會用把加密的檔案以base64方式輸出或輸入。
如果你不給key file，他會要你輸入password。
-pbkdf2 是Password-Based Key Derivation Function，她會把你的key在強化過一次。
-iter pbkdf2的迭代次數，記得加解密時這些flag都要一樣。

`openssl rsautl -encrypt -inkey key.pub -pubin -in asuka.txt -out asuka.enc` \
`openssl rsautl -decrypt -inkey key.pri -in asuka.enc -out asuka.dec` \
使用rsa公鑰與私鑰加解密。




# Digital Signature

```
openssl rsautl -sign -inkey key.pri -in asuka.txt -out asuka.txt.sig
openssl rsautl -verify -inkey key.pub -pubin -in asuka.txt.sig
openssl sha1 -sign key.pri -out asuka.txt.sig asuka.txt
openssl sha1 -verify key.pub -signature asuka.txt.sig asuka.txt
openssl dgst -sha256 -sign key.pri -out asuka.txt.sig asuka.txt
openssl dgst -sha256 -verify key.pub -signature asuka.txt.sig asuka.txt

openssl sha256 -binary -out hash asuka.txt
openssl pkeyutl -sign -inkey ecdsa.pri -in hash -out asuka.txt.sig -pkeyopt digest:sha256
openssl pkeyutl -verify -pubin -inkey ecdsa.pub -in hash -sigfile asuka.txt.sig
```
對檔案加上簽章與驗證，下面的是hash-based signature。 \
用dgst查看更多可以使用的hash法。 \
也可以使用pkeyutl達到同樣的效果。 \


# HMAC & CMAC

你可以用HMAC或CMAC來加密檔案。
```
openssl sha1 -hmac <key> -out asuka.txt.sha1hmac asuka.txt
```


# Digital Certificates
CSR(Certificate Signing Request)
用來產生certification檔，通常副檔名是cer或csr。


`openssl req -new -x509 -key rsa.pri -sha256 -days 356 -out test.cer` \
產生self signed certificate，所謂的self signed certificate就是不由public的CA(trusted public certificate authorities)所發出的簽章。
而是由公司或是自己產生用來認證用的。 \
-new創建一個新的簽章，要創建的話一定要加。 \
-x509生成self signed certificate。

`openssl req -in test.csr -noout -text`
查看csr檔。

`openssl x509 -in test.cer -noout -text` \
查看self signed certificate。

`openssl req -new -x509 -newkey rsa:2048 -sha256 -nodes -days 356 -keyout rsa2048.pri -out test.cer` \
你如果不想自己先建立private key，你可以用-newkey跟-keyout一起建立。 \
-node不對private key進行加密。


`openssl req -new -x509 -key ecdsa.pri -days 365 -subj '/CN=Max/OU=AAA' -out test.cer` \
-sub可以讓你直接在command輸入那些基本資料。


`openssl req -new -x509 -newkey rsa:2048 -keyout rsa.pri -sha256 -nodes -days 356 -out test.cer -subj '/CN=Test' -addext "basicConstraints=critical,CA:true,pathlen:1"`
-addext加入extension，有哪些extensions可以用請查閱網路。

`openssl req -new -config fd.cnf -key fd.key -out fd.csr`
如果你有自己寫的config檔，你可以直接輸入，就不用在指令中打一大串了。

`openssl x509 -x509toreq -in test.cer -out test.csr -signkey rsa.pri`
你可以直接把x509轉成csr。

Basic Constraints表示這個簽章代表CA，讓他可以用這個證書簽署其他簽章。
Key Usage (KU) and Extended Key Usage (EKU)用來設定這key到底可以用在什麼地方。




