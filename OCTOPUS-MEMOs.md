#OCTOPUS MEMOs

##Misc <a id="toc"></a>
* [What is the best way to merge mp3 files](#1)
* [Cannot connect to samba shared files after 4.1.14-1 upgrade.](#2)
* [Disk Utility in Linux](#3)
* [Linux运维](#4)
* [VPN相关](#5)
* [Markdown相关](#6)
* [VIM配置](#7)
* [Exact String Matching Algorithms](#8)
* [General Purpose Hash Function Algorithms](#9)
* [有用的博客](#10)
* [多路归并外排相关](#11)
* [ssh配置](#12)
* [apt-get using http_proxy](#13)
* [常用samba设置](#14)
* [linux查看端口占用情况](#15)
* [docker相关](#16)
* [using http_proxy](#17)
* [C99 array initializaers](#18)
* [usage of sed](#19)
* [usage of patch](#20)
* [ubuntu init](#21)
* [screen使用技巧](#22)

##What is the best way to merge mp3 files? <a id="1"></a>
[stackoverflow上的回答](http://stackoverflow.com/questions/62618/what-is-the-best-way-to-merge-mp3-files)

**Use ffmpeg or a similar tool to convert all of your MP3s into a consistent format, e.g.**
>ffmpeg -i originalA.mp3 -f mp3 -ab 128kb -ar 44100 -ac 2 intermediateA.mp3
>ffmpeg -i originalB.mp3 -f mp3 -ab 128kb -ar 44100 -ac 2 intermediateB.mp3

Then, at runtime, concat your files together:

>cat intermediateA.mp3 intermediateB.mp3 > output.mp3

Finally, run them through the tool MP3Val to fix any stream errors without forcing a full re-encode:

>mp3val output.mp3 -f -nb

##Cannot connect to samba shared files after 4.1.14-1 upgrade. <a id="2"></a>

[\[SOLVED\]cannot connect to samba server after upgrade](https://bbs.archlinux.org/viewtopic.php?id=190592)
[FS\#43015 - \[samba\] cannot connect to samba shared files after 4.1.14-1 upgrade](https://bugs.archlinux.org/task/43015)

See [\[SOLVED\] cannot connect to samba server after upgrade](https://bbs.archlinux.org/viewtopic.php?pid=1484501#p1484501) for some log comparisons between 4.1.13 and 4.1.14 taken moments apart and some cursory debugging. The problem is not so easily worked around for windows clients.

>EDIT: Looked at the upstream patch found at [patch-4.1.13-4.1.14.diffs.gz](http://samba.org/samba/ftp/patches/patch-4.1.13-4.1.14.diffs.gz) and found that they changed how the "smb_my_netbios_names" array is allocated in "samba-4.1.14/source3/lib/util_names.c" and must have broke "is_myname(cstring)". It's an upstream bug for sure.

>EDIT2: Super simple workaround! Just shorten your NETBIOS name by adding "netbios name=\[15 chars or less, simple ASCII chars only\]" to your smb.conf.

>EDIT3: Reported upstream: [samba-show-bug](https://bugzilla.samba.org/show_bug.cgi?id=11008)

[Troubleshooting Samba](https://www.samba.org/samba/docs/using_samba/ch12.html)

##Disk Utility in Linux <a id="3"></a>
###Disk scanning for badblocks
badblocks
mhdd

###Data recovery
safecopy
testdisk
photorec

##Linux运维 <a id="4"></a>
[Linux运维网](http://www.linuxyunwei.com)

##VPN相关 <a id="5"></a>
[使用 Strongswan 架设 Ipsec VPN](https://zh.opensuse.org/SDB:Setup_Ipsec_VPN_with_Strongswan)

##Markdown相关 <a id="6"></a>
[Markdown Cheatsheet](http://assemble.io/docs/Cheatsheet-Markdown.html)

[Anchor links in markdown](http://blog.justin.kelly.org.au/anchor-links-in-markdown/)

[Markdown open a new window link](http://stackoverflow.com/questions/3492153/markdown-open-a-new-window-link)

##<a id="7"></a>VIM配置
常用vim配置
```
set cindent shiftwidth=4
set ts=4
set listchars=tab:>-,trail:-
set list
set expandtab
set number

set encoding=utf8
set fileencodings=ucs-bom,utf-8,cp936,gb18030,big5,euc-jp,euc-kr,latin1
```
[turn off auto indent when pasting in vim](http://stackoverflow.com/questions/2514445/turning-off-auto-indent-when-pasting-text-into-vim)
```
:set paste
:set nopaste
```

[strongswan VPN配置](https://oogami.name/1467/)
[1](https://gist.github.com/losisli/11081793)
[2](https://wiki.archlinux.org/index.php/IPsec-based_VPN_Server_%28%E7%AE%80%E4%BD%93%E4%B8%AD%E6%96%87%29)
[3](https://raymii.org/s/tutorials/IPSEC_vpn_with_Ubuntu_15.04.html)
[4](https://zh.opensuse.org/index.php?title=SDB:Setup_Ipsec_VPN_with_Strongswan&variant=zh#ipsec.secrets)


##<a id="8"/>Exact String Matching Algorithms
[Exact String Matching Algorithms](http://www-igm.univ-mlv.fr/~lecroq/string/)


##<a id="9"/>General Purpose Hash Function Algorithms
[hash function](http://www.partow.net/programming/hashfunctions/)


##<a id="10"/>有用的博客
[菜鸟的自留地](http://blog.csdn.net/yang_yulei)

[gmarik](http://www.gmarik.info/)


##<a id="11"/>
[多路归并外排](http://sandbox.mc.edu/~bennet/cs402/lec/index.html)

##<a id="12"/>
[ssh配置](http://blog.chinaunix.net/uid-20710081-id-3266103.html)

##<a id="13"/>
[apt-get using http_proxy](https://help.ubuntu.com/community/AptGet/Howto#Setting_up_apt-get_to_use_a_http-proxy)
包括sudo是http_proxy的使用,在/etc/sudoers文件中修改.


##<a id="14"/>
常用samba设置
```
#设置 server 显示名称
netbios name = NASERVER
#设置访问方式
security = user
#设置软链接访问
allow insecure wide links = yes

 [share]
public = no
comment = NAS share
path = /home/huangleon/share
force user = huangleon
valid users = huangleon
read only = no
writable = yes
browsable = yes
wide links = yes
```

##<a id="15"/>

linux查看端口占用情况

同时需要必要的root权限

查看端口占用情况的命令：lsof -i

查看某一端口的占用情况： lsof -i:端口号


##<a id="16"/>

docker相关
[docker文档](https://docs.docker.com)

[通过http_proxy访问docker时的配置](https://docs.docker.com/engine/admin/systemd/#http-proxy)

docker的网络配置可以通过
```
docker run -it --net=host
```
来设置

##<a id="17"/>
Using HTTP_PROXY
[using http_proxy in pip](http://stackoverflow.com/questions/14149422/using-pip-behind-a-proxy)

Prefered using, (note its HTTPS_PROXY, not HTTP_PROXY)
```
export https_proxy=...
sudo -E pip install...
```

using ssh through http_proxy
```
     ProxyCommand
             Specifies the command to use to connect to the server.  The command string extends to the end of the line, and is executed using the user's shell ‘exec’ directive
             to avoid a lingering shell process.

             In the command string, any occurrence of ‘%h’ will be substituted by the host name to connect, ‘%p’ by the port, and ‘%r’ by the remote user name.  The command
             can be basically anything, and should read from its standard input and write to its standard output.  It should eventually connect an sshd(8) server running on
             some machine, or execute sshd -i somewhere.  Host key management will be done using the HostName of the host being connected (defaulting to the name typed by the
             user).  Setting the command to “none” disables this option entirely.  Note that CheckHostIP is not available for connects with a proxy command.

             This directive is useful in conjunction with nc(1) and its proxy support.  For example, the following directive would connect via an HTTP proxy at 192.0.2.0:

                ProxyCommand /usr/bin/nc -X connect -x 192.0.2.0:8080 %h %p

```

How to use ntpdate behind a proxy?
```
sudo date -s "$(wget -S  "http://www.google.com/" 2>&1 | grep -E '^[[:space:]]*[dD]ate:' | sed 's/^[[:space:]]*[dD]ate:[[:space:]]*//' | head -1l | awk '{print $1, $3, $2,  $5 ,"GMT", $4 }' | sed 's/,//')"
```

##<a id="18"/>
Development language
[C99 array initializers](http://gcc.gnu.org/onlinedocs/gcc-4.1.2/gcc/Designated-Inits.html)

```
int array[1024] = {[0 ... 1023] = 5};
```

##<a id="19"/>
usage of sed
[sed's RE is basic regular expression](http://unix.stackexchange.com/questions/90653/why-do-i-need-to-escape-regex-characters-in-sed-to-be-interpreted-as-regex-chara)


##<a id="20"/>
use 'patch' to patch code

```
patch -p1 -l --dry-run --verbose < patchfile
```

##<a id="21"/>
[ubuntu init.d scripts](http://unix.stackexchange.com/questions/133961/can-not-execute-restart-networking-service-on-ubuntu-14-04)

##<a id="22"/>
screen 记录log
Ctrl-a H
用more可以查看带escape标示的log文件

[\[Table of Contents\]](#toc)
