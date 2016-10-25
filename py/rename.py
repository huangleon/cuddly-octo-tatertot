#!/usr/bin/env python
# -*- coding: utf-8 -*-

"""extract_mp3.py: rename mp3 file with padding '0' file name"""

__author__ = "Huang, Liang"
__credits__ = ["Huang, Liang"]

__license__ = "MIT"
__version__ = "0.0.1"
__maintainer__ = "Huang, Liang"
__email__ = "huangleon@gmail.com"
__status__ = "in process"

import glob
import shutil

def main():
    print "rename files"
    srcfiles = glob.glob('*.mp3')
    for fn in srcfiles:
        num = int(fn[3:len(fn)-7])
        dstfile = "target/" + fn[0:3] + "{0:03d}".format(num) + fn[len(fn)-7:]
        shutil.copyfile(fn, dstfile)

if __name__ == '__main__':
    main()
