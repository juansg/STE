#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define MAX_ITER 2000
#define MAX 100 //maximum value of the matrix element
#define TOL 0.001

// Generate a random float number with the maximum value of max
float rand_float(int max){
  return ((float)rand()/(float)(RAND_MAX)) * max;
}


// Allocate 2D matrix
void allocate_init_2Dmatrix(float ***mat, int n, int m){
  int i, j;
  *mat = (float **) malloc(n * sizeof(float *));
  for(i = 0; i < n; i++) {
    (*mat)[i] = (float *)malloc(m * sizeof(float));
    for (j = 0; j < m; j++)
      (*mat)[i][j] = rand_float(MAX);
  }
} 

void print_matrix(float ***mat, const int n, const int m){

       for (int i = 0; i < n; i++) {
	
        	for (int j = 0; j < m; j++) {
			printf("%.2f ", (*mat)[i][j]);
	       } 
		putchar('\n');
	}


}


// solver
void solver(float ***mat, int n, int m){
  float diff = 0, temp;
  int done = 0, cnt_iter = 0, i, j;
  //const int mat_dim = n * n;

  while (!done && (cnt_iter < MAX_ITER)){
    diff = 0;
    for (i = 1; i < n - 1; i++)
      for (j = 1; j < m - 1; j++){
	temp = (*mat)[i][j];
	(*mat)[i][j] = 0.25 * ( (*mat)[i][j - 1] + (*mat)[i - 1][j] + (*mat)[i][j + 1] + (*mat)[i + 1][j]);
	diff = fmaxf(fabs((*mat)[i][j] - temp),diff);
      }
    //printf("diff %f\n", diff);
    if (diff< TOL)
      done = 1; 
    cnt_iter ++;
  }

  if (done)
    printf("Solver converged after %d iterations\n", cnt_iter);
  else
    printf("Solver not converged after %d iterations\n", cnt_iter);
  
}

int main(int argc, char *argv[]) {
  int n;
  float **a;


  if (argc < 2) {
    printf("Call this program with two parameters: matrix_size communication \n");
    printf("\t matrix_size: Add 2 to a power of 2 (e.g. : 18, 1026)\n");
    
    exit(1);
  }

  n = atoi(argv[1]);
  printf("Matrix size = %d \n", n);

  allocate_init_2Dmatrix(&a, n, n);
  //print_matrix(&a, n, n);
  // Initial operation time
  clock_t i_exec_t = clock();

  solver(&a, n, n);

  // Final operation time
  clock_t f_exec_t = clock();
  float exec_time = (float)(f_exec_t - i_exec_t) / CLOCKS_PER_SEC;
  printf("SEQ: Operations time: %f\n\n", exec_time);

  //print_matrix(&a, n, n);

  return 0;
}
