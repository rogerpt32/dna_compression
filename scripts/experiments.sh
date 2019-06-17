#!/bin/bash 

cd ../src/
make clean
make
mkdir -p ../data/

echo -e "Experiments" > ../results/results.txt

for i in `seq 1 30`;
do
    for j in `seq 1 30`;
    do
        rm -f ../data/test.gz ../data/test_compressed.dna
        pow=$( echo "2^$i" | bc )
        c=$(( 30*(i-1) + j ))
        echo -ne "$(printf %03d $c)/900 \t size $pow"\\r
        echo -e "\n\nSize $pow\n" >> ../results/results.txt
        ./generator $pow ../data/test.txt
        echo -e "gzip:" >> ../results/results.txt
        { time tar -czvf ../data/test.gz ../data/test.txt >/dev/null; } 2>&1 | grep real >> ../results/results.txt
        echo -ne "compr " >> ../results/results.txt
        stat --printf="%s" ../data/test.gz >> ../results/results.txt
        echo -e "\nour:" >> ../results/results.txt
        { time ./compress ../data/test.txt >/dev/null; } 2>&1 | grep real >> ../results/results.txt
        echo -ne "compr " >> ../results/results.txt
        stat --printf="%s" ../data/test_compressed.dna >> ../results/results.txt
        
    done
done

echo -e "\n"
rm ../data/test.txt
cd ../scripts/
# rm ../results/*.txt