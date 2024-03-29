#! /bin/bash

if test -z "$1"; then
 echo "Usage: __run <dataset number> <number of runs (optional)>"
 exit
fi

#Searching for dataset info (command line and loop wrapper)
found="0"
exec 5< _ccc_info_datasets
 read <&5 ds_max ;
 while read <&5 line; 
 do 
  if [ "$line" == "=====" ]; then
   read <&5 ds ;
   read <&5 cmd ;
   read <&5 loop_wrap ;
   if [ $ds -eq $1 ] ; then
    found="1"
    break;
   fi
  fi
 done
exec 5>&-

if [ $found != "1" ] ; then
 echo "Can't find dataset info in the _ccc_info_datasets file ..."
 exit
fi

#if test -n "$2"; then
# loop_wrap=$2
#fi

echo "Found dataset: " $ds
echo "Command line:  " $cmd
echo "Loop wrap:     " $loop_wrap

#if test -n "$2"; then
# echo $2 > _finfo_dataset
#else
 echo $loop_wrap > _finfo_dataset
#fi

strip_size=1

if test -n "$2"; then
  strip_size=$2
fi

echo "Strip size: " $strip_size
echo $strip_size >> _finfo_dataset

nthreads=4

if test -n "$3"; then
   nthreads=$3 
fi

echo "Nthreads: " $nthreads
echo $nthreads >> _finfo_dataset

echo ""

if test -n "$CCC_RE"; then
 	echo "time $CCC_RE ./asusan_s $cmd" > tmp_bat
else
	echo "time ./asusan_s $cmd" > tmp_bat
fi

source tmp_bat
