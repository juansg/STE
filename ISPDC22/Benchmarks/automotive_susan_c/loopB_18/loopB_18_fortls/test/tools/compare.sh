#rm -f tmp-ccc-diff
#diff ftmp_out ftmp_out-std >> tmp-ccc-diff
#diff output_large.corners.pgm output_large.corners.pgm-std >> tmp-ccc-diff

diff ftmp_out ftmp_out-std
diff output_large.corners.pgm output_large.corners.pgm-std
