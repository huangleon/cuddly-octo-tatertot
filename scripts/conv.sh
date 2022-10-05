#!/bin/bash
DRYRUN="0"

function conv_wav2mp3 () {
    SRCFILE=$1
    DSTFILE="$(basename $SRCFILE .wav).mp3"
    # https://trac.ffmpeg.org/wiki/Encode/MP3
    echo "ffmpeg -y -i '$SRCFILE' -q:a 0 '$DSTFILE'"
    if [[ $DRYRUN == "0" ]]; then
        ffmpeg -y -i "$SRCFILE" -q:a 0 "$DSTFILE"
    fi
}

WORKDINGDIR=""

if [[ $1 == "" ]]; then
    echo "usage: conv.sh [-n] <DIR>           <<<<<<<< convert all .wav file under <DIR> to .mp3 files"
    exit 1
fi

if [[ $1 == "-n" ]]; then
    DRYRUN="1"
    WORKINGDIR="$2"
else
    DRYRUN="0"
    WORKINGDIR="$1"
fi

if [[ $WORKINGDIR == "" ]]; then
    echo "usage: conv.sh [-n] <DIR>           <<<<<<<< convert all .wav file under <DIR> to .mp3 files"
    exit 1
fi

cd $WORKINGDIR

SAVEIFS=$IFS
IFS=$(echo -en "\n\b")
for f in `ls *.wav`; do
    conv_wav2mp3 "$f"
done
IFS=$SAVEIFS
