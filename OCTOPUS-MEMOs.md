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
* [screen and tmux使用技巧](#22)
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
* [Linux相关](#37)
* [File system](#38)
  * [File permission and ACLs](#48)
  * [File punch hole](#49)
* [HTTP 协议相关](#39)
* [scons相关](#40)
* [编译器相关](#41)
* [VMWare相关](#42)
* [Networking相关](#43)
* [iOS相关](#45)
* [Multi-threading](#46)
* [vim/ctags/cscope](#47)
* [gdb相关](#50)
* [软件工程](#51)
* [Misc](#52)
* [Security](#53)
* [gdb/valgrind](#54)

## What is the best way to merge mp3 files ? <a id="1" />

[stackoverflow上的回答](http://stackoverflow.com/questions/62618/what-is-the-best-way-to-merge-mp3-files)

**Use ffmpeg or a similar tool to convert all of your MP3s into a consistent format, e.g.**

>ffmpeg -i originalA.mp3 -f mp3 -ab 128kb -ar 44100 -ac 2 intermediateA.mp3

>ffmpeg -i originalB.mp3 -f mp3 -ab 128kb -ar 44100 -ac 2 intermediateB.mp3

Then, at runtime, concat your files together:

>cat intermediateA.mp3 intermediateB.mp3 > output.mp3

Finally, run them through the tool MP3Val to fix any stream errors without forcing a full re-encode:

>mp3val output.mp3 -f -nb

## Cannot connect to samba shared files after 4.1.14-1 upgrade. <a id="2" />

[\[SOLVED\]cannot connect to samba server after upgrade](https://bbs.archlinux.org/viewtopic.php?id=190592)
[FS\#43015 - \[samba\] cannot connect to samba shared files after 4.1.14-1 upgrade](https://bugs.archlinux.org/task/43015)

See [\[SOLVED\] cannot connect to samba server after upgrade](https://bbs.archlinux.org/viewtopic.php?pid=1484501#p1484501) for some log comparisons between 4.1.13 and 4.1.14 taken moments apart and some cursory debugging. The problem is not so easily worked around for windows clients.

>EDIT: Looked at the upstream patch found at [patch-4.1.13-4.1.14.diffs.gz](http://samba.org/samba/ftp/patches/patch-4.1.13-4.1.14.diffs.gz) and found that they changed how the "smb_my_netbios_names" array is allocated in "samba-4.1.14/source3/lib/util_names.c" and must have broke "is_myname(cstring)". It's an upstream bug for sure.

>EDIT2: Super simple workaround! Just shorten your NETBIOS name by adding "netbios name=\[15 chars or less, simple ASCII chars only\]" to your smb.conf.

>EDIT3: Reported upstream: [samba-show-bug](https://bugzilla.samba.org/show_bug.cgi?id=11008)

[Troubleshooting Samba](https://www.samba.org/samba/docs/using_samba/ch12.html)

## Disk Utility in Linux <a id="3" />

### Disk scanning for badblocks

badblocks
mhdd

### Data recovery
safecopy
testdisk
photorec

## Linux运维 <a id="4" />

[Linux运维网](http://www.linuxyunwei.com)

[nginx配置中使用环境变量](https://docs.apitools.com/blog/2014/07/02/using-environment-variables-in-nginx-conf.html)

[nginx.conf中替换环境变量](http://serverfault.com/questions/577370/how-can-i-use-environment-variables-in-nginx-conf)

[sort find result in time order](https://unix.stackexchange.com/questions/29899/how-can-i-use-find-and-sort-the-results-by-mtime#29901)

## VPN相关 <a id="5" />

[使用 Strongswan 架设 Ipsec VPN](https://zh.opensuse.org/SDB:Setup_Ipsec_VPN_with_Strongswan)

## Markdown相关 <a id="6" />

[Markdown Cheatsheet](http://assemble.io/docs/Cheatsheet-Markdown.html)

[Anchor links in markdown](http://blog.justin.kelly.org.au/anchor-links-in-markdown/)

[Markdown open a new window link](http://stackoverflow.com/questions/3492153/markdown-open-a-new-window-link)

## VIM配置 <a id="7" />

常用vim配置
```
set cindent shiftwidth=4
set ts=4
set listchars=tab:>-,trail:-
set list
" statements below set indention to 2
" set tabstop=2
" set shiftwidth=2
" set softtabstop=2
set expandtab
set number
" show cusor position
set ruler
" show status line
set laststatus=2
" set hilight cursor
set cursorline
hi CursorLine   cterm=NONE ctermbg=DarkCyan ctermfg=white guibg=DarkCyan guifg=white
hi CursorColumn cterm=NONE ctermbg=DarkCyan ctermfg=white guibg=DarkCyan guifg=white
nnoremap <Leader>c :set cursorline! cursorcolumn!<CR>

set encoding=utf8
set fileencodings=ucs-bom,utf-8,cp936,gb18030,big5,euc-jp,euc-kr,latin1
" high-light search result
set hlsearch
" set ctag file search path, from ./ to /
set tags=./tags;/

" automatic center search result
nmap n nzz
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

[5 essential vim plugins](http://joelhooks.com/blog/2013/04/23/5-essential-vim-plugins/)

[How to search visual selected text](https://stackoverflow.com/questions/8587136/how-do-i-search-for-the-selected-text)

[How to search multiple words...](https://stackoverflow.com/questions/19970974/how-to-highlight-multiple-words-in-vim)

[vim search patterns](https://vim.fandom.com/wiki/Search_patterns)

## Exact String Matching Algorithms <a id="8" />

[Exact String Matching Algorithms](http://www-igm.univ-mlv.fr/~lecroq/string/)

## General Purpose Hash Function Algorithms <a id="9" />

[hash function](http://www.partow.net/programming/hashfunctions/)

## 有用的博客 <a id="10"/>

[菜鸟的自留地](http://blog.csdn.net/yang_yulei)

[gmarik](http://www.gmarik.info/)

## ssh配置 <a id="12"/>

[ssh配置](http://blog.chinaunix.net/uid-20710081-id-3266103.html)

[ssh auto-logout 在screen中自动退出的问题](http://www.adercon.com/ac/node/39)

## 常用samba设置 <a id="14"/>
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

## linux查看端口占用情况 <a id="15"/>

同时需要必要的root权限

查看端口占用情况的命令：
>lsof -i

查看某一端口的占用情况：
>lsof -i:端口号

查看文件占用情况:
>fuser filename

[How to list opened ports](https://apple.stackexchange.com/questions/117644/how-can-i-list-my-open-network-ports-with-netstat)

## docker相关 <a id="16"/>

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

## Using HTTP_PROXY <a id="17"/>

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

## Development language <a id="18"/>
[C99 array initializers](http://gcc.gnu.org/onlinedocs/gcc-4.1.2/gcc/Designated-Inits.html)

```
int array[1024] = {[0 ... 1023] = 5};
```

## usage of sed <a id="19"/>

[sed's RE is basic regular expression](http://unix.stackexchange.com/questions/90653/why-do-i-need-to-escape-regex-characters-in-sed-to-be-interpreted-as-regex-chara)

## use 'patch' to patch code <a id="20"/>

```
patch -p1 -l --dry-run --verbose < patchfile
```

## ubuntu init <a id="21"/>

[ubuntu init.d scripts](http://unix.stackexchange.com/questions/133961/can-not-execute-restart-networking-service-on-ubuntu-14-04)

## screen and tmux使用技巧 <a id="22"/>

screen 记录log
Ctrl-a H
用more可以查看带escape标示的log文件

[putty上使用screen后的scrollback](http://serverfault.com/questions/32313/putty-and-screen-and-scroll-back-buffer)

[clear screen after using vim in screen](http://serverfault.com/questions/270103/gnu-screen-clearing-on-vim-less-etc-exit)

[Set screen-new-window path](https://stackoverflow.com/questions/1517414/how-to-make-gnu-screen-start-a-new-window-at-the-current-working-directory)

[screen key-bindings](http://www.pixelbeat.org/lkdb/screen.html)

[scroll in tmux](https://superuser.com/questions/209437/how-do-i-scroll-in-tmux)

[set scrollback buffer size](https://stackoverflow.com/questions/8760346/how-do-i-increase-the-scrollback-buffer-in-a-running-screen-session)

## build kernel相关 <a id="23"/>

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

## 使用lvm管理磁盘 <a id="24"/>

[使用lvm管理磁盘扩容](https://www.rootusers.com/how-to-increase-the-size-of-a-linux-lvm-by-adding-a-new-disk/)

## Android System UIDs inconsistent的解决方法 <a id="25"/>

Check the file /data/system/uiderrors.txt for inconsistent uids.

[You Need MANAGE_USERS permission](http://forum.xda-developers.com/showthread.php?t=1999383)

[How to replace java 8 with java 7 on Mac OS](https://www.java.com/en/download/help/mac_uninstall_java.xml)

[How to switch java version on Mac OS](http://stackoverflow.com/questions/21964709/how-to-set-or-change-the-default-java-jdk-version-on-os-x#24657630)

[How to remove java 8 on MacOS](http://stackoverflow.com/questions/17885494/how-can-i-change-mac-oss-default-java-vm-returned-from-usr-libexec-java-home#20994919)

[How to check java version in ant](http://www.asjava.com/ant/how-to-check-java-version-in-ant/)


[Ant error 'javac1.8 class not found'](http://stackoverflow.com/questions/20702626/javac1-8-class-not-found)

## Python搭建虚拟开发环境 <a id="26"/>

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

## 关闭SELinux <a id="27"/>
```
sudo setenforce 0
```

SELinux 配置文件
```
sudo vim /etc/sysconfig/selinux
#SELINUX=enforcing
SELINUX=permissive
```

## k8s相关 <a id="28"/>

[heapster无法获取时间不同步的node的metrics](https://github.com/kubernetes/heapster/issues/516)

[heapster的'time synchronization'问题](https://github.com/kubernetes/heapster/issues/802)

## openssl 相关 <a id="29"/>

[openssl使用](https://www.digitalocean.com/community/tutorials/openssl-essentials-working-with-ssl-certificates-private-keys-and-csrs)

[Android上(certificate recovation list)未检查的问题](https://commonsware.com/blog/2014/04/18/more-android-revoked-ssl-certificates.html)

[der/pem/crt/cer file type](http://info.ssl.com/article.aspx?id=12149)

[how to install certificates on local](https://askubuntu.com/questions/645818/how-to-install-certificates-for-command-line)

## cURL的使用问题 <a id="30"/>

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

## C++相关 <a id="31"/>

[c++ vtable](http://shaharmike.com/cpp/)

[vptr initialization](https://stackoverflow.com/questions/6591859/when-does-the-vptr-pointing-to-vtable-get-initialized-for-a-polymorphic-class)

[C++相关](http://blog.csdn.net/anzhsoft)

[C++ faq from BJ](http://www.stroustrup.com/bs_faq2.html)

[Differences between 'static' and 'extern'](http://stackoverflow.com/questions/92546/variable-declarations-in-header-files-static-or-not#93663)

[右值引用](http://thbecker.net/articles/rvalue_references/section_01.html)

[const and linkage](http://stackoverflow.com/questions/12042549/constants-only-header-file-c#12043198)

[const and extern](https://stackoverflow.com/questions/14894698/why-does-extern-const-int-n-not-work-as-expected)

[Differences between 'libstdc++' and 'libc++'](http://stackoverflow.com/questions/14972425/should-i-use-libc-or-libstdc)

[Some issues about libc++ and libstdc++ on MAC](http://stackoverflow.com/questions/19637164/c-linking-error-after-upgrading-to-mac-os-x-10-9-xcode-5-0-1)

STL

[How to securely clear containers data](http://stackoverflow.com/questions/3785582/how-to-write-a-password-safe-class)

[Secure programming in C++](http://etutorials.org/Programming/secure+programming/)

[How does delete knows array size](https://isocpp.org/wiki/faq/freestore-mgmt#num-elems-in-new-array)

```
/// A example of new/delete access memory violation error
#include <iostream>
struct A {
    A()
    {
        std::cout << "A called" << std::endl;
    }
    ~A()
    {
        std::cout << "~A called" << std::endl;
    }
};
int main()
{
    A* pa = (A*)(new char[sizeof(A) * 2]);
    delete [] (char*)pa;
}
```
In the code above
```
(gdb) l
2
3       struct A {
4           A()
5           {
6               std::cout << "A called" << std::endl;
7           }
8           ~A()
9           {
10              std::cout << "~A called" << std::endl;
11          }
(gdb) b 10
Breakpoint 1 at 0x400a10: file test.cpp, line 10.
(gdb) l
12
13      };
14      int main()
15      {
16          A* pa = (A*)(new char[sizeof(A) * 2]);
17          delete [] pa;
18      }
(gdb) b 17
Breakpoint 2 at 0x400967: file test.cpp, line 17.
(gdb) r
Starting program: /home/c4dev/a.out
Missing separate debuginfos, use: zypper install glibc-debuginfo-2.19-31.9.emc7065956.7065956.x86_64

Breakpoint 2, main () at test.cpp:17
17          delete [] pa;
Missing separate debuginfos, use: zypper install libgcc_s1-debuginfo-5.2.1+r226025-4.1.x86_64 libstdc++6-debuginfo-5.2.1+r226025-4.1.x86_64
(gdb) p pa
$1 = (A *) 0x613c20
(gdb) x/32xb 0x613c20-8
0x613c18:       0x21    0x00    0x00    0x00    0x00    0x00    0x00    0x00
0x613c20:       0x00    0x00    0x00    0x00    0x00    0x00    0x00    0x00
0x613c28:       0x00    0x00    0x00    0x00    0x00    0x00    0x00    0x00
0x613c30:       0x00    0x00    0x00    0x00    0x00    0x00    0x00    0x00
<<<<<<<<-------- 0x613c18 contains 8 bytes of cookie for size of memory of char, 0x21
(gdb) p pa
$2 = (A *) 0x613c20
(gdb) p pa+1
$3 = (A *) 0x613c21
<<<<<<<<-------- 0x613c21 is the legal address of last element A in array
(gdb) p pa+0x20
$4 = (A *) 0x613c40
(gdb) c
Continuing.

Breakpoint 1, A::~A (this=0x613c40, __in_chrg=<optimized out>) at test.cpp:10
10              std::cout << "~A called" << std::endl;
<<<<<<<<-------- 0x613c40 is pa + 0x20, which is falsely taken as last element by compiler, total elem count is 0x21
(gdb) c
Continuing.
~A called

Breakpoint 1, A::~A (this=0x613c3f, __in_chrg=<optimized out>) at test.cpp:10
10              std::cout << "~A called" << std::endl;
(gdb) p sizeof(A) * 2
$5 = 2
<<<<<<<<-------- call ~A on each of element in reverse order.

This is overflow access of memory, the legal address range is [0x613c20, 0x613c22), 0x613c40 is out of that range.
```

[elide-constructors](https://stackoverflow.com/questions/23854249/temporary-objects-with-fno-elide-constructors)

[undefined reference in boost linkage](https://stackoverflow.com/questions/15280882/why-undefined-reference-to-boostsystemgeneric-category-even-if-i-do-link#15318710)

[C++ standards](http://www.open-std.org/JTC1/SC22/WG21/docs/standards)

[C++ delete operator not always used](https://stackoverflow.com/questions/49713773/c-operator-delete-override-not-always-used)

[destructor not called with `exit(0)`](https://stackoverflow.com/questions/7054685/are-destructors-run-when-calling-exit)

## 算法相关 <a id="32"/>

[多路归并外排](http://sandbox.mc.edu/~bennet/cs402/lec/index.html)

[算法和数据结构](http://lib.csdn.net/base/datastructure)

[海量和数据处理](http://blog.csdn.net/v_july_v/article/details/7382693)

[算法在线课程](http://julyedu.com)

[Concurrency VS Parallelism](https://www.quora.com/What-is-the-difference-between-concurrency-and-parallelism)

[File Data Structures](http://dcs.gla.ac.uk/Keith/Chapter.4/Ch.4.html)

[Oracle B-Tree Index: From the concept to Internals](http://web.archive.org/web/20161221112438/http://www.toadworld.com/platforms/oracle/w/wiki/11001.oracle-b-tree-index-from-the-concept-to-internals)

## git/svn 相关 <a id="33"/>

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
[vim with git](https://stackoverflow.com/questions/16232767/git-difftool-in-read-write-mode)

[vim-git](https://github.com/tpope/vim-git)

[fugitive](https://github.com/tpope/vim-fugitive)

[Word by word diffs in git](https://idnotfound.wordpress.com/2009/05/09/word-by-word-diffs-in-git/)

[how to disable git ssl certificate](https://stackoverflow.com/questions/11621768/how-can-i-make-git-accept-a-self-signed-certificate)
```
git -c http.sslVerify=false clone ...
```

[shell command to sum integers](https://stackoverflow.com/questions/450799/shell-command-to-sum-integers-one-per-line)
```
git log --shortstat 1115b31ce78b5cf691c60c64deef21e6658cbcbb..32b04223a148451e0db8b62873c4ae96118f69a6 | grep 'files changed' | awk '{s+=$4} END {print s}'
git log --shortstat 1115b31ce78b5cf691c60c64deef21e6658cbcbb..32b04223a148451e0db8b62873c4ae96118f69a6 | grep 'files changed' | awk '{s+=$6} END {print s}'
```

## 工具相关 <a id="34"/>

[绘制sequence diagram](https://www.websequencediagrams.com)

[Another tool to draw call sequence diagram](https://mscgen.js.org/)

[Tools to draw call graph](https://stackoverflow.com/questions/517589/tools-to-get-a-pictorial-function-call-graph-of-code)

[Tools to draw call sequence](https://stackoverflow.com/questions/1367059/tool-for-drawing-protocol-sequence-diagrams)

[How to select different network adapter to use in windows 10](https://answers.microsoft.com/en-us/windows/forum/windows_10-networking/adapter-priority-setting-unavailable-in-windows-10/d2b63caa-e77c-4b46-88b5-eeeaee00c306#ThreadAnswers)

[How to draw c++ inheritance relationship graph on linux](https://stackoverflow.com/questions/8509243/class-hierarchy-dependency-diagram-generator-for-c-in-linux)

## About shoggoth <a id="35"/>

[shoggoth produce multiple variables using jinja2](http://jinja.pocoo.org/docs/2.9/templates/#assignments)

[jinja variables scope in block](http://stackoverflow.com/questions/4870346/can-a-jinja-variables-scope-extend-beyond-in-an-inner-block)

## Coding style <a id="36"/>

[C++ coding style](http://geosoft.no/development/cppstyle.html)

[Prefer suffix than prefix underscore](http://stackoverflow.com/questions/1228161/why-use-prefixes-on-member-variables-in-c-classes#1228199)

[do ... while(0)](https://stackoverflow.com/questions/154136/why-use-apparently-meaningless-do-while-and-if-else-statements-in-macros)

[Guru of the Week](http://www.gotw.ca/gotw/)

[if (condition) statement](https://softwareengineering.stackexchange.com/questions/350472/developer-insists-if-statements-shouldnt-have-negated-conditions-and-should-al)

## Linux相关 <a id="37"/>

[fstab格式](https://wiki.archlinux.org/index.php/fstab)

[Touchscreen HID USB protocol](https://forum.pjrc.com/threads/32331-USB-HID-Touchscreen-support-needed)

[container_of in linux kernel](https://stackoverflow.com/questions/15832301/understanding-container-of-macro-in-the-linux-kernel)

[statement expression in GNU C](http://gcc.gnu.org/onlinedocs/gcc/Statement-Exprs.html)

[kernel init order at boot-up time](https://stackoverflow.com/questions/18605653/linux-module-init-vs-core-initcall-vs-early-initcall#18605952)

[Linux Kernel Hash data-structure](https://lwn.net/Articles/510202/)

[Linux Kernel Spinlock definitely has preemption disabled](http://www.linuxinternals.org/blog/2014/05/07/spinlock-implementation-in-linux-kernel/)

[A filesystem reading list](https://lwn.net/Articles/196292/)

[大神Brendan Gregg](http://www.brendangregg.com/)

[How to remove bytes from start of file](https://unix.stackexchange.com/questions/6852/best-way-to-remove-bytes-from-the-start-of-a-file?utm_medium=organic&utm_source=google_rich_qa&utm_campaign=google_rich_qa)

[How to install lighttpd on suse](https://www.linuxhelp.com/how-to-install-lighttpd-web-server-in-opensuse/)

[Latency numbers every programmer should know](https://people.eecs.berkeley.edu/~rcs/research/interactive_latency.html)

[Jeffrey Dean's blog](https://ai.google/research/people/jeff)

[Teach Yourself Programming in Ten Years by Norvig](http://norvig.com/21-days.html)

[Quantitative System Performance by Lazowska](https://homes.cs.washington.edu/~lazowska/qsp/)

[Operating System: Three Easy Pieces](http://pages.cs.wisc.edu/~remzi/OSTEP/)

## File system <a id="38" />

[ext4 filesystem](https://swbae98.wordpress.com/tag/ext4/)

[ext4 disk layout](https://ext4.wiki.kernel.org/index.php/Ext4_Disk_Layout)

[learn more about ext4](https://www.datarecoverytools.co.uk/2009/11/16/learn-more-about-ext4/)

[ext3 journaling file system](http://www.cs.umd.edu/projects/shrug/ppt/5-Oct-2001.ppt)

[SHRUG](http://www.cs.umd.edu/projects/shrug/)

[SSDFANS](http://www.ssdfans.com/?p=832)

[CFM](https://www.flashmemorysummit.com/English/Collaterals/Proceedings/2015/20150811_FB11_Jadon.pdf)

[USENIX conference on file and storage](https://www.usenix.org/legacy/events/bytopic/fast.html)

[FAST20](https://www.usenix.org/conference/fast20)

### Windows <a id="48"/>

[How to get file ACLs on windows through command line](https://superuser.com/questions/364083/windows-list-files-and-their-permissions-access-in-command-line#364088)

[What is UPN](https://apttech.wordpress.com/2012/02/29/what-is-upn-and-why-to-use-it/)

### Windows debugging

[Show external code in visual studio](https://blogs.msdn.microsoft.com/zainnab/2010/10/24/show-external-code/)

[Download windows symbols](https://developer.microsoft.com/en-us/windows/hardware/download-symbols)

[Crash Dump Analysis](https://msdn.microsoft.com/en-us/library/windows/desktop/ee416349(v=vs.85).aspx)

[Specify Symbols in Visual Studio](https://msdn.microsoft.com/en-us/library/ms241613.aspx)

### File punch hole <a id="49" />

[Difference between dig hole and punch hole](https://unix.stackexchange.com/questions/390248/what-is-the-difference-between-fallocate-dig-holes-and-fallocate-punch-ho)

## HTTP 协议相关 <a id="39"/>

[If password in url contains '@', encode '@' with '%40'](http://serverfault.com/questions/371907/can-you-pass-user-pass-for-http-basic-authentication-in-url-parameters#comment-838925)

[Quick Reference about HTTP header](https://www.cs.tut.fi/~jkorpela/http.html)

[URL-encoding](http://www.vermontdatabase.com/cloudwriter/url_encoding.htm)

## scons相关 <a id="40"/>

[编译器标志对应 Env 变量](http://scons.org/doc/production/HTML/scons-man.html#f-ParseFlags)

[Print Env Dump](http://scons.org/doc/1.2.0/HTML/scons-user/x4613.html)

## 编译器相关 <a id="41"/>

[options '-rpath' and '-rpath-link'](https://sourceware.org/binutils/docs/ld/Options.html#Options)

[gcc link order](https://gcc.gnu.org/onlinedocs/gcc/Link-Options.html)

> It makes a difference where in the command you write this option; the linker searches and processes libraries and object files in the order they are specified. Thus, ‘foo.o -lz bar.o’ searches library ‘z’ after file foo.o but before bar.o. If bar.o refers to functions in ‘z’, those functions may not be loaded.

[gcc static link dependency](http://eli.thegreenplace.net/2013/07/09/library-order-in-static-linking)

[How to avoid `unused variable` warnings](https://stackoverflow.com/questions/4647665/why-cast-an-unused-function-parameter-value-to-void)

## VMWare相关 <a id="42"/>

[Issue about vsphere client open console resolution](http://serverfault.com/questions/806914/vsphere-client-console-missing-bottom-and-right-of-screen#818466)

## Networking相关 <a id="43"/>

[What is address 169.254.x.x](https://superuser.com/questions/840388/i-am-using-windows-7-and-i-get-a-169-254-x-x-ip-address#840406)

[Automatic Private IP addressing](http://www.webopedia.com/TERM/A/APIPA.html)

## iOS相关 <a id="45"/>

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

## Multi-threading <a id="46" />

[Introduction to parallel computing](https://computing.llnl.gov/tutorials/parallel_comp/)

[POSIX Threads Programming](https://computing.llnl.gov/tutorials/pthreads/)

[Multi-threaded  performance pitfalls](http://www.ciaranmchale.com/training-courses.html#training-multi-threaded)

[Generic synchronization policies](http://www.ciaranmchale.com/training-courses.html#training-gsp)

>To allow other threads to continue execution, the main thread should terminate by calling pthread_exit() rather than exit(3).

[Signal handler execution on linux](https://stackoverflow.com/questions/6949025/how-are-asynchronous-signal-handlers-executed-on-linux)

[Memory ordering model with atomic operation](https://gcc.gnu.org/wiki/Atomic/GCCMM/AtomicSync)

[pure virtual method called in multi-threading environment](https://tombarta.wordpress.com/2008/07/10/gcc-pure-virtual-method-called/)

[atomic_shared_ptr](https://www.justsoftwaresolutions.co.uk/threading/why-do-we-need-atomic_shared_ptr.html)

[Multi-threading materials](https://www.justsoftwaresolutions.co.uk/threading/)

[Atomic Smart pointers](http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2014/n4162.pdf)

[shared_ptr thread safety](https://stackoverflow.com/questions/14482830/stdshared-ptr-thread-safety)

[lock-free programming](http://www.rossbencina.com/code/lockfree)

[lock-free lecture](https://www.cs.cmu.edu/~410-s05/lectures/L31_LockFree.pdf)

## vim/ctags/cscope <a id="47" />

build ctags index:
```
ctags --exclude=.git -n -R .
```
in ~/.vimrc file, set tags searching order from ./tags file to /.
```
set tags=./tags;/
```
[setup ctags and cscope in vim](https://www.embeddedarm.com/blog/tag-jumping-in-a-codebase-using-ctags-and-cscope-in-vim/)

ctag/cscope update scripts.
```
#!/bin/bash

# update ctags
ctags --exclude=.git -a -n -R .

/usr/local/bin/gentags

huangleon@huangleon-virtual-machine:~/work/unity$ cat /usr/local/bin/gentags
#!/bin/bash

CSCOPE_DIR="$PWD/cscope"

if [ ! -d "$CSCOPE_DIR" ]; then
mkdir "$CSCOPE_DIR"
fi

echo "Finding files ..."
find "$PWD" -name '*.[ch]' \
-o -name '*.java' \
-o -name '*properties' \
-o -name '*.cpp' \
-o -name '*.cc' \
-o -name '*.hpp' \
-o -name '*.cxx' \
-o -name '*.hxx' \
-o -name '*.js' \
-o -name '*.py' \
-o -name '*.pl' \
-o -name '*.php' > "$CSCOPE_DIR/cscope.files"

echo "Adding files to cscope db: $PWD/cscope.db ..."
cscope -b -R -q -i "$CSCOPE_DIR/cscope.files"

export CSCOPE_DB="$PWD/cscope.out"
echo "Exported CSCOPE_DB to: '$CSCOPE_DB'"
```

## gdb/valgrind 相关 <a id="50" />

[gdb pretty print](https://stackoverflow.com/questions/12618331/displaying-struct-values-in-gdb#12618396)

[gdb toc](https://ftp.gnu.org/old-gnu/Manuals/gdb/html_node/gdb_toc.html)

[gdb thread](https://stackoverflow.com/questions/18391808/getting-the-backtrace-for-all-the-threads-in-gdb)

[gdb logging](https://stackoverflow.com/questions/1707167/how-to-dump-the-entire-gdb-session-to-a-file-including-commands-i-type-and-thei)

[gdb gdbinit](https://stackoverflow.com/questions/15399265/how-do-i-load-gdbinit-on-gdb-startup)

[load gdbinit external with gdb](https://stackoverflow.com/questions/14226563/how-to-read-and-execute-gdb-commands-from-a-file)

```
gdb -x ./gdbinit
```
[show stack information](https://stackoverflow.com/questions/7848771/how-can-one-see-content-of-stack-with-gdb)
```
info frame
x/100x $rbp
```

[understanding gdb assembly](https://www.recurse.com/blog/7-understanding-c-by-learning-assembly)

[get SIG_SEGV addr](https://stackoverflow.com/questions/3003339/how-can-i-get-gdb-to-tell-me-what-address-caused-a-segfault)
```
(gdb) p $_siginfo._sifields._sigfault.si_addr
```
[gdb signals and SIG_SEGV](https://sourceware.org/gdb/onlinedocs/gdb/Signals.html)

[gdb-commands](http://www.yolinux.com/TUTORIALS/GDB-Commands.html)

[x86 asm](http://ref.x86asm.net/)

[x86 cheat-sheet](https://www.cs.uaf.edu/2005/fall/cs301/support/x86/index.html)

[x86-cheat-sheet](https://stackoverflow.com/questions/1933801/x86-assembly-reference-sheet)

[x86-cheat-sheet](https://cs.brown.edu/courses/cs033/docs/guides/x64_cheatsheet.pdf)

[gdb-commands](http://www.yolinux.com/TUTORIALS/GDB-Commands.html)

[x64 registers](https://stackoverflow.com/questions/1753602/what-are-the-names-of-the-new-x86-64-processors-registers)

Redirect 'ALL' gdb output to a logfile
```
gdb executable-file core-dump-file |& tee backtrace.log
```

[how-to-view-a-pointer-like-an-array-in-gdb](https://stackoverflow.com/questions/14502236/how-to-view-a-pointer-like-an-array-in-gdb)
```
p *array@len
```
[valgrind bug](https://stackoverflow.com/questions/1542457/memory-leak-reported-by-valgrind-in-dlopen)

## 软件工程 <a id="51" />

[backrev](https://everything2.com/title/backrev)

## Misc <a id="52" />

[Hex words](http://www.nsftools.com/tips/HexWords.htm)

[Bash function](https://ryanstutorials.net/bash-scripting-tutorial/bash-functions.php)

[OS plumber](https://blog.fpmurphy.com/)

[how to make make show gcc commands](https://stackoverflow.com/questions/5820303/how-do-i-force-make-gcc-to-show-me-the-commands)

[base41](https://github.com/sveljko/base41)

[MurmurHash & Smhasher](https://github.com/aappleby/smhasher)

```
# for CMAKE
make VERBOSE=1
# for GNU make
make V=1
```

[g++ -m32](https://stackoverflow.com/questions/4643197/missing-include-bits-cconfig-h-when-cross-compiling-64-bit-program-on-32-bit)

[Why is it faster to process a sorted array than an unsorted array?](https://stackoverflow.com/questions/11227809/why-is-it-faster-to-process-a-sorted-array-than-an-unsorted-array)

[turn off buffering in bash pipe](https://unix.stackexchange.com/questions/25372/turn-off-buffering-in-pipe)

```
convert \r to \n
#!/bin/bash
cat file.txt | tr '\r' '\n' | tr -s '\n' > file.translated.txt
```
[convert MAC EOL to Unix](https://marcelog.github.io/articles/mac_newline_to_unix_eol.html)

## Security <a id="53" />

[Differences between krb and NTLM](https://www.itprotoday.com/security/comparing-windows-kerberos-and-ntlm-authentication-protocols)

## gdb/valgrind <a id="54" />
[uninitialized value in valgrind and gtest](https://www.kullo.net/blog/why-valgrind-reports-uninitialised-value-errors-when-running-google-testmock/)

[\[Table of Contents\]](#toc)
