#1.6 Wiki Backup
* <a id="misc"/>Misc
    * [cubieboard的android系统编译准备](#1)
    * [Cubieboard上用sdcard启动android](#2)
    * [android sensors的底层配置](#3)
    * [android permissions的设置](#4)
    * [android系统源代码编译](#5)
    * [android系统按键映射表](#6)
    * [elinux开发](#7)
    * [adb无法找到设备的解决方法](#8)
    * [Android APK的反编译](#9)
    * [Android 程序调试](#10)
    * [Linux I/O重定向](#11)
    * [wget使用技巧](#12)
    * [网络工具使用](#13)
    * [samba服务挂载](#14)
    * [usbfs的问题](#15)
    * [Linux用户密码设置](#16)
    * [vim使用技巧](#17)

##<a id="1"/>cubieboard的android系统编译准备
文档:

[Cubieboard开发环境、Uboot的SD启动卡制作、U-boot初步分析](http://blog.csdn.net/andy_wsj/article/details/8515197)

[加载boot的问题](http://forum.cubietech.com/forum.php?mod=viewthread&tid=641)

[Cubieboard2 Info](http://androtab.info/cubieboard2/)

**ubuntu 64位下需要准备的软件包：**

[Android Source Initializing](http://source.android.com/source/initializing.html)

**JDK的安装 jdk 1.7**
```
$ sudo apt-get update
$ sudo apt-get install openjdk-7-jdk
```
**jdk 1.6
下载jdk-6u33-linux-x64.bin
执行如下指令：**
```
$ chmod +x jdk-6u33-linux-x64.bin
$ sudo ./jdk-6u33-linux-x64.bin
$ sudo mv jdk1.6.0_32 /usr/lib/jvm/
$ sudo update-alternatives  --install /usr/bin/javac javac /usr/lib/jvm/jdk1.6.0_45/bin/javac 1
$ sudo update-alternatives  --install /usr/bin/java java /usr/lib/jvm/jdk1.6.0_45/bin/java 1
$ sudo update-alternatives  --install /usr/bin/javaws javaws /usr/lib/jvm/jdk1.6.0_45/bin/javaws 1
$ sudo update-alternatives  --install /usr/bin/javah javah /usr/lib/jvm/jdk1.6.0_45/bin/javah 1
$ sudo update-alternatives  --install /usr/bin/javap javap /usr/lib/jvm/jdk1.6.0_45/bin/javap 1
$ sudo update-alternatives  --install /usr/bin/javadoc javadoc /usr/lib/jvm/jdk1.6.0_45/bin/javadoc 1

$ sudo update-alternatives --config javac
$ sudo update-alternatives --config java
$ sudo update-alternatives --config javaws
$ sudo update-alternatives --config javah
$ sudo update-alternatives --config javap
$ sudo update-alternatives --config javadoc
```
**同时调整JAVA_HOME**
```
export JAVA_HOME=/usr/lib/jvm/jdk1.6.0_45
```

**准备12.04编译环境**
```
$ sudo apt-get install git gnupg flex bison gperf build-essential zip curl libc6-dev libncurses5-dev:i386 x11proto-core-dev libx11-dev:i386 libreadline6-dev:i386 libgl1-mesa-glx:i386 libgl1-mesa-dev g++-multilib mingw32 tofrodos python-markdown libxml2-utils xsltproc zlib1g-dev:i386
$ sudo ln -s /usr/lib/i386-linux-gnu/mesa/libGL.so.1 /usr/lib/i386-linux-gnu/libGL.so
```
[Android, setting up a Linux build environment](http://stackoverflow.com/questions/23254439/android-setting-up-a-linux-build-environment-libgl1-mesa-glxi386-package-have)

**Install libglapi-mesa-lts-saucy:i386 instead of libgl1-mesa-glx:i386:**
```
$ sudo apt-get install libglapi-mesa-lts-saucy:i386
```
**Now you have correct AOSP build environment and don't loose desktop environment.**

##<a id="2"/>Cubieboard上用sdcard启动android
###准备工具链
####准备linaro
获取linaro toolchain
```
$ wget https://launchpad.net/linaro-toolchain-binaries/trunk/2013.04/+download/gcc-linaro-arm-linux-gnueabihf-4.7-2013.04-20130415_linux.tar.bz2
```
不使用gcc 4.8,与kernel有问题
```
$ tar xvf gcc-linaro-arm-linux-gnueabihf-4.7-2013.04-20130415_linux.tar.bz2
```
配置PATH路径, 添加gcc-linaro-arm-linux-gnueabihf-4.7-2013.04-20130415_linux/bin
```
$ vi ~/.bashrc
```
####获取linux-sunxi工具链
```
$ git clone git://github.com/linux-sunxi/u-boot-sunxi.git
$ git clone git://github.com/linux-sunxi/linux-sunxi.git
$ git clone git://github.com/linux-sunxi/sunxi-tools.git
$ git clone git://github.com/linux-sunxi/sunxi-boards.git
```
准备uboot启动区，参考
[U-Boot](http://linux-sunxi.org/U-Boot)

start|size|usage
-----|----|-----
0|8KB|Unused, available for partition table etc.
8|24KB|Initial SPL loader
32|512KB|u-boot
544|128KB|environment
672|352KB|reserved
1024|-|Free for partitions

准备uboot
```
$ cd u-boot-sunxi
$ make cubieboard CROSS_COMPILE=arm-linux-gnueabihf-
```
可用的boardtype为

boardtype|remark
---------|------
sun4i|Generic A10
sun5i|Generic A13
a13_olinuxino|Olimex A13-OLinuXino (SPL)
cubieboard|Cubieboard (SPL)
cubieboard_512|Cubieboard 512MB version (SPL)
mele_a1000|Mele A1000 (SPL)
a13_mid|A common A13 based tablet (SPL)
hackberry|Hackberry 1GB (SPL)
mini-x|Mini-X TV Box (SPL)
marsboard-a10|MarsBoard A10 (SPL)
som-a13|MarsBoard SOM-A13 (SPL)

重新准备boot.scr和script.bin文件
```
$ cd sunxi-tools
$ make fex2bin
$ cd ../sunxi-boards/sys_config/a10
$ ../../../sunxi-tools/fex2bin cubieboard.fex script.bin
```
把如下内容写入boot.cmd文件
```
setenv bootargs console=ttyS0,115200 root=/dev/mmcblk0p2 rootwait panic=10 ${extraargs}
fatload mmc 0 0x43000000 script.bin
fatload mmc 0 0x48000000 uImage
bootm 0x48000000
```
然后执行
```
$ mkimage -C none -A arm -T script -d boot.cmd boot.scr
```
生成boot.scr文件 
####在sdcard中预制android系统，启动cubieboard盒子步骤：
准备64位ubuntu
下载android源代码
```
$ wget http://dl.cubieboard.org/software/sources/cubieboard_opentv.tar.gz
```
编译代码
```
$ tar -zxf cubieboard_opentv.tar.gz
$ cd cubieboard_opentv/
$ source build/envsetup.sh && lunch #select cubieboard
$ make -j4
```
生成image
```
$ tools/pack-cm.sh
```
准备android工具
```
$ wget http://dl.linux-sunxi.org/users/arete74/tools.tar.gz
$ tar -zxvf tools.tar.gz
```
准备awutils
```
$ git clone https://github.com/Ithamar/awutils.git
$ cd awutils
```
从android image中提取文件

假设android image文件名是android.img
```
$ awimage -u android.img
```
生成文件夹android.dump,进入文件夹，找到如下文件:
```
RFSFAT16_BOOT_00000000000 (the boot partition)
RFSFAT16_RECOVERY_0000000 (the recovery partition)
RFSFAT16_SYSTEM_000000000 (the system partition, ext4 sparse)
RFSFAT16_BOOTLOADER_00000 (the bootloader partition)
```
复制相应文件:
```
$ cp android.img.dump/RFSFAT16_BOOT_00000000000 ../boot.img
$ cp android.img.dump/RFSFAT16_RECOVERY_0000000 ../recovery.img
$ cp android.img.dump/RFSFAT16_SYSTEM_000000000 ../system.img
$ cp android.img.dump/RFSFAT16_BOOTLOADER_00000 ../bootloader.img
$ cd ..
```
提起kernel文件和ramdisk文件
```
$ ./tools/split_bootimg.pl boot.img
Page size: 2048 (0x00000800)
Kernel size: 4215036 (0x004050fc)
Ramdisk size: 974998 (0x000ee096)
Second size: 0 (0x00000000)
Board name:
Command line: console=ttyS0,115200 rw init=/init loglevel=5
Writing boot.img-kernel ... complete.
Writing boot.img-ramdisk.gz ... complete.
```
解压缩ramdisk数据
```
$ mkdir boot
$ cd boot
$ gunzip -c ../boot.img-ramdisk.gz | cpio -i
$ tar -cpvf ../boot.tar *
$ cd ..
```
启动网络adb
修改default.prop文件
```
#set adb root
ro.secure=0
#set adb using TCP
service.adb.tcp.port=5555
#set adb using USB
#service.adb.tcp.port=-1
```
```
system/core/adb/adb.c
/* for the device, start the usb transport if the
 ** android usb device exists and the "service.adb.tcp.port" and
 ** "persist.adb.tcp.port" properties are not set.
 ** Otherwise start the network transport.
 */
```
所以可以动态设置，用setprop service.adb.tcp.port 5555来启动网络adb

To switch between TCP and USB modes with just one command, you can add this to /init.rc:
```
on property:service.adb.tcp.port=*
restart adbd

on property:service.adb.tcp.enable=1
setprop service.adb.tcp.port 5555

on property:service.adb.tcp.enable=0
setprop service.adb.tcp.port -1
```
And now you can use property service.adb.tcp.enable to enable or disable listening on port 5555. Run netstat to check whether it's listening. As you can see it will also trigger if you do wish to change service.adb.tcp.port manually.

转化kernel文件
```
$mkimage -A arm -O linux -T kernel -C none -a 0x40008000 -e 0x40008000 -n "Linux 2.6" -d boot.img-kernel uImage
```
提取system文件

如果运行有问题，使用sudo
```
$ ./tools/simg2img system.img system1.img
$ mkdir system
$ mount -o loop system1.img system
$ cd system
$ tar -cpvf ../system.tar *
$ cd ..
$ umount system
```
提取recovery文件
```
$ ./tools/split_bootimg.pl recovery.img
Page size: 2048 (0x00000800)
Kernel size: 4215036 (0x004050fc)
Ramdisk size: 974998 (0x000ee096)
Second size: 0 (0x00000000)
Board name:
Command line: console=ttyS0,115200 rw init=/init loglevel=5
Writing recovery.img-kernel ... complete.
Writing recovery.img-ramdisk.gz ... complete.
```

解压缩ramdisk数据
```
$ mkdir recovery
$ cd recovery
$ gunzip -c ../recovery.img-ramdisk.gz | cpio -i
$ tar -cpvf ../recovery.tar *
$ cd ..
```
准备SD卡分区

SD卡前1M区域置零，准备启动用

sh脚本中：
```
card=/dev/sdb
dd if=/dev/zero of=$card bs=1M count=1
sfdisk -R $card
cat <<EOT | sfdisk --in-order -uM $card
8,16,c
,36,83
,500,83
,,5
,1000,83
,16,83
,36,83
,125,83
,16,83
,,83
EOT
echo "mkfs......"
mkfs.vfat -n bootloader ${card}1
mkfs.ext4 -L boot       ${card}2
mkfs.ext4 -L system     ${card}3
mkfs.ext4 -L data       ${card}5
mkfs.ext4 -L misc       ${card}6
mkfs.ext4 -L recovery   ${card}7
mkfs.ext4 -L cache      ${card}8
mkfs.ext4 -L private    ${card}9
mkfs.vfat -n UDISK      ${card}10

echo "tune2fs......"
tune2fs -O ^huge_file ${card}2
tune2fs -O ^huge_file ${card}3
tune2fs -O ^huge_file ${card}5
tune2fs -O ^huge_file ${card}6
tune2fs -O ^huge_file ${card}7
tune2fs -O ^huge_file ${card}8
tune2fs -O ^huge_file ${card}9
#准备bootloader
dd if=./spl/sunxi-spl.bin of=$card bs=1024 seek=8
dd if=./u-boot.bin of=$card bs=1024 seek=32
```
创建android分区

partition|Size|Name|Fs|Description
---------|----|----|---|-----------
/dev/sdc1|16MiB|bootloader|VFAT|Files to assist the bootloader.
/dev/sdc2|36MiB|boot|EXT4|ramdisk
/dev/sdc3|500 MiB|system|EXT4|Android's /system partition
/dev/sdc4|Fill all space|extend|Extend Partition|
/dev/sdc5|300MiB|data|EXT4|
/dev/sdc6|16 MiB|misc|EXT4|
/dev/sdc7|36 MiB|recovery|EXT4|Android's recovery partition
/dev/sdc8|125 MiB|cache|EXT4|
/dev/sdc9|16 MiB|private|EXT4|
/dev/sdc10|1-2 GiB|UDISK|VAFT|

准备复制bootloader文件
```
mkdir bootloader
mount -o loop bootloader.img bootloader

mount ${card}1 /mnt/
cp uImage  /mnt
cp script.bin /mnt

cat >/mnt/uEnv.txt << EOT
fexfile=script.bin
kernel=uImage
extraargs=root=/dev/mmcblk0p2 loglevel=8 rootwait console=ttyS0,115200 rw init=/init mac_addr=00:AE:99:A3:E4:AF
boot_mmc=fatload mmc 0 0x43000000 ${fexfile}; fatload mmc 0 0x48000000 ${kernel}; bootm 0x48000000
EOT

cat >/mnt/uEnv_recovery.txt << EOT
fexfile=script.bin
kernel=uImage
extraargs=root=/dev/mmcblk0p7 loglevel=8 rootwait console=ttyS0,115200 rw init=/init mac_addr=00:AE:99:A3:E4:AF
boot_mmc=fatload mmc 0 0x43000000 ${fexfile}; fatload mmc 0 0x48000000 ${kernel}; bootm 0x48000000
EOT
cp boot.scr /mnt
umount /mnt
```
android旋转屏幕

屏是LANDSCAPE的，要让它默认显示为PORTRAIT.

1. kernel里要旋转FrameBuffer.启动参数里加入fbcon=rotate:1(0:正常屏; 1:顺时钟转90度; 2:转180度; 3:顺时钟转270度;) 最后生成的autoconf.h里有类似项：
    ```c_cpp
    #define CONFIG_CMDLINE "console=ttySAC0,115200 fbcon=rotate:1"
    ```
    此项的解析在$(kernel)/drivers/video/console/fbcon.c
    ```c_cpp
    static int __init fb_console_setup(char *this_opt);
    ```
    只是去初始化变量initial_rotation，然后initial_rotation会传递给其他需要的结构。注意：参考$(kernel)/documentation/fb/fbcon.txt
2. android OS旋转屏幕
系统默认是针对竖屏的，而MID使用的是横屏，所以需要做一个转换的动作。
```
PORTRAIT               LANDSCAPE         <------屏幕显示方式
ROTATION_0             ROTATION_90
ROTATION_90        ROTATION_180
ROTATION_180        ROTATION_270
ROTATION_270        ROTATION_0
```

准备ramdisk分区
```
$ mount ${card}2 /mnt
$ tar -xpvf boot.tar -C /mnt
```
修改init.sun4i.rc文件，替换nand
```
$ sed -i "s/nandd/mmcblk0p3/g"  /mnt/init.sun4i.rc
$ sed -i "s/nande/mmcblk0p5/g"  /mnt/init.sun4i.rc
$ sed -i "s/nandh/mmcblk0p8/g"  /mnt/init.sun4i.rc
$ sed -i "s/nandi/mmcblk0p9/g" /mnt/init.sun4i.rc
$ umount /mnt
```
修改init.sun4.rc文件，添加/mnt/sdcard
```
缺...
```

复制system分区
```
$ mount ${card}3 /mnt
$ tar -xpvf system.tar -C /mnt
$ umount /mnt
```
复制recovery分区
```
$ mount ${card}7 /mnt
$ tar -xpvf recovery.tar -C /mnt
$ sed -i "s/nandf/mmcblk0p6/g"  /mnt/ueventd.sun4i.rc
$ umount /mnt
```
重新配置 kernel

在cubieboard-tv-sdk目录下，编译kernel的命令行是
```
$ make -C kernel/allwinner/common O=/opt/cubieboard-tv-sdk/out/target/product/cubieboard/obj/KERNEL_OBJ ARCH=arm CROSS_COMPILE=" /opt/cubieboard-tv-sdk/prebuilt/linux-x86/toolchain/arm-eabi-4.4.3/bin/arm-eabi-" cubieboard_defconfig
```
配置文件在
```
kernel/allwinner/common/arch/arm/configs/cubieboard_defconfig
```
配置文件使用的是
```
out/target/product/cubieboard/obj/KERNEL_OBJ/.config
```
配置 android编译脚本

环境配置脚本
```
$ build/envsetup.sh
```
通过搜索
```
vendor/*/vendorsetup.sh
vendor/*/*/vendorsetup.sh
device/*/*/vendorsetup.sh
```
相关文件添加预定义的配置，cubieboard的配置文件在device/allwinner/cubieboard目录下


参考

[U-Boot build howto](http://linux-sunxi.org/FirstSteps)

##<a id="3"/>android sensors的底层配置
加载sensors的代码在 android_root/hardware/libhardware/hardware.c 文件中

两个加载路径
```
/** Base path of the hal modules */
#define HAL_LIBRARY_PATH1 "/system/lib/hw"
#define HAL_LIBRARY_PATH2 "/vendor/lib/hw"

/**
 * There are a set of variant filename for modules. The form of the filename
 * is "<MODULE_ID>.variant.so" so for the led module the Dream variants-
 * of base "ro.product.board", "ro.board.platform" and "ro.arch" would be:
 *
 * led.trout.so
 * led.msm7k.so
 * led.ARMV6.so
 * led.default.so
 */
```
加载环境变量
```c_cpp
static const char *variant_keys[] = {
    "ro.hardware",  /* This goes first so that it can pick up a different
                       file on the emulator. */
    "ro.product.board",
    "ro.board.platform",
    "ro.arch"
};
```
调用property_get函数，位于
```
android_root/system/core/include/cutils/properties.h
android_root/system/core/libcutils/properties.c
```
调用__system_property_get函数，位于
```
android_root/bionic/libc/include/sys/__system_properties.h
```

配置文件路径位于
```c_cpp
#define PROP_PATH_RAMDISK_DEFAULT  "/default.prop"
#define PROP_PATH_SYSTEM_BUILD     "/system/build.prop"
#define PROP_PATH_SYSTEM_DEFAULT   "/system/default.prop"
#define PROP_PATH_LOCAL_OVERRIDE   "/data/local.prop"
```
变量文件在/system/build.prop文件中

##<a id="4"/>android permissions的设置

###Android权限
1. 权限 每个程序在安装时都有建立一个系统ID，如app_15，用以保护数据不被其它应用获取。Android根据不同的用户和组，分配不同权限，比如访问SD卡，访问网络等等。底层映射为Linux权限。
2. 应用申请权限
    1. 应用开发者通过AndroidManifest.xml中<uses-permission>指定对应权限，再映射到底层的用户和组，默认情况下不设定特殊的权限。AndroidManifest加入权限后系统安装程序时会在图形界面中提示权限
    2. 如果是缺少某个权限（程序中使用的某种权限而在AndroidManifest.xml中并未声名），程序运行时会在logcat中打印出错误信息requires <permission>
    3. 与某个进程使用相同的用户ID 应用程序可与系统中已存在的用户使用同一权限，需要在AndroidManifest.xml中设置sharedUserId，如android:sharedUserId="android.uid.shared"，作用是获得系统权限，但是这样的程序属性只能在build整个系统时放进去（就是系统软件）才起作用，共享ID的程序必须是同一签名的
3. Android权限的实现
    1. 第一层：由应用设置，修改AndroidManifest.xml，形如：
    ```
    <uses-permission android:name=”android.permission.INTERNET”/>
    ```
    2. 第二层：框架层，权限对应组，frameworks/base/data/etc/platform.xml，形如：
    ```
    <permission name=”android.permission.INTERNET”><group gid=inet” /></permission>
    ```
    3. 第三层：系统层，系统的权限，system/core/include/private/android_filesystem_config.h,形如：
    ```
    #define AID_INET 3003 建立SOCKET的权限 …… { “inet”, AID_INET, },\
    ```
4. 系统权限
    1. 特殊权限的用户
    ```
    system uid 1000
    radio uid 1001
    ```
    2. 查看可用系统的权限
    ```
    $ adb shell
    $ pm list permissions
    ```
5. framework层对权限的判断
    1. 相关源码实现
    ```
    frameworks/base/services/java/com/android/server/PackageManagerService.java
    frameworks/base/services/java/com/android/server/am/ActivityManagerService.java
    ```
    2. 在系统层，如何查看某个应用的权限
        1. 在应用进程开启时，ActivityManagerService.java会在logcat中输出该应用的权限，形如：
        ```
        >I/ActivityManager(1730): Start proc com.anbdroid.phone for restart com.android.phone:pid=2605 uid=1000 gids={3002,3001,3003}
        ```
        即它有3001,3002,3003三个权限：访问蓝牙和建立socket
        2. 注意：此打印输出在应用第一次启动时。如果进程已存在，需要先把对应进程杀掉，以保证该进程重新启动，才能显示
        3. 具体实现，见：
        ```
        framewors/base/services/java/com/android/server/am/ActivityManagerService.java
        ```
        的函数startProcessLocked()，其中取其组信息的具本语句是 mContext.getPackageManager().getPackageGids(app.info.packageName);

###Android系统签名

安装在设备中的每一个apk文件，Android给每个APK进程分配一个单独的用户空间,其manifest中的userid就是对应一个Linux 用户都会被分配到一个属于自己的统一的Linux用户ID，并且为它创建一个沙箱，以防止影响其他应用程序（或者其他应用程序影响它）。用户ID 在应用程序安装到设备中时被分配，并且在这个设备中保持它的永久性。 

通过Shared User id,拥有同一个User id的多个APK可以配置成运行在同一个进程中.所以默认就是可以互相访问任意数据. 也可以配置成运行成不同的进程, 同时可以访问其他APK的数据目录下的数据库和文件.就像访问本程序的数据一样.

对于一个APK来说，如果要使用某个共享UID的话，必须做三步：

1. 在Manifest节点中增加android:sharedUserId属性。
2. 在Android.mk中增加LOCAL_CERTIFICATE的定义。
    如果增加了上面的属性但没有定义与之对应的LOCAL_CERTIFICATE的话，APK是安装不上去的。提示错误是：
    ```
    Package com.test.MyTest has no signatures that match those in shared user android.uid.system; ignoring!
    ```
    也就是说，仅有相同签名和相同sharedUserID标签的两个应用程序签名都会被分配相同的用户ID。例如所有和 media/download相关的APK都使用android.media作为sharedUserId的话，那么它们必须有相同的签名media。
3. 把APK的源码放到packages/apps/目录下，用mm进行编译。

####举例说明一下。

系统中所有使用android.uid.system作为共享UID的APK，都会首先在manifest节点中增加 android:sharedUserId="android.uid.system"，然后在Android.mk中增加 LOCAL_CERTIFICATE := platform。可以参见Settings等

系统中所有使用android.uid.shared作为共享UID的APK，都会在manifest节点中增加 android:sharedUserId="android.uid.shared"，然后在Android.mk中增加 LOCAL_CERTIFICATE := shared。可以参见Launcher等

系统中所有使用android.media作为共享UID的APK，都会在manifest节点中增加 android:sharedUserId="android.media"，然后在Android.mk中增加LOCAL_CERTIFICATE := media。可以参见Gallery等。

另外，应用创建的任何文件都会被赋予应用的用户标识，并且正常情况下不能被其他包访问。当通过 getSharedPreferences（String，int）、openFileOutput（String、int）或者 openOrCreate Database（String、int、SQLiteDatabase.CursorFactory）创建一个新文件时，开发者可以同时或分别使用 MODE_WORLD_READABLE和MODE_WORLD_RITEABLE标志允许其他包读/写此文件。当设置了这些标志后，这个文件仍然属于自 己的应用程序，但是它的全局读/写和读/写权限已经设置，所以其他任何应用程序可以看到它。

####关于签名：

build/target/product/security目录中有四组默认签名供Android.mk在编译APK使用：

1. testkey：普通APK，默认情况下使用。
2. platform：该APK完成一些系统的核心功能。经过对系统中存在的文件夹的访问测试，这种方式编译出来的APK所在进程的UID为system。
3. shared：该APK需要和home/contacts进程共享数据。
4. media：该APK是media/download系统中的一环。

应用程序的Android.mk中有一个LOCAL_CERTIFICATE字段，由它指定用哪个key签名，未指定的默认用testkey.

[Android中startActivity中的permission检测与UID机制](http://yelinsen.iteye.com/blog/977683)

参考:

应用层的permission定义在
```
frameworks/base/core/res/AndroidManifest.xml
```
包含了所有的permission隶属于哪些层级(normal, dangerous, signature, signatureOrSystem)
[android 权限的实现](http://blog.csdn.net/xieyan0811/article/details/6083019?reload)

##<a id="5"/>android系统源代码编译
正常情况，开vpn，访问
[Android Source](http://source.android.com/)
即可获取大部分编译android系统的信息
如果无法翻墙，可以利用omap的镜像获取android source.
```
repo init -u git://git.omapzoom.org/platform/manifest
```
剩下部分雷同。

用repo start保证代码切换完整，之后编译代码出的问题可以通过
[Android Source on Google Code](https://code.google.com/p/android/)
的issue tracker查询到各种编译遇到的坑。

##<a id="6"/>android系统按键映射表

[android系统的按键映射参考](http://source.android.com/devices/input/keyboard-devices.html)

代码位于:
```
frameworks/base/services/input
frameworks/base/include/ui
frameworks/base/libs/ui
```
按键映射表位于:
```
frameworks/base/data/keyboards
```
NDK头文件位于：
```
platforms/android-xx/arch-arm/usr/include/android/keycodes.h
```
##<a id="7"/>elinux开发
[Embedded Linux Wiki](http://elinux.org)

##<a id="8"/>adb无法找到设备的解决方法
[adb无法连接usb设备的官方解决办法](http://developer.android.com/tools/device.html)

补充方法： 在~/.android/adb_usb.ini文件中添加vendorId,如小米(0x2717)

##<a id="9"/>Android APK的反编译

You need Three Tools to decompile an APK file.

dex2jar - Tools to work with android .dex and java .class files.

apktool - A tool for reverse engineering Android apk files.

jd-gui - Java Decompiler is a tools to decompile and analyze Java 5 “byte code” and the later versions.

for more how-to-use-dextojar. Hope this will help You and all! :)

三个工具完成APK的反编译:

1. dex2jar，把dex文件转成java的.class文件 [dex2jar](http://code.google.com/p/dex2jar/)
2. apktool, android apk的反向工程工具 [apk-tool](https://code.google.com/p/android-apktool/)
3. jd-gui，查看.class文件的浏览器工具。 [jd-gui](http://jd.benow.ca/)

##<a id="10"/>Android 程序调试

[使用ddms调优程序性能](http://www.linuxtopia.org/online_books/android/devguide/guide/developing/tools/ddms.html)

##<a id="11"/>Linux I/O重定向
Linux Shell 环境中支持输入输出重定向，用符号"<"和">"来表示。0、1和2分别表示标准输入、标准输出和标准错误信息输出，可以用来指定需要重定向的标准输入或输出，比如 2>a.txt 表示将错误信息输出到文件a.txt中。

同时，还可以在这三个标准输入输出之间实现重定向，比如将错误信息重定向到标准输出，可以用 2>&1来实现。

Linux下还有一个特殊的文件/dev/null，它就像一个无底洞，所有重定向到它的信息都会消失得无影无踪。这一点非常有用，当我们不需要回显程序的所有信息时，就可以将输出重定向到/dev/null。

如果想要正常输出和错误信息都不显示，则要把标准输出和标准错误都重定向到/dev/null， 例如：
```
$ ls 1>/dev/null 2>/dev/null
```
还有一种做法是将错误重定向到标准输出，然后再重定向到 /dev/null，例如：
```
$ ls >/dev/null 2>&1
```

注意：此处的顺序不能更改，否则达不到想要的效果，此时先将标准输出重定向到 /dev/null，然后将标准错误重定向到标准输出，由于标准输出已经重定向到了/dev/null，因此标准错误也会重定向到/dev/null，于是一切静悄悄:-)

另外+:
```
$ make >& make_log
```

意思是把标准输出和错误输出都重定向, make>out 只重定向标准输出!!!!!

\>log 表示把标准输出重新定向到文件log中

& log 表示把标准输出和错误输出都定向到文件log中，相当于 >log 2>&1

* * * *

###I/O重定向详解及应用实例

1. 基本概念（这是理解后面的知识的前提，请务必理解） 
    1. I/O重定向通常与 FD有关，shell的FD通常为10个，即 0～9；
    2. 常用FD有3个，为0（stdin，标准输入）、1（stdout，标准输出）、2（stderr，标准错误输出），默认与keyboard、monitor、monitor有关；
    3. 用 < 来改变读进的数据信道(stdin)，使之从指定的档案读进；
    4. 用 > 来改变送出的数据信道(stdout, stderr)，使之输出到指定的档案；
    5. 0 是 < 的默认值，因此 < 与 0<是一样的；同理，> 与 1> 是一样的；
    6. 在IO重定向 中，stdout 与 stderr 的管道会先准备好，才会从 stdin 读进资料；
    7. 管道“|”(pipe line):上一个命令的 stdout 接到下一个命令的 stdin;
    8. tee 命令是在不影响原本 I/O 的情况下，将 stdout 复制一份到档案去;
    9. bash（ksh）执行命令的过程：分析命令－变量求值－命令替代（和$( )）－重定向－通配符展开－确定路径－执行命令；
    10. ( ) 将 command group 置于 sub-shell 去执行，也称 nested sub-shell，它有一点非常重要的特性是：继承父shell的Standard input, output, and error plus any other open file descriptors。
    11. exec 命令：常用来替代当前 shell 并重新启动一个 shell，换句话说，并没有启动子 shell。使用这一命令时任何现有环境都将会被清除。exec 在对文件描述符进行操作的时候，也只有在这时，exec 不会覆盖你当前的 shell 环境。

2. 基本IO cmd > file 把 stdout 重定向到 file 文件中 cmd >> file 把 stdout 重定向到 file 文件中(追加) cmd 1> fiel 把 stdout 重定向到 file 文件中 cmd > file 2>&1 把 stdout 和 stderr 一起重定向到 file 文件中 cmd 2> file 把 stderr 重定向到 file 文件中 cmd 2>> file 把 stderr 重定向到 file 文件中(追加) cmd >> file 2>&1 把 stderr 和 stderr 一起重定向到 file 文件中(追加) cmd < file >file2 cmd 命令以 file 文件作为 stdin，以 file2 文件作为 stdout cat <>file 以读写的方式打开 file cmd < file cmd 命令以 file 文件作为 stdin cmd << delimiter Here document，从 stdin 中读入，直至遇到 delimiter 分界符

##<a id="12"/>wget使用技巧

[使用wget来爬网站内容](http://stackoverflow.com/questions/8755229/how-to-download-all-files-from-a-website-using-wget)

##<a id="13"/>网络工具使用

端口映射工具：
1. socat
本地tcp映射到udp端口:
```
socat tcp4-listen:5353,fork udp:192.168.56.101:10101
```
将本地tcp 5353端口映射到192.168.56.101的udp端口10101
```
socat -T15 udp4-recvfrom:10101,fork tcp:127.0.0.1:5353
```
将本地udp 10101端口接收的内容映射到127.0.0.1的tcp 5353端口
2. nc
```
nc -l 1234
```
listen on tcp 1234端口
```
nc 1234
```
向本地 tcp 1234端口发数据
```
nc -u 1234
```
向本地 udp 1234端口发数据
3. ssh
网络扫描工具：nmap

参考：
[SSH Port Forwarding for TCP and UDP Packets](http://www.digitalinternals.com/network/ssh-port-forwarding-tcp-udp/365/)


##<a id="14"/>samba服务挂载
```
mount.cifs //192.168.1.3/Tools /mnt -o user=<name>,pass=<pass>,dom=duwei
或
mount -t cifs //192.168.1.3/Tools /mnt -o user=<name>,pass=<pass>,dom=duwei
```

##<a id="15"/>usbfs的问题
###在这里详述 usbfs的问题

usbfs is no longer supported by the kernel (not since ~2.6.31-17 IIRC) so quite a few older printers cause problems. There is a workaround, not terribly satisfactory, but usually does the job. The following commands: Code:
```
sudo mount --bind /dev/bus /proc/bus
sudo ln -s /sys/kernel/debug/usb/devices /proc/bus/usb/devices
```
before printing should do the necessary. After printing it's probably advisable to reverse the above with: Code:
```
sudo umount   /proc/bus
```
as you may well break something else.

游戏手柄通过USB模块和系统交换数据,游戏程序通过USB文件节点进行读取数据的操作,对于该USB节点,需要(rw)读/写权限.
在linux中,我们通过配置udev模块中的配置文件,通过添加一行 位置: /etc/udev/rules.d/中的某个rules文件中添加一行:
```
SUBSYSTEM=="usb", ATTRS{idVendor}=="ffff", ATTRS{idProduct}=="ffff", ACTION=="add", ENV{DEVTYPE}=="usb_device", NAME"bus/usb/$env{BUSNUM}/$env{DEVNUM}", MODE="0666"
```
如上一行表示如果接入的usb设备vid,pid是ffff,ffff,的情况下,在/dev/bus/usb下生成的文件节点模式设置为0666,即游戏程序拥有该节点的读/写权限, 这样游戏程序就可以和游戏手柄驱动进行交互.而对于其他的USB设备,则都采用系统默认的配置方式生成文件节点.

在android系统中的linux内核采用另外一套机制,配置文件是根目录下的ueventd.rc文件,在其中添加一行
```
/dev/bus/usb/*    0666    system    usb
```
但是缺陷是无法限定某一个vid,pid的设备权限

补充：

在android 系统中，因为游戏要读取鼠标数据，故需要将 /dev/input/event/* 的权限亦改为 666

此修改仅用于2.x 版本，4.0以上系统不需要修改

####ubuntu下手机usb连接权限的问题
在命令行中
```
fastboot devices
```
却无法显示任何一个devices
```
fastboot reboot
```
显示waiting for devices

解决办法:配置udev规则文件，调整权限。

修改/etc/udev/rule.d目录下的51-android.rules文件（根据情况，这个文件名可能略有不同），备份是修改文件的一个好习惯。
```
# fastboot protocol on passion (Nexus One)
SUBSYSTEM=="usb", ATTR{idVendor}=="0bb4", ATTR{idProduct}=="0fff", MODE="0666", OWNER="<tom>"
```
注意到idVendor，就是我们lsusb的时候，显示出来的id，我的显示的是0bb4，然后看注释，要改的是第二句，将MODE改成0666 保存。

然后
```
sudo chmod a+x 51-android.rules

sudo udevadm control --reload-rules
```
重新插拔下usb，再输入fastboot devices命令，应该就能找到device

如果还不行，关机重启下试试

参考

[ueventdrc](http://www.vikesh.in/posts/2011-08-29-uventdrc.html)

##<a id="16"/>Linux用户密码设置
如果系统管理员希望添加一个用户以后，让该用户第一次登录以后自己设置自己的密码，那么就要使得用户的初始密码或者空密码立刻过期，强制用户第一次登录后立刻修改密码。

为了强制用户第一次登录时设置一个新密码，请按照下面的指示来做，但是需要的注意的时候如果用户是通过SSH远程登录进去的，那么该方法是不能生效的。

1. 锁定用户密码 - 如果用户不存在，用useradd添加用户，但是不设置密码，使得该帐号仍然处于锁定状态，如果用户密码已经激活，则用下面命令锁定：
```
usermod -L username
```
2. 强制密码立刻过期，该命令设置用户上次修改密码的时间为纪元时间（1970年1月1日），这样会使得该命令立刻过期，而不论密码过期策略的设置。
```
chage -d 0 username
```
3. 对帐号解锁 - 这里有两个方法来实现，管理员可以设置一个新密码或者设置空密码：
注意：不要使用passwd来设置密码，因为它会使得刚才设置的使密码立刻过期的设置失效。
为了设置初始密码，使用下面步骤：
启动Python:
```
$ python
Python 2.3.4 (#1, Feb 6 2006, 10:38:46) [GCC 3.4.5 20051201 (Red Hat 3.4.5-2)] on linux2 Type "help", "copyright", "credits" or "license" for more information.
>>>
```
在提示符>>>后输入下面命令：
```
import crypt;
print crypt.crypt("userpassword","username")
```
输出将会类似是： 12CsGd8FRcMSM
输入[Ctrl]+[D]退出python。
拷贝刚才的输出密码结果，12CsGd8FRcMSM，用在下面的命令中：
```
usermod -p "12CsGd8FRcMSM" username 
```
当然也可以给用户给一个空密码：
```
usermod -p "" username 
```
注： 虽然空密码很方便，但是有安全风险。
然后登录该用户，就会提示输入密码。

####其他办法：

使用下面方法也可以实现：

1. 使用useradd添加用户
2. 使用passwd设置用户密码
3. 使用usermod -L来锁密码
4. 强制用户帐号过期chage -d 0 username
5. 解锁用户帐号

上面流程的示例：
```
# useradd dan
//Changing password for user dan.
# passwd dan
New password:
Retype new password:
passwd: all authentication tokens updated successfully.
# usermod -L dan
# chage -d 0 dan
# usermod -U dan
```
当然用户dan第一次登录，就会提示设置密码如下：
```
// Changing password for dan (current) UNIX
$ su dan
Password:
You are required to change your password immediately (root enforced)
password:
New password:
Retype new password:
```
本文摘自redhat官方文档！

根据本人理解只需2步：

1. 建立用户账户
2. 强制用户帐号过期

若需清空账户只需将/etc/shadow中相应用户的密码字段（字段以“：”分隔，第二个字段） 清空即可。

##<a id="17"/>vim使用技巧
![vim键盘图](/image/o_vim.png)
![vim命令图解](/image/vim_cheet_sheet_full.png)



[Table of Contents](#misc)

