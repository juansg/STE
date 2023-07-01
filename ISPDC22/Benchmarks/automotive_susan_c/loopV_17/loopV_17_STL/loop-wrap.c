#include <stdio.h>
#include <sys/time.h>

void main1(int argc, char* argv[], const long strip_size, const int nthreads);

int main(int argc, char* argv[])
{ 
  struct timeval start_time, end_time;

  FILE* loop_wrap=NULL;
  long loop_wrap1, loop_wrap2, strip_size;
  int nthreads;

  gettimeofday(&start_time, NULL);
  
  if ((loop_wrap=fopen("_finfo_dataset","rt"))==NULL)
  {
    fprintf(stderr,"\nError: Can't find dataset!\n");
    return 1;
  }

  fscanf(loop_wrap, "%ld %ld %d", &loop_wrap2, &strip_size, &nthreads);
  fclose(loop_wrap);

  ///*
  #pragma omp parallel num_threads(nthreads)
  {
  #pragma omp single
  { 
  //*/ 		  
  for (loop_wrap1=0; loop_wrap1<loop_wrap2; loop_wrap1++)
  {
    main1(argc, argv, strip_size, nthreads);
  }
  ///*
  }
  } 
  //*/
  gettimeofday(&end_time, NULL);
  double run_time = ((end_time.tv_sec  - start_time.tv_sec) * 1000000u + end_time.tv_usec - start_time.tv_usec) / 1.e6;
  printf("Timer %lf\n",run_time);

  return 0;
}
