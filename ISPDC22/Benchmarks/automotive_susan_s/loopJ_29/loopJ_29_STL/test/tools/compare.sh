#rm -f tmp-ccc-diff
#diff ftmp_out ftmp_out-std >> tmp-ccc-diff
#diff output_large.smoothing.pgm output_large.smoothing.pgm-std >> tmp-ccc-diff

diff ftmp_out ftmp_out-std
diff output_large.smoothing.pgm output_large.smoothing.pgm-std
