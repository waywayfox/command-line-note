# SSH note


## SSH keygen

```
ssh-keygen -t rsa -b 4096
ssh-keygen -t dsa
ssh-keygen -t ecdsa -b 521
ssh-keygen -t ed25519

```

## ssh-add
```
ssh-add <private key path>
ssh-add -l/-L  # show all added key
ssh-add -D #remove all key
```

##查看目前支援的algorithms
Ciphers: ssh -Q cipher
MACs: ssh -Q mac
KexAlgorithms: ssh -Q kex
PubkeyAcceptedKeyTypes: ssh -Q key



Message ID                            Value    Reference
-----------                           -----    ---------
SSH_MSG_DISCONNECT                       1     [SSH-TRANS]
SSH_MSG_IGNORE                           2     [SSH-TRANS]
SSH_MSG_UNIMPLEMENTED                    3     [SSH-TRANS]
SSH_MSG_DEBUG                            4     [SSH-TRANS]
SSH_MSG_SERVICE_REQUEST                  5     [SSH-TRANS]
SSH_MSG_SERVICE_ACCEPT                   6     [SSH-TRANS]
SSH_MSG_KEXINIT                         20     [SSH-TRANS]
SSH_MSG_NEWKEYS                         21     [SSH-TRANS]
SSH_MSG_USERAUTH_REQUEST                50     [SSH-USERAUTH]
SSH_MSG_USERAUTH_FAILURE                51     [SSH-USERAUTH]
SSH_MSG_USERAUTH_SUCCESS                52     [SSH-USERAUTH]
SSH_MSG_USERAUTH_BANNER                 53     [SSH-USERAUTH]
SSH_MSG_GLOBAL_REQUEST                  80     [SSH-CONNECT]
SSH_MSG_REQUEST_SUCCESS                 81     [SSH-CONNECT]
SSH_MSG_REQUEST_FAILURE                 82     [SSH-CONNECT]
SSH_MSG_CHANNEL_OPEN                    90     [SSH-CONNECT]
SSH_MSG_CHANNEL_OPEN_CONFIRMATION       91     [SSH-CONNECT]
SSH_MSG_CHANNEL_OPEN_FAILURE            92     [SSH-CONNECT]
SSH_MSG_CHANNEL_WINDOW_ADJUST           93     [SSH-CONNECT]
SSH_MSG_CHANNEL_DATA                    94     [SSH-CONNECT]
SSH_MSG_CHANNEL_EXTENDED_DATA           95     [SSH-CONNECT]
SSH_MSG_CHANNEL_EOF                     96     [SSH-CONNECT]
SSH_MSG_CHANNEL_CLOSE                   97     [SSH-CONNECT]
SSH_MSG_CHANNEL_REQUEST                 98     [SSH-CONNECT]
SSH_MSG_CHANNEL_SUCCESS                 99     [SSH-CONNECT]
SSH_MSG_CHANNEL_FAILURE                100     [SSH-CONNECT]


