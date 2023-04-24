# 維維的openssl 小筆記


`openssl list` \
`openssl list-standard-commands | list-message-digest-commands | list-cipher-commands | list-cipher-algorithms |
             list-message-digest-algorithms | list-public-key-algorithms`
顯示支援的指令或演算法。在我的mac上是下面那種，可以用man openssl去查。


# Key Generate

openssl常見的key種類有以下4種
種類   | 格式     | 副檔名
-------|----------|--------
Base64 | PEM      | .pem, .crt, .cer, .key
Base64 | PKCS #7  | .p7b, .p7c
Binary | DER      | .cer, .der
Binary | PKCS #12 | .pfx, .p12


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
























