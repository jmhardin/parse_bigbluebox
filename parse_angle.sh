#!/bin/bash

PA=../DIRC_Cookies_1116
#DC=739
DC=762
FD=../dc$DC
CO=cookie
A=ANGLE_

for i in 00 05 10 20 30 45
do 

./parse_transmittance -ifile $PA/${A}${CO}10_2/A_${CO}10_2_${i}_x10.txt -dark_current $DC > $FD/${A}transmittance_cookie10_2_${i}.txt
./parse_transmittance -ifile $PA/${A}${CO}14_2/A_${CO}14_2_${i}_x10.txt -dark_current $DC > $FD/${A}transmittance_cookie14_2_${i}.txt
./parse_transmittance -ifile $PA/${A}${CO}6_2/A_${CO}6_2_10_${i}.txt -dark_current $DC > $FD/${A}transmittance_cookie6_2_${i}.txt
./parse_transmittance -ifile $PA/${A}${CO}7_2/A_${CO}7_2_${i}a.txt -dark_current $DC > $FD/${A}transmittance_cookie7_2_${i}.txt
./parse_transmittance -ifile $PA/${A}${CO}f/A_${CO}f_${i}_x10.txt -dark_current $DC > $FD/${A}transmittance_cookief_${i}.txt
./parse_transmittance -ifile $PA/${A}${CO}r_2/A_${CO}r2_${i}_x10.txt -dark_current $DC > $FD/${A}transmittance_cookier_2_${i}.txt
./parse_transmittance -ifile $PA/${A}onequartz/A_onequartz_${i}_x10.txt -dark_current $DC > $FD/${A}transmittance_onequartz_${i}.txt

done

#find $FD/ -name "*.txt" -size -90c -delete