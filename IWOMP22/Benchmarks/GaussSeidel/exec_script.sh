#!/bin/bash

iteraciones=(1)

matrix_sizes=(34)


for matrix_size in "${matrix_sizes[@]}"
do
    echo "-------------------------------"
    echo "|  Matrix size $matrix_size  |"
    echo "-------------------------------"





	    for iteracion in "${iteraciones[@]}"
	    do
		 echo "-------------------------------"
		 echo "| Iteracion $iteracion  |"
		 echo "-------------------------------"


		    for ((num_thread=4; num_thread>=4; num_thread--))
		    do

			 echo "-------------------------------"
			 echo "| N Threads $num_thread  |"
			 echo "-------------------------------"

			 BS=$(((matrix_size-2)/2))
			 #./gs_taskloop $matrix_size
			 #./gs_openmp $matrix_size
			 ./gs_seq $matrix_size 
			 ./gs_task $matrix_size $BS $num_thread
			 ./gs_STE $matrix_size $BS $num_thread


           	    done

           done
done 



