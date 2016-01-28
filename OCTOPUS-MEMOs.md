#OCTOPUS MEMOs

##Misc
* [What is the best way to merge mp3 files](#1)
* [Cannot connect to samba shared files after 4.1.14-1 upgrade.](#2)

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

EDIT: Looked at the upstream patch found at [patch-4.1.13-4.1.14.diffs.gz](http://samba.org/samba/ftp/patches/patch-4.1.13-4.1.14.diffs.gz) and found that they changed how the "smb_my_netbios_names" array is allocated in "samba-4.1.14/source3/lib/util_names.c" and must have broke "is_myname(cstring)". It's an upstream bug for sure.

EDIT2: Super simple workaround! Just shorten your NETBIOS name by adding "netbios name=\[15 chars or less, simple ASCII chars only\]" to your smb.conf.

EDIT3: Reported upstream: [samba-show-bug](https://bugzilla.samba.org/show_bug.cgi?id=11008)


[Troubleshooting Samba](https://www.samba.org/samba/docs/using_samba/ch12.html)

[Table of Contents](#misc)