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

[\[Table of Contents\]](#toc)
