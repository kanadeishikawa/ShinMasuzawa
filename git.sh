#!/bin/bash

DATE=`TZ='Asia/Tokyo' date`
echo ${DATE}

cp ShinMasuzawa.cc backup
cp makefile backup
cp LaTeX/Result_Tohoku.tex backup
cp LaTeX/compile_latex.sh backup
git add -A
#git add -u
git commit -m "AUTO COMMIT at ${DATE}"
git push
git log
date
