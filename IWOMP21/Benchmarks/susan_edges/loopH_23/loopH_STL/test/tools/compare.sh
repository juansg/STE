#rm -f tmp-ccc-diff
#diff ftmp_out ftmp_out-std >> tmp-ccc-diff
#diff output_large.edges.pgm output_large.edges.pgm-std >> tmp-ccc-diff

diff ftmp_out ftmp_out-std
diff output_large.edges.pgm output_large.edges.pgm-std
