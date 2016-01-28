#1.6 Wiki Backup
* Misc
    * [cubieboard的android系统编译准备]()

##cubieboard的android系统编译准备
文档:

[Cubieboard开发环境、Uboot的SD启动卡制作、U-boot初步分析](http://blog.csdn.net/andy_wsj/article/details/8515197)
[加载boot的问题](http://forum.cubietech.com/forum.php?mod=viewthread&tid=641)
[Cubieboard2 Info](http://androtab.info/cubieboard2/)

ubuntu 64位下需要准备的软件包：

[Android Source Initializing](http://source.android.com/source/initializing.html)

JDK的安装 jdk 1.7

>$ sudo apt-get update
>$ sudo apt-get install openjdk-7-jdk

jdk 1.6
下载jdk-6u33-linux-x64.bin
执行如下指令：
>$chmod +x jdk-6u33-linux-x64.bin
>$sudo ./jdk-6u33-linux-x64.bin
>$sudo mv jdk1.6.0_32 /usr/lib/jvm/
 
>$ sudo update-alternatives  --install /usr/bin/javac javac /usr/lib/jvm/jdk1.6.0_45/bin/javac 1
>$ sudo update-alternatives  --install /usr/bin/java java /usr/lib/jvm/jdk1.6.0_45/bin/java 1
>$ sudo update-alternatives  --install /usr/bin/javaws javaws /usr/lib/jvm/jdk1.6.0_45/bin/javaws 1
>$ sudo update-alternatives  --install /usr/bin/javah javah /usr/lib/jvm/jdk1.6.0_45/bin/javah 1
>$ sudo update-alternatives  --install /usr/bin/javap javap /usr/lib/jvm/jdk1.6.0_45/bin/javap 1
>$ sudo update-alternatives  --install /usr/bin/javadoc javadoc /usr/lib/jvm/jdk1.6.0_45/bin/javadoc 1

>$sudo update-alternatives --config javac
>$sudo update-alternatives --config java
>$sudo update-alternatives --config javaws
>$sudo update-alternatives --config javah
>$sudo update-alternatives --config javap
>$sudo update-alternatives --config javadoc

同时调整JAVA_HOME

>export JAVA_HOME=/usr/lib/jvm/jdk1.6.0_45

准备12.04编译环境

>$ sudo apt-get install git gnupg flex bison gperf build-essential \
          zip curl libc6-dev libncurses5-dev:i386 x11proto-core-dev \
            libx11-dev:i386 libreadline6-dev:i386 libgl1-mesa-glx:i386 \
              libgl1-mesa-dev g++-multilib mingw32 tofrodos \
                python-markdown libxml2-utils xsltproc zlib1g-dev:i386
                $ sudo ln -s /usr/lib/i386-linux-gnu/mesa/libGL.so.1 /usr/lib/i386-linux-gnu/libGL.so

                http://stackoverflow.com/questions/23254439/android-setting-up-a-linux-build-environment-libgl1-mesa-glxi386-package-have

                Install libglapi-mesa-lts-saucy:i386 instead of libgl1-mesa-glx:i386:

                $ sudo apt-get install libglapi-mesa-lts-saucy:i386

                Now you have correct AOSP build environment and don't loose desktop environment. 


