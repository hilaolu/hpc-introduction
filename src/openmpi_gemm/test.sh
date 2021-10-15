mpic++ main.cpp -lopenblas -O3 -march=native
i=50
while [ $i -le 3000 ]
do
    mpirun  ./a.out $i 
    i=$(($i+50))
done
    