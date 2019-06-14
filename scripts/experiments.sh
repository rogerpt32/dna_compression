#!/bin/bash 

cd ../src/
make clean
make
mkdir -p ../data/

echo "Experiments\n" > ../results/results.txt

for i in `seq 1 30`;
do
    rm -f ../data/test.gz ../data/test_compressed.dna
    pow=$( echo "2^$i" | bc )
    echo -ne "$i/30\t size $pow"\\r
    echo -e "\nSize $pow\n" >> ../results/results.txt
    ./generator $pow ../data/test.txt
    echo -e "gzip\n" >> ../results/results.txt
    { time tar -czvf ../data/test.gz ../data/test.txt >/dev/null; } 2>&1 | grep real >> ../results/results.txt
    echo -e "\ncompressed" >> ../results/results.txt
    stat --printf="%s" ../data/test.gz >> ../results/results.txt
    echo -e "\nour\n" >> ../results/results.txt
    { time ./compress ../data/test.txt >/dev/null; } 2>&1 | grep real >> ../results/results.txt
    echo -e "\n compressed" >> ../results/results.txt
    stat --printf="%s" ../data/test_compressed.dna >> ../results/results.txt
    
done

rm ../data/test.txt
cd ../scripts/
# rm ../results/*.txt