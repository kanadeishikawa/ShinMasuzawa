#!/bin/bash

rm -f *.gz
rm -f *.aux
rm -f *.log
rm -f *.lof
rm -f *.lot
rm -f *.toc
rm -f *.dvi
rm -f *.bbl
rm -f *.bcf
rm -f *.blg
rm -f *.xml
uplatex -synctex=1 Result_Tohoku.tex
uplatex -synctex=1 Result_Tohoku.tex
dvipdfmx -f ptex-haranoaji.map Result_Tohoku.dvi
#uplatex -synctex=1 Result_Tohoku_kouhan.tex
#uplatex -synctex=1 Result_Tohoku_kouhan.tex
#dvipdfmx -f ptex-haranoaji.map Result_Tohoku_kouhan.dvi
rm -f *.gz
rm -f *.aux
rm -f *.log
rm -f *.lof
rm -f *.lot
rm -f *.toc
rm -f *.dvi
rm -f *.bbl
rm -f *.bcf
rm -f *.blg
rm -f *.xml
date
