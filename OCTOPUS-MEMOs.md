#OCTOPUS MEMOs
* Misc
	* [What is the best way to merge mp3 files](#1)

##What is the best way to merge mp3 files?
[stackoverflow上的回答](http://stackoverflow.com/questions/62618/what-is-the-best-way-to-merge-mp3-files)

**Use ffmpeg or a similar tool to convert all of your MP3s into a consistent format, e.g.**
>ffmpeg -i originalA.mp3 -f mp3 -ab 128kb -ar 44100 -ac 2 intermediateA.mp3
>ffmpeg -i originalB.mp3 -f mp3 -ab 128kb -ar 44100 -ac 2 intermediateB.mp3

Then, at runtime, concat your files together:

>cat intermediateA.mp3 intermediateB.mp3 > output.mp3

Finally, run them through the tool MP3Val to fix any stream errors without forcing a full re-encode:

>mp3val output.mp3 -f -nb
