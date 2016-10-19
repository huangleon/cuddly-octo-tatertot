#!/usr/bin/env python
# -*- coding: utf-8 -*-

"""extract_mp3.py: py module to extract mp3 from html"""

__author__ = "Huang, Liang"
__credits__ = ["Huang, Liang"]

__license__ = "MIT"
__version__ = "0.0.1"
__maintainer__ = "Huang, Liang"
__email__ = "huangleon@gmail.com"
__status__ = "in process"


import requests
import re

def main():
    print "hello world"

    # request for page content
    r = requests.get('http://www.ishuyin.com/player.php?mov_id=5204&look_id=186&player=down')
    r.raise_for_status()
#    print r.text

    # use regular expression to search key content
    # the key content is:
    # <script>\r\n\tvar u="*104*116*116*112*58*47*47*102*100*102*115*46*120*109*99*100*110*46*99*111*109*47*103*114*111*117*112*52*47*77*48*53*47*57*56*47*50*66*47*119*75*103*68*115*49*82*84*111*71*75*65*81*104*87*99*65*68*52*53*45*67*68*119*121*83*85*48*49*53*46*109*112*51*";\r\n\tvar uArr=u.split("*");\r\n\tvar n = uArr.length;\r\n\tvar x = '';\r\n\tfor(i=1;i<n-1;i++){\r\n\t   x += String.fromCharCode(uArr[i]);\r\n\t}\r\n\t$("#urlDown").attr('href',x);\r\n\r\n</script>

    m = re.search('var u=\"(.*)\"', r.text)
    encoded_chars = m.group(1).split('*')
    decoded_url = ''
    for ch in encoded_chars:
        if ch != u'':
            decoded_url += unichr(int(ch))

    print decoded_url

if __name__ == '__main__':
    main()
