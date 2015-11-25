#!/bin/bash
date_start=$(date +%s)
echo compile indepth
g++ Indepth.cpp netdata.cpp -o indepth &
echo compile acquaintance
g++ Acquaintance.cpp netdata.cpp -o acquaintance &
echo compile target
g++ Target.cpp netdata.cpp -o target &
echo compile random
g++ Random.cpp netdata.cpp -o random &
wait
date_end=$(date +%s)
echo "compile time：$((date_end-date_start))s"

date_start=$(date +%s)
./indepth &
./acquaintance &
wait
./target &
./random &
wait
echo combine result
paste indepth.csv acquaintance.csv target.csv random.csv > result.tmp
sed 's/\t/,/g' result.tmp > result.csv
rm -f result.tmp
rm -f indepth.csv
rm -f acquaintance.csv
rm -f target.csv
rm -f random.csv
echo finish
date_end=$(date +%s)
echo "run time：$((date_end-date_start))s"
