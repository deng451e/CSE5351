#!/bin/bash


for i in {1..100}; do 
    ibrun  -np 2  ./a.out 2  64 >> q2_64.log 
    
done
echo "--------------------------" >> q2_64.log 

for i in {1..100}; do 
    ibrun  -np 4  ./a.out 4  64 >> q2_64.log 
     
done

echo "--------------------------" >> q2_64.log 
for i in {1..100}; do 
    ibrun  -np 8 ./a.out 8  64 >> q2_64.log 
     
done
echo "--------------------------" >> q2_64.log 

for i in {1..100}; do 
    ibrun  -np 16  ./a.out 16 64  >> q2_64.log 
     
done 
echo "--------------------------" >> q2_64.log 




for i in {1..100}; do 
    ibrun  -np 2  ./a.out 2  128 >> q2_128.log 
     
done

echo "--------------------------" >> q2_128.log


for i in {1..100}; do 
    ibrun  -np 4  ./a.out 4  128 >> q2_128.log
 
     
done
echo "--------------------------" >> q2_128.log
 

for i in {1..100}; do 
    ibrun  -np 8 ./a.out 8  128 >> q2_128.log
 
    
done
echo "--------------------------" >> q2_128.log

for i in {1..100}; do 
    ibrun  -np 16  ./a.out 16 128  >> q2_128.log
 
     
done
echo "--------------------------" >> q2_128.log
 