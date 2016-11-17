OUTFOLDER=ofolder
mkdir $OUTFOLDER

for MIR in thor eci mirror1 mirror2 mirror3 mirror4 mirror5 mirror6 ;
do
	for ANGLE in 30 45 60 75;
	do
		./parse_reflectance Dirc_mirrors_0316/direct_reference/direct_reference_${ANGLE}deg.txt Dirc_mirrors_0316/angle_${ANGLE}/${MIR}_${ANGLE}deg.txt > ${OUTFOLDER}/${MIR}_${ANGLE}deg_refl.csv
		./parse_reflectance Dirc_mirrors_0316/direct_reference/direct_reference_${ANGLE}deg_f3.txt Dirc_mirrors_0316/angle_${ANGLE}/${MIR}_${ANGLE}deg_f3.txt > ${OUTFOLDER}/${MIR}_${ANGLE}deg_refl_f3.csv 
	done
done
for MIR in thor eci mirror1 mirror2 mirror3 mirror4 mirror5 mirror6 ;
do
	rm ${OUTFOLDER}/${MIR}_integrated_refl.csv
	for ANGLE in 30 45 60 75;
	do
		echo $ANGLE `./parse_reflectance -integrate Dirc_mirrors_0316/direct_reference/direct_reference_${ANGLE}deg.txt Dirc_mirrors_0316/angle_${ANGLE}/${MIR}_${ANGLE}deg.txt` >> ${OUTFOLDER}/${MIR}_integrated_refl.csv
	done
done
