./pcm-tsx-2020.x  -e RTM_RETIRED.COMMIT  -e  RTM_RETIRED.ABORTED -e RTM_RETIRED.ABORTED_MISC1 -- ./execute.sh > aborts_nm.txt

./pcm-tsx-2020.x   -e  RTM_RETIRED.ABORTED -e RTM_RETIRED.ABORTED_MISC3 -e RTM_RETIRED.ABORTED_MISC5 -- ./execute.sh >> aborts_nm.txt

./pcm-tsx-2020.x   -e  RTM_RETIRED.ABORTED_MISC1  -e TX_MEM.ABORT_CONFLICT -e TX_MEM.ABORT_CAPACITY_WRITE -- ./execute.sh >> aborts_nm.txt
