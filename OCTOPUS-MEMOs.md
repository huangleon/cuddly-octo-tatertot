# OCTOPUS MEMOs

## Misc <a id="toc"></a>

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
* [ssh配置](#12)
* [常用samba设置](#14)
* [linux查看端口/文件占用情况](#15)
* [docker相关](#16)
* [using http_proxy](#17)
* [C99 array initializaers](#18)
* [usage of sed](#19)
* [usage of patch](#20)
* [ubuntu init](#21)
* [screen使用技巧](#22)
* [build kernel相关](#23)
* [使用lvm管理磁盘](#24)
* [Android相关](#25)
* [python开发相关](#26)
* [SELinux相关](#27)
* [k8s相关](#28)
* [openssl相关](#29)
* [curl使用](#30)
* [C++ 相关](#31)
* [算法和数据结构](#32)
* [git/svn相关](#33)
* [工具相关](#34)
* [usage of jinja2](#35)
* [C++ coding style](#36)
* [linux相关](#37)
* [File permission and ACLs](#38)
* [HTTP 协议相关](#39)
* [scons相关](#40)
* [编译器相关](#41)
* [VMWare相关](#42)
* [Networking相关](#43)
* [iOS相关](#45)
* [Multi-threading](#46)

<a id="1" />
## What is the best way to merge mp3 files ? 

[stackoverflow上的回答](http://stackoverflow.com/questions/62618/what-is-the-best-way-to-merge-mp3-files)

**Use ffmpeg or a similar tool to convert all of your MP3s into a consistent format, e.g.**

>ffmpeg -i originalA.mp3 -f mp3 -ab 128kb -ar 44100 -ac 2 intermediateA.mp3

>ffmpeg -i originalB.mp3 -f mp3 -ab 128kb -ar 44100 -ac 2 intermediateB.mp3

Then, at runtime, concat your files together:

>cat intermediateA.mp3 intermediateB.mp3 > output.mp3

Finally, run them through the tool MP3Val to fix any stream errors without forcing a full re-encode:

>mp3val output.mp3 -f -nb

<a id="2" />
## Cannot connect to samba shared files after 4.1.14-1 upgrade.

[\[SOLVED\]cannot connect to samba server after upgrade](https://bbs.archlinux.org/viewtopic.php?id=190592)
[FS\#43015 - \[samba\] cannot connect to samba shared files after 4.1.14-1 upgrade](https://bugs.archlinux.org/task/43015)

See [\[SOLVED\] cannot connect to samba server after upgrade](https://bbs.archlinux.org/viewtopic.php?pid=1484501#p1484501) for some log comparisons between 4.1.13 and 4.1.14 taken moments apart and some cursory debugging. The problem is not so easily worked around for windows clients.

>EDIT: Looked at the upstream patch found at [patch-4.1.13-4.1.14.diffs.gz](http://samba.org/samba/ftp/patches/patch-4.1.13-4.1.14.diffs.gz) and found that they changed how the "smb_my_netbios_names" array is allocated in "samba-4.1.14/source3/lib/util_names.c" and must have broke "is_myname(cstring)". It's an upstream bug for sure.

>EDIT2: Super simple workaround! Just shorten your NETBIOS name by adding "netbios name=\[15 chars or less, simple ASCII chars only\]" to your smb.conf.

>EDIT3: Reported upstream: [samba-show-bug](https://bugzilla.samba.org/show_bug.cgi?id=11008)

[Troubleshooting Samba](https://www.samba.org/samba/docs/using_samba/ch12.html)

<a id="3" />
## Disk Utility in Linux

### Disk scanning for badblocks

badblocks
mhdd

### Data recovery
safecopy
testdisk
photorec

<a id="4" />
## Linux运维

[Linux运维网](http://www.linuxyunwei.com)

[nginx配置中使用环境变量](https://docs.apitools.com/blog/2014/07/02/using-environment-variables-in-nginx-conf.html)

[nginx.conf中替换环境变量](http://serverfault.com/questions/577370/how-can-i-use-environment-variables-in-nginx-conf)

<a id="5" />
## VPN相关

[使用 Strongswan 架设 Ipsec VPN](https://zh.opensuse.org/SDB:Setup_Ipsec_VPN_with_Strongswan)

<a id="6" />
## Markdown相关

[Markdown Cheatsheet](http://assemble.io/docs/Cheatsheet-Markdown.html)

[Anchor links in markdown](http://blog.justin.kelly.org.au/anchor-links-in-markdown/)

[Markdown open a new window link](http://stackoverflow.com/questions/3492153/markdown-open-a-new-window-link)

<a id="7" />
## VIM配置

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

<a id="8" />
## Exact String Matching Algorithms

[Exact String Matching Algorithms](http://www-igm.univ-mlv.fr/~lecroq/string/)

<a id="9" />
## General Purpose Hash Function Algorithms

[hash function](http://www.partow.net/programming/hashfunctions/)

<a id="10"/>
## 有用的博客

[菜鸟的自留地](http://blog.csdn.net/yang_yulei)

[gmarik](http://www.gmarik.info/)

<a id="12"/>
## ssh配置

[ssh配置](http://blog.chinaunix.net/uid-20710081-id-3266103.html)

[ssh auto-logout 在screen中自动退出的问题](http://www.adercon.com/ac/node/39)

<a id="14"/>
## 常用samba设置
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
create mask = 0664
directory mask = 0775
```

<a id="15"/>
## linux查看端口占用情况

同时需要必要的root权限

查看端口占用情况的命令：
>lsof -i

查看某一端口的占用情况：
>lsof -i:端口号

查看文件占用情况:
>fuser filename

[How to list opened ports](https://apple.stackexchange.com/questions/117644/how-can-i-list-my-open-network-ports-with-netstat)

<a id="16"/>
## docker相关

[docker文档](https://docs.docker.com)

[通过http_proxy访问docker时的配置](https://docs.docker.com/engine/admin/systemd/#http-proxy)

[修改docker data存储路径](https://forums.docker.com/t/how-do-i-change-the-docker-image-installation-directory/1169)

[docker容器挂在volume,容器的数据(db)写出,permission denied问题](http://www.projectatomic.io/blog/2015/06/using-volumes-with-docker-can-cause-problems-with-selinux/)

[docker运行log查看](http://stackoverflow.com/questions/30969435/where-is-the-docker-daemon-log)
```
sudo journalctl -fu docker.service
```

[docker和selinux相关]()
启动docker-daemon时的参数 --selinux-enabled 会导致一些permission denied的问题,在开发调试过程中我们可以把它关掉.如host和container要共享/var/run/docker.sock进行通信.

[或者使用这个模块解决/var/run/docker.sock共享的问题](https://github.com/dpw/selinux-dockersock)

[selinux相关内容](https://wiki.centos.org/HowTos/SELinux)

docker配置文件
ubuntu:
/etc/default/docker
centos:
/etc/sysconfig/docker
/etc/sysconfig/docker-storage

docker的网络配置可以通过
```
docker run -it --net=host
```
来设置

<a id="17"/>
## Using HTTP_PROXY

[using http_proxy in pip](http://stackoverflow.com/questions/14149422/using-pip-behind-a-proxy)

[using socks5 proxy](https://askubuntu.com/questions/35223/syntax-for-socks-proxy-in-apt-conf)

[apt-get using http_proxy](https://help.ubuntu.com/community/AptGet/Howto#Setting_up_apt-get_to_use_a_http-proxy)
包括sudo是http_proxy的使用,在/etc/sudoers文件中修改.

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

<a id="18"/>
## Development language
[C99 array initializers](http://gcc.gnu.org/onlinedocs/gcc-4.1.2/gcc/Designated-Inits.html)

```
int array[1024] = {[0 ... 1023] = 5};
```

<a id="19"/>
## usage of sed
[sed's RE is basic regular expression](http://unix.stackexchange.com/questions/90653/why-do-i-need-to-escape-regex-characters-in-sed-to-be-interpreted-as-regex-chara)

<a id="20"/>
## use 'patch' to patch code

```
patch -p1 -l --dry-run --verbose < patchfile
```

<a id="21"/>
## ubuntu init

[ubuntu init.d scripts](http://unix.stackexchange.com/questions/133961/can-not-execute-restart-networking-service-on-ubuntu-14-04)

<a id="22"/>
## screen使用技巧

screen 记录log
Ctrl-a H
用more可以查看带escape标示的log文件

[putty上使用screen后的scrollback](http://serverfault.com/questions/32313/putty-and-screen-and-scroll-back-buffer)

[clear screen after using vim in screen](http://serverfault.com/questions/270103/gnu-screen-clearing-on-vim-less-etc-exit)

<a id="23"/>
## build kernel相关

[在ubuntu平台上重新编译kernel及使用新kernel](https://www.howtoforge.com/kernel_compilation_ubuntu)

用apt-get安装必要包,kernel-package libncurses5-dev fakeroot
准备好linux kernel的source code(打好patch的)

复制当前系统的kernel配置到source code目录下
```
cp /boot/config-`uname -r` ./.config
```
```
make menuconfig
```
Load .config file from local directory and save.
build kernel

```
make-kpkg clean
fakeroot make-kpkg --initrd --append-to-version=-custom kernel_image kernel_headesr
```
build好deb之后,可以安装linux-image和linux-headers的deb包

纯kernel的安装方法
```
# build kernel
make
# install zimage to boot
sudo make install
# install ko to /lib/modules
sudo make modules_install
# update /etc/default/grub for timeout variable
# update grub list
sudo update-grub
# install headers to /usr/src
INSTALL_HDR_PATH=/usr/src/linux-headers-$(uname -r) sudo make headers_install 
```

<a id="24"/>
## 使用lvm管理磁盘

[使用lvm管理磁盘扩容](https://www.rootusers.com/how-to-increase-the-size-of-a-linux-lvm-by-adding-a-new-disk/)

<a id="25"/>
## Android System UIDs inconsistent的解决方法

Check the file /data/system/uiderrors.txt for inconsistent uids.

[You Need MANAGE_USERS permission](http://forum.xda-developers.com/showthread.php?t=1999383)

[How to replace java 8 with java 7 on Mac OS](https://www.java.com/en/download/help/mac_uninstall_java.xml)

[How to switch java version on Mac OS](http://stackoverflow.com/questions/21964709/how-to-set-or-change-the-default-java-jdk-version-on-os-x#24657630)

[How to remove java 8 on MacOS](http://stackoverflow.com/questions/17885494/how-can-i-change-mac-oss-default-java-vm-returned-from-usr-libexec-java-home#20994919)

[How to check java version in ant](http://www.asjava.com/ant/how-to-check-java-version-in-ant/)


[Ant error 'javac1.8 class not found'](http://stackoverflow.com/questions/20702626/javac1-8-class-not-found)

<a id="26"/>
## Python搭建虚拟开发环境

```
pip install virtualenv
```
创建开发环境
```
virtualenv flask
cd flask
source bin/activate
pip install ...
```
退出开发环境
```
deactivate
```
导出开发环境需要的软件包
```
pip freeze > requirements.txt
```
导入开发环境需要的软件包
```
pip install -r requirements.txt
```

[lldb not working with brewed python](https://github.com/Homebrew/legacy-homebrew/issues/47201)

<a id="27"/>
## 关闭SELinux
```
sudo setenforce 0
```

SELinux 配置文件
```
sudo vim /etc/sysconfig/selinux
#SELINUX=enforcing
SELINUX=permissive
```
<a id="28"/>
## k8s相关

[heapster无法获取时间不同步的node的metrics](https://github.com/kubernetes/heapster/issues/516)

[heapster的'time synchronization'问题](https://github.com/kubernetes/heapster/issues/802)

<a id="29"/>
## openssl 相关

[openssl使用](https://www.digitalocean.com/community/tutorials/openssl-essentials-working-with-ssl-certificates-private-keys-and-csrs)

[Android上(certificate recovation list)未检查的问题](https://commonsware.com/blog/2014/04/18/more-android-revoked-ssl-certificates.html)

[der/pem/crt/cer file type](http://info.ssl.com/article.aspx?id=12149)

<a id="30"/>
## cURL的使用问题

http_proxy的环境变量只能用小写,不能用大写,manpage里有说明
>The environment variables can be specified in lower case or upper case. The lower case version has precedence. http_proxy is an exception as it is only available in lower case.

设置了http_proxy之后,不使用proxy可以用如下:
```
curl --noproxy '*' ...
```

About reuse connections in cURL

[Connection reuse](https://ec.haxx.se/libcurl-connectionreuse.html)

[How to reuse connect in cURL](http://stackoverflow.com/questions/972925/persistent-keepalive-http-with-the-php-curl-library/982556#982556)

[How to link libcurl statically](http://stackoverflow.com/questions/20461682/linking-project-with-statically-build-curl#20467476)

<a id="31"/>
## C++相关

[c++ vtable](http://shaharmike.com/cpp/)

[C++相关](http://blog.csdn.net/anzhsoft)

[C++ faq from BJ](http://www.stroustrup.com/bs_faq2.html)

[Differences between 'static' and 'extern'](http://stackoverflow.com/questions/92546/variable-declarations-in-header-files-static-or-not#93663)

[右值引用](http://thbecker.net/articles/rvalue_references/section_01.html)

[const and linkage](http://stackoverflow.com/questions/12042549/constants-only-header-file-c#12043198)

[Differences between 'libstdc++' and 'libc++'](http://stackoverflow.com/questions/14972425/should-i-use-libc-or-libstdc)

[Some issues about libc++ and libstdc++ on MAC](http://stackoverflow.com/questions/19637164/c-linking-error-after-upgrading-to-mac-os-x-10-9-xcode-5-0-1)

STL

[How to securely clear containers data](http://stackoverflow.com/questions/3785582/how-to-write-a-password-safe-class)


[Secure programming in C++](http://etutorials.org/Programming/secure+programming/)

<a id="32"/>
## 算法相关

[多路归并外排](http://sandbox.mc.edu/~bennet/cs402/lec/index.html)

[算法和数据结构](http://lib.csdn.net/base/datastructure)

[海量和数据处理](http://blog.csdn.net/v_july_v/article/details/7382693)

[算法在线课程](http://julyedu.com)

[Concurrency VS Parallelism](https://www.quora.com/What-is-the-difference-between-concurrency-and-parallelism)

<a id="33"/>
## git/svn 相关

[gerrit deny force-push](https://groups.google.com/forum/#!topic/repo-discuss/kPglQJIDQh0)

[git patch](http://stackoverflow.com/questions/5120038/is-it-possible-to-cherry-pick-a-commit-from-another-git-repository#9507417)

[convert git patch to svn patch](http://stackoverflow.com/questions/708202/git-format-patch-to-be-svn-compatible#13377540)

[convert svn patch to git](http://stackoverflow.com/questions/659467/how-to-apply-svn-diff-to-git#38655007)

[Mirror copy a git repo](http://blog.plataformatec.com.br/2013/05/how-to-properly-mirror-a-git-repository/)

[SVN diff doesnot contain 'new added directory'](http://stackoverflow.com/questions/4248768/including-new-files-in-svn-diff)

svn propset 的语法

```
svn ps svn:externals PROP_VALUE PATH
PROP_VALUE: '^/thirdparty-allversions/external/libcurl/source/scripts scripts'
PATH: .\source\libcurl-7.50.3\jenkins\
```

<a id="34"/>
## 工具相关

[绘制sequence diagram](https://www.websequencediagrams.com)

[How to select different network adapter to use in windows 10](https://answers.microsoft.com/en-us/windows/forum/windows_10-networking/adapter-priority-setting-unavailable-in-windows-10/d2b63caa-e77c-4b46-88b5-eeeaee00c306#ThreadAnswers)

<a id="35"/>
## About shoggoth

[shoggoth produce multiple variables using jinja2](http://jinja.pocoo.org/docs/2.9/templates/#assignments)

[jinja variables scope in block](http://stackoverflow.com/questions/4870346/can-a-jinja-variables-scope-extend-beyond-in-an-inner-block)

<a id="36"/>
## Coding style

[C++ coding style](http://geosoft.no/development/cppstyle.html)

[Prefer suffix than prefix underscore](http://stackoverflow.com/questions/1228161/why-use-prefixes-on-member-variables-in-c-classes#1228199)

[Guru of the Week](http://www.gotw.ca/gotw/)

<a id="37"/>
## linux相关

[fstab格式](https://wiki.archlinux.org/index.php/fstab)

[Touchscreen HID USB protocol](https://forum.pjrc.com/threads/32331-USB-HID-Touchscreen-support-needed)

<a id="38"/>
## Windows

[How to get file ACLs on windows through command line](https://superuser.com/questions/364083/windows-list-files-and-their-permissions-access-in-command-line#364088)

[What is UPN](https://apttech.wordpress.com/2012/02/29/what-is-upn-and-why-to-use-it/)

### Windows debugging

[Show external code in visual studio](https://blogs.msdn.microsoft.com/zainnab/2010/10/24/show-external-code/)

[Download windows symbols](https://developer.microsoft.com/en-us/windows/hardware/download-symbols)

[Crash Dump Analysis](https://msdn.microsoft.com/en-us/library/windows/desktop/ee416349(v=vs.85).aspx)

[Specify Symbols in Visual Studio](https://msdn.microsoft.com/en-us/library/ms241613.aspx)


<a id="39"/>
## HTTP 协议相关

[If password in url contains '@', encode '@' with '%40'](http://serverfault.com/questions/371907/can-you-pass-user-pass-for-http-basic-authentication-in-url-parameters#comment-838925)

[Quick Reference about HTTP header](https://www.cs.tut.fi/~jkorpela/http.html)


<a id="40"/>
## scons相关

[编译器标志对应 Env 变量](http://scons.org/doc/production/HTML/scons-man.html#f-ParseFlags)

[Print Env Dump](http://scons.org/doc/1.2.0/HTML/scons-user/x4613.html)

<a id="41"/>
## 编译器相关

[options '-rpath' and '-rpath-link'](https://sourceware.org/binutils/docs/ld/Options.html#Options)

[gcc link order](https://gcc.gnu.org/onlinedocs/gcc/Link-Options.html)

> It makes a difference where in the command you write this option; the linker searches and processes libraries and object files in the order they are specified. Thus, ‘foo.o -lz bar.o’ searches library ‘z’ after file foo.o but before bar.o. If bar.o refers to functions in ‘z’, those functions may not be loaded.

[gcc static link dependency](http://eli.thegreenplace.net/2013/07/09/library-order-in-static-linking)


<a id="42"/>
## VMWare相关
[Issue about vsphere client open console resolution](http://serverfault.com/questions/806914/vsphere-client-console-missing-bottom-and-right-of-screen#818466)


<a id="43"/>
## Networking相关

[What is address 169.254.x.x](https://superuser.com/questions/840388/i-am-using-windows-7-and-i-get-a-169-254-x-x-ip-address#840406)
[Automatic Private IP addressing](http://www.webopedia.com/TERM/A/APIPA.html)

<a id="45"/>
## iOS相关

[iOS Simulator containers](http://stackoverflow.com/questions/6480607/is-there-any-way-to-see-the-file-system-on-the-ios-simulator)

[iOS Simulator containers 2](http://stackoverflow.com/questions/1108076/where-does-the-iphone-simulator-store-its-data)

[How to build ipa file with command line](http://blog.octo.com/en/automating-over-the-air-deployment-for-iphone/)

[Build ipa from command line](http://stackoverflow.com/questions/2664885/xcode-build-and-archive-from-command-line)

[How to build iOS App without developer account](http://stackoverflow.com/questions/40730051/how-to-build-an-ipa-without-signing-in-xcode-8)

[iPad connect/disconnect mac rapidly](https://discussions.apple.com/thread/5523411?start=0&tstart=0)

[Convert plist between xml and binary](http://osxdaily.com/2016/03/10/convert-plist-file-xml-binary-mac-os-x-plutil/)

[Generate unsigned ipa](http://stackoverflow.com/questions/25396299/generating-an-unsigned-ipa-ios-application)

[How to build ipa without signing it](http://stackoverflow.com/questions/40730051/how-to-build-an-ipa-without-signing-in-xcode-8)

[How to analyze ios ips crash file](http://stackoverflow.com/questions/40447722/analysing-app-ips-file-in-xcode)

After sync iOS device with iTunes, on Windows, the sync files are located at
```
%APPDATA%\Apple Computer
```
[How to retrieve ips file from device](https://www.careiphone.com/how-to-retrieve-crash-file-ips-from-iphone-ipad-or-ipod-touch/)

[When an iOS application goes to the background, are lengthy tasks paused?](http://stackoverflow.com/questions/6650717/when-an-ios-application-goes-to-the-background-are-lengthy-tasks-paused)

[How to install multiple versions of Xcode](https://medium.com/@YogevSitton/install-xcode-7-and-xcode-8-side-by-side-5bf40ea8f5ac)

[use xcode-select to select different version of Xcode](http://stackoverflow.com/questions/37867753/change-carthage-swift-version)

[how to set different swift that xcodebuild uses](http://stackoverflow.com/questions/39884323/where-is-xcodes-toolchains-set)

[Xcode build without provisioning profile](http://iphonedevwiki.net/index.php/Xcode#Developing_without_Provisioning_Profile)

[About xcrun](http://stackoverflow.com/questions/2664885/xcode-build-and-archive-from-command-line)

[how to write voip sockets on ios](http://techqa.info/programming/question/27631748/configuring-ios-voip-application-to-run-in-sleep/background-mode)

[Basics about background task and networking on ios TN2277](https://developer.apple.com/library/content/technotes/tn2277/_index.html)

[More details about specific feature of ios app](https://developer.apple.com/library/content/documentation/iPhone/Conceptual/iPhoneOSProgrammingGuide/StrategiesforImplementingYourApp/StrategiesforImplementingYourApp.html)

[Analyzing ios crash report](https://developer.apple.com/library/content/technotes/tn2151/_index.html)

[iOS files accessing](https://developer.apple.com/library/content/documentation/FileManagement/Conceptual/FileSystemProgrammingGuide/AccessingFilesandDirectories/AccessingFilesandDirectories.html)

[symbolicate ios crash](https://stackoverflow.com/questions/1460892/symbolicating-iphone-app-crash-reports/4954949#4954949)

[More about thread](https://ohadsc.wordpress.com/2015/01/27/the-case-of-the-crashing-stdthread-destructor-and-why-you-should-use-tasks-instead-of-threads/)

<a id="46" />
## Multi-threading

[Introduction to parallel computing](https://computing.llnl.gov/tutorials/parallel_comp/)

[POSIX Threads Programming](https://computing.llnl.gov/tutorials/pthreads/)

[Multi-threaded  performance pitfalls](http://www.ciaranmchale.com/training-courses.html#training-multi-threaded)

[Generic synchronization policies](http://www.ciaranmchale.com/training-courses.html#training-gsp)


[\[Table of Contents\]](#toc)
