#!/bin/bash

PA=../DIRC_Cookies_1116
#DC=739
DC=764
FD=../dc$DC
CO=cookie

for i in 0 1 2 3
do 

./parse_transmittance -ifile $PA/twoquartz_ca/twoquartz_ca_${i}0a.txt -dark_current $DC > $FD/transmittance_cookie1_0_${i}0.txt
./parse_transmittance -ifile $PA/twoquartz_air/twoquartz_air_${i}0.txt -dark_current $DC > $FD/transmittance_cookie2_0_${i}0.txt
./parse_transmittance -ifile $PA/twoquartz_oil/twoquartz_oil_${i}0a.txt -dark_current $DC > $FD/transmittance_cookie3_0_${i}0.txt

./parse_transmittance -ifile $PA/onequartz/onequartz_${i}0a.txt -dark_current $DC > $FD/transmittance_cookie0_0_${i}0.txt

./parse_transmittance -ifile $PA/cookief/cookief_${i}0.txt -dark_current $DC > $FD/transmittance_cookief_${i}0.txt

./parse_transmittance -ifile $PA/cookier_1/cookier_1_${i}0.txt -dark_current $DC > $FD/transmittance_cookier_1_${i}0.txt
./parse_transmittance -ifile $PA/cookier_2/cookier_2_${i}0.txt -dark_current $DC > $FD/transmittance_cookier_2_${i}0.txt

./parse_transmittance -ifile $PA/cookief/cookief_${i}0.txt -dark_current $DC > $FD/transmittance_cookief_${i}0.txt

./parse_transmittance -ifile $PA/${CO}5/${CO}5_3_${i}0.txt -dark_current $DC > $FD/transmittance_${CO}5_3_${i}0.txt
./parse_transmittance -ifile $PA/${CO}15/${CO}15_3_${i}0.txt -dark_current $DC > $FD/transmittance_${CO}15_3_${i}0.txt
./parse_transmittance -ifile $PA/${CO}7_1/${CO}7_1_${i}0.txt -dark_current $DC > $FD/transmittance_${CO}7_1_${i}0.txt
./parse_transmittance -ifile $PA/${CO}7_2/${CO}7_2_${i}0.txt -dark_current $DC > $FD/transmittance_${CO}7_2_${i}0.txt

for j in 6 8 9 10 13 14 16
do 

./parse_transmittance -ifile $PA/${CO}${j}_1/${CO}${j}_1_${i}0.txt -dark_current $DC > $FD/transmittance_${CO}${j}_1_${i}0.txt

echo "./parse_transmittance -ifile $PA/${CO}${j}_1/${CO}${j}_1_${i}0.txt -dark_current $DC > $FD/transmittance_${CO}${j}_1_${i}.txt" 

./parse_transmittance -ifile $PA/${CO}${j}_2/${CO}${j}_2_${i}0.txt -dark_current $DC > $FD/transmittance_${CO}${j}_2_${i}0.txt

if (j==6) then
./parse_transmittance -ifile $PA/${CO}${j}/${CO}${j}_2_15.txt -dark_current $DC > $FD/transmittance_${CO}${j}_2_15.txt
./parse_transmittance -ifile $PA/${CO}${j}/${CO}${j}_2_15.txt -dark_current $DC > $FD/transmittance_${CO}${j}_2_15.txt
fi

done

done

find $FD/ -name "*.txt" -size -90c -delete