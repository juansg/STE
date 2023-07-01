#!/bin/bash

#iteraciones=(1 2 3 4 5)
#strips=(18700 20100 20000)

iteraciones=(1 2)


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
		
			 ./execute.sh  $num_thread

		        #OMP_NUM_THREADS=$num_thread ./pcm-tsx.x  -e RTM_RETIRED.COMMIT  -e  RTM_RETIRED.ABORTED -e RTM_RETIRED.ABORTED_MEMTYPE -e RTM_RETIRED.ABORTED_UNFRIENDLY  -- ./execute.sh 1 $strip_size

			tail -6 inp.out
             echo ""
	    done

	echo ""
done


