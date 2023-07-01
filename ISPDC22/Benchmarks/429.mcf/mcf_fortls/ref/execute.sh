strip_size=60

if test -n "$1"; then
  strip_size=$1
fi

echo "Strip size: " $strip_size
echo $strip_size > _finfo_dataset

nthreads=4

if test -n "$2"; then
   nthreads=$2 
fi

echo "Nthreads: " $nthreads
echo $nthreads >> _finfo_dataset

./mcf inp.in > inp.out
