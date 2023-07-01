#!/bin/bash

#iteraciones=(1 2 3 4 5)
#strips=(18700 20100 20000)

iteraciones=(1 2 3 4)
#strips=(75 76 77)
strips=(75)

for iteracion in "${iteraciones[@]}"
do
			 echo "-------------------------------"
			 echo "| Iteracion $iteracion  |"
			 echo "-------------------------------"


    #for ((strip_size=1; strip_size<=50; strip_size+=1))
    for strip_size in "${strips[@]}"
    do
		
		 echo "-------------------------------"
		 echo "| S SIZE $strip_size |"
		 echo "-------------------------------"


	    for ((num_thread=4; num_thread>=4; num_thread--))
	    do

		 echo "-------------------------------"
		 echo "| N Threads $num_thread  |"
		 echo "-------------------------------"
		
			 ./execute.sh  $strip_size $num_thread

		        #OMP_NUM_THREADS=$num_thread ./pcm-tsx.x  -e RTM_RETIRED.COMMIT  -e  RTM_RETIRED.ABORTED -e RTM_RETIRED.ABORTED_MEMTYPE -e RTM_RETIRED.ABORTED_UNFRIENDLY  -- ./execute.sh 1 $strip_size

			tail -7 inp.out
             echo ""
	    done

	echo ""
    done
	echo ""
done


