nthreads=4

if test -n "$1"; then
   nthreads=$1 
fi

echo "Nthreads: " $nthreads
echo $nthreads > _finfo_dataset

./mcf inp.in > inp.out
