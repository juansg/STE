#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <omp.h>

#define MAX_ITER 2000

// Maximum value of the matrix element
#define MAX 100
#define TOL 0.001




// Generate a random float number with the maximum value of max
float rand_float(const int max) {
	return ((float)rand() / (float)(RAND_MAX)) * max;
}




// Calculates how many rows are given, as maximum, to each thread
int get_max_rows(const int num_threads, const int n) {
	return (int)(ceil((n-2) / num_threads) + 2);
}




// Allocate 2D matrix with random floats
void alloc_matrix(float ***mat, const int n, const int m) {

	*mat = (float **) malloc(n * sizeof(float*));

       for (int i = 0; i < n ; i++) {
		(*mat)[i] = malloc(m * sizeof(float));

        	for (int j = 0; j <m; j++) {
		  (*mat)[i][j] = rand_float(MAX);
	       } 

	}
	
}

void print_matrix(float ***mat, const int n, const int m){

       for (int i = 1; i < n-1; i++) {
	
        	for (int j = 1; j < m-1; j++) {
			printf("%.2f ", (*mat)[i][j]);
	       } 
		putchar('\n');
	}


}



// Write the time results into a CSV file
void write_to_file(int n, char *schedule_type, float total_time, float exec_time) {

	FILE *f;
	char* file_name = "results.csv";

	if (access(file_name, F_OK) == -1) {
 		f = fopen(file_name, "a");
		fprintf(f, "Matrix size;Schedule type;Total time;Operations time;\n");
	}
	else {
		f = fopen(file_name, "a");
	}

	fprintf(f, "%d;%s;%f;%f;\n", n, schedule_type, total_time, exec_time);
	fclose(f);
}




// Solves the matrix splitting the rows into different threads
void solver(float ***mat, const int n, const int m, const int num_ths, const int max_cells_per_th, const int BS) {

	float diff;

	int done = 0;
	int cnt_iter = 0;
	//const int mat_dim = n * n;


       #pragma omp parallel num_threads(num_ths) // reduction(task,+:diff)
       {
       #pragma omp single
       {
	while (!done && (cnt_iter < MAX_ITER)) {


		diff = 0;

              #pragma omp taskgroup task_reduction (max:diff)
		{
		// Neither the first row nor the last row are solved
		// (that's why both 'i' and 'j' start at 1 and go up to '[nm]-1')
		for (int i = 1; i < n-BS; i+=BS) {
			for (int j = 1; j < m-BS; j+=BS) {


                            #pragma omp task default(none) firstprivate(BS,m,n,i,j,cnt_iter,mat) in_reduction(max:diff) depend(inout: (*mat)[i:BS][j:BS]) depend(in:(*mat)[i+BS:1][j:BS], (*mat)[i-1:1][j:BS] , (*mat)[i:BS][j-1:1], (*mat)[i:BS][j+BS:1]) 
                            {
                            for (int ii=i; ii<i+BS; ++ii){
					for (int jj=j; jj<j+BS; ++jj){

						  //const int pos = (ii * m) + jj;
						  const float temp = (*mat)[ii][jj];

				          
						  (*mat)[ii][jj] = 
							0.25 * (
								//(*mat)[ii][jj]
								(*mat)[ii][jj-1]
								+ (*mat)[ii-1][jj]
								+ (*mat)[ii][jj+1]
								+ (*mat)[ii+1][jj]
							);
						   //#pragma omp critical
						   diff=fmaxf(fabs((*mat)[ii][jj] - temp),diff);
					 }
                              }
                              } 
			}
		}

              //#pragma omp taskwait
		}
              //printf("diff %f \n", diff);
		//getchar();
		if (diff < TOL) {
			done = 1;
		}
		cnt_iter ++;
	}
       }
       }

	printf("Solver converged after %d iterations\n", cnt_iter);
}




int main(int argc, char *argv[]) {

	if (argc < 3) {
		printf("Call this program with two parameters: matrix_size communication \n");
		printf("\t matrix_size: Add 2 to a power of 2 (e.g. : 18, 1026)\n");
		exit(1);
	}

	const int n = atoi(argv[1]);
       const int BS= atoi(argv[2]);
       const int nthreads = atoi(argv[3]);

	// Start recording the time
	const double i_total_t = omp_get_wtime();

	float **mat;
	alloc_matrix(&mat, n, n);
       //(&mat, n, n);
	// Calculate how many cells as maximum per thread
	const int max_threads = 4;//omp_get_max_threads();
	const int max_rows = get_max_rows(max_threads, n);
	const int max_cells = max_rows * (n-2);


	// Initial operation time
	const double i_exec_t = omp_get_wtime();

	// Parallelized solver
	solver(&mat, n, n, nthreads, max_cells, BS);

	// Final operation time
	const double f_exec_t = omp_get_wtime();

       //print_matrix(&mat, n, n);
	free(mat);

	// Finish recording the time
	const double f_total_t = omp_get_wtime();

	const double total_time = f_total_t - i_total_t;
	const double exec_time = f_exec_t - i_exec_t;
	printf("Total time: %lf\n", total_time);
	printf("TASKS Operations time: %lf\n\n", exec_time);

	//write_to_file(n, "static", total_time, exec_time);
}
