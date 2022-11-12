cp attack.template attack.c
rm -f attack_tmp*
./generate-attack-array < attack.c > attack-array.h
sed -i 's:#include://#include:g' attack.c
cat attack.c >> attack-array.h 
mv attack-array.h attack.c
./generate-attack-array < attack.c > attack-array.h
sed -i 's:r compile_attack:r xx_compile_attack:g' attack.c
cat attack.c >> attack-array.h 
mv attack-array.h attack.c
make clean
make
sudo make install
