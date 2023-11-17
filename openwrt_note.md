# OPENWRT note




## UCI system
UCI的全名是Unified Configuration Interface，使用來集中管理openwrt裡的各個module。
所有的設定會被切成好幾個檔案，被存在/etc/config/裡面。
你可以用任何方式修改這些設定檔，不過你需要重新啟動那些service才能讓設定生效，通常使用init.d call，可以參見下面的Init Scripts。

```
/etc/init.d/network restart
```
基礎的設定檔的語法是這樣的
config開始定義一個module的section，timeserver是type，而ntp是名稱。
名稱只能含有英文字跟底線，名稱也不一定要給，不過在設定時就要用module.@\<type\>來設定。
而在她之下可以設定option跟list，option後面要先加上type，然後是當前的設定值。
假如type是boolean，你可以使用'0', 'no', 'off' 'false'代表false，而'1' , 'yes', 'on' 'true'來代表true。
list後面加上他所屬的list的名稱，然後他會跟據順序加入。
語法上只會認空格，所以請盡量使用引號把value括起來。
```
package 'example' #這一行不一定有

config timeserver 'ntp'
        list server '0.us.pool.ntp.org'
        list server '1.us.pool.ntp.org'
        list server '2.us.pool.ntp.org'
        list server '3.us.pool.ntp.org'
        option enabled '1'
        option enable_server '0'
        option ntpserver1addr '0.us.pool.ntp.org'
        option ntpserver2addr '1.us.pool.ntp.org'
```
### 基礎操作
當你使用了set, add, delete, rename之後，你需要commit它，你剛才設定的東西才會被寫到設定檔中。
export，import是導出或導入一個設定檔。
change會列出目前所有未儲存的設定。
```
Usage: uci [<options>] <command> [<arguments>]

Commands:
    batch
    export     [<config>]
    import     [<config>]
    changes    [<config>]
    commit     [<config>]
    add        <config> <section-type>
    add_list   <config>.<section>.<option>=<string>
    show       [<config>[.<section>[.<option>]]]
    get        <config>.<section>[.<option>]
    set        <config>.<section>[.<option>]=<value>
    delete     <config>[.<section[.<option>]]
    rename     <config>.<section>[.<option>]=<name>
    revert     <config>[.<section>[.<option>]]

Options:
    -c <path>  set the search path for config files (default: /etc/config)
    -d <str>   set the delimiter for list values in uci show
    -f <file>  use <file> as input instead of stdin
    -m         when importing, merge data into an existing package
    -n         name unnamed sections on export (default)
    -N         don't name unnamed sections
    -p <path>  add a search path for config change files
    -P <path>  add a search path for config change files and use as default
    -q         quiet mode (don't print error messages)
    -s         force strict mode (stop on parser errors, default)
    -S         disable strict mode
    -X         do not use extended syntax on 'show'
```


### command line
dmesg		print or control the kernel ring buffer
logread		Shows the messages from syslogd (using circular buffer)
cat /proc/version
cat /proc/meminfo		more detailed info about RAM usage
cat /proc/cpuinfo		info about your CPU
cat /proc/mtd
cat /proc/partitions
cat /proc/net/nf_conntrack
cat /proc/cmdline
cat /proc/modules


下面是對應功能的設定檔
|  File      | Description |
| ------------- |-------------  |
| Basic    |
| /etc/config/dhcp| Dnsmasq and odhcpd settings: DNS, DHCP, DHCPv6 |
| /etc/config/dropbear| SSH server options |
| /etc/config/firewall| NAT, packet filter, port forwarding, etc. |
| /etc/config/network| Switch, interface and route configuration: |
General, IPv4, IPv6, Routes, Rules, WAN, Aliases, Switches, VLAN, IPv4/IPv6 transitioning, Tunneling
| /etc/config/system| Misc. system settings, NTP, RNG, Watchcat |
| /etc/config/wireless| Wireless settings and wifi network definition |
IPv6
| /etc/config/ahcpd| Ad-Hoc Configuration Protocol (AHCP) server and forwarder configuration |
| /etc/config/dhcp6c| WIDE-DHCPv6 client |
| /etc/config/dhcp6s| WIDE-DHCPv6 server |
| /etc/config/gw6c| GW6c client configuration |
Other
| /etc/config/babeld| babeld configuration |
| /etc/config/bbstored| BoxBackup server configuration |
| /etc/config/ddns| Dynamic DNS configuration (ddns-scripts) |
| /etc/config/dnscrypt-proxy| DNSCrypt proxy |
| /etc/config/dockerd| The Docker CE Engine Daemon |
| /etc/config| E-MailRelay: simple SMTP server and proxy with POP support. Package emailrelay |
| /etc/config/etherwake| Wake-on-Lan: etherwake |
| /etc/config/freifunk_p2pblock| Uses iptables layer7-, ipp2p- and recent-modules to block p2p/filesharing traffic |
| /etc/config/fstab| Mount points and swap |
| /etc/config/hd-idle| Another idle-daemon for attached hard drives |
| /etc/config/httpd| Web server options (Busybox httpd, deprecated) |
| /etc/config/ipset-dns| Configure ipset-dns |
| /etc/config/kadnode| KadNode p2p DNS |
| /etc/config/luci| Base LuCI config |
| /etc/config/luci_statistics| Configuration of Statistics packet |
| /etc/config/mini_snmpd| mini_snmpd settings |
| /etc/config/minidlna| MiniDLNA settings |
| /etc/config/mjpg-streamer| Streaming application for Linux-UVC compatible webcams |
| /etc/config/mountd| OpenWrt automount daemon |
| /etc/config/mroute| Configuration files for multiple WAN routes |
| /etc/config/multiwan| Simple multi WAN configuration |
| /etc/config/mwan3| Multi-WAN config with load balancing and failover |
| /etc/config/nodogsplash| nodogsplash configuration |
| /etc/config/ntpclient| Getting the correct time |
| /etc/config/nut_server| Controlling a UPS (Uninterruptible Power Supply) and/or sharing with other hosts |
| /etc/config/nut_monitor| Monitoring a UPS (Uninterruptible Power Supply) from a remote host or local nut-server |
| /etc/config/nut_cgi| Web UI for NUT (viewing only in UCI) |
| /etc/config/p910nd| config for non-spooling Printer daemon p910nd.server |
| /etc/config/pure-ftpd| Pure-FTPd server config |
| /etc/config/qos| Implementing Quality of Service for the upload |
| /etc/config/racoon| racoon IPsec daemon |
| /etc/config/samba| settings for the Microsoft file and print services daemon |
| /etc/config/snmpd| SNMPd settings |
| /etc/config/sqm| SQM settings |
| /etc/config/sshtunnel| Settings for the package sshtunnel |
| /etc/config/stund| STUN server configuration |
| /etc/config/tinc| tinc package configuration |
| /etc/config/tor| Tor configuration |
| /etc/config/tor-hs| Tor hidden services configuration |
| /etc/config/transmission| BitTorrent configuration |
| /etc/config/uhttpd| Web server options (uHTTPd) |
| /etc/config/upnpd| miniupnpd UPnP server settings |
| /etc/config/users| user database for different services |
| /etc/config/ushare| uShare UPnP server settings |
| /etc/config/vblade| vblade userspace AOE target |
| /etc/config/vnstat| vnstat downloader settings |
| /etc/config/wifitoggle| Toggle WiFi with a button |
| /etc/config/wol| Wake-on-Lan: wol |
| /etc/config/znc| ZNC bouncer configuration |



## Init Scripts
當你要操作一個service，我們會使用init script來啟動。
通常他會提供下面這幾個操作，start, stop, restart, reload, enable, disable。
你會需要在script的一開始定義START跟STOP兩個變數，範圍在1~99，這代表的是當他要開始或結束時的優先順序。
當兩個檔案有同樣的優先順序時，他會根據字母大小來決定誰先。
你需要給檔案加上可執行的權限。

你還可以提供boot跟shutdown，當開機或關機時他會執行一次。
你可以定義EXTRA_COMMANDS來加上自定義的command。

