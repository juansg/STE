#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <omp.h>
#include <immintrin.h>

#define MAX_ITER  2000

// Maximum value of the matrix element
#define MAX 100
#define TOL 0.001




// Generate a random float number with the maximum value of max
float rand_float(const int max)
{
    return ((float)rand() / (float)(RAND_MAX)) * max;
}




// Calculates how many rows are given, as maximum, to each thread
int get_max_rows(const int num_threads, const int n)
{
    return (int)(ceil((n-2) / num_threads) + 2);
}




// Allocate 2D matrix with random floats
void alloc_matrix(float ***mat, const int n, const int m)
{

    *mat = (float **) malloc(n * sizeof(float*));

    for (int i = 0; i < n ; i++)
    {
        (*mat)[i] = malloc(m * sizeof(float));

        for (int j = 0; j <m; j++)
        {
            (*mat)[i][j] = rand_float(MAX);
        }

    }

}

void print_matrix(float ***mat, const int n, const int m)
{

    for (int i = 0; i < n; i++)
    {

        for (int j = 0; j < m; j++)
        {
            printf("%.2f ", (*mat)[i][j]);
        }
        putchar('\n');
    }


}



// Write the time results into a CSV file
void write_to_file(int n, char *schedule_type, float total_time, float exec_time)
{

    FILE *f;
    char* file_name = "results.csv";

    if (access(file_name, F_OK) == -1)
    {
        f = fopen(file_name, "a");
        fprintf(f, "Matrix size;Schedule type;Total time;Operations time;\n");
    }
    else
    {
        f = fopen(file_name, "a");
    }

    fprintf(f, "%d;%s;%f;%f;\n", n, schedule_type, total_time, exec_time);
    fclose(f);
}




// Solves the matrix splitting the rows into different threads
void solver(float ***mat, const int n, const int m, const int num_ths, const int max_cells_per_th, const int BS, float ***un)
{

    float diff[MAX_ITER];

    int done = 0;
    int cnt_iter = 0;
    int next_iter=cnt_iter;
    int i,j;
    //const int mat_dim = n * n;


    #pragma omp parallel num_threads(num_ths) //reduction(task, +:diff)
    {
        #pragma omp master
        {
            while (!done && (cnt_iter < MAX_ITER))
            {



                diff[cnt_iter] = 0;
                //printf("while: diff %f cnt %d next %d done %d \n", diff[cnt_iter],cnt_iter,next_iter,done);
                //#pragma omp taskgroup task_reduction (+:diff)
                //{
                // Neither the first row nor the last row are solved
                // (that's why both 'i' and 'j' start at 1 and go up to '[nm]-1')

		//#pragma omp task depend(out: diff[cnt_iter]) firstprivate(cnt_iter) default(shared) 
              //{

//printf("Task 1 inicio diff %f cnt %d next %d done %d \n", diff[cnt_iter],cnt_iter,next_iter,done);
                    for (i = 1; i < n-BS; i+=BS)
                    {
                        for (j = 1; j < m-BS; j+=BS)
                        {


                            #pragma omp task  default(none) firstprivate(BS,i,j,cnt_iter,mat,un) shared( next_iter,done,diff) depend(out: (*un)[i:BS][j:BS])  depend(in: (*mat)[i:BS][j:BS]) depend(in:(*mat)[i+BS:1][j:BS], (*mat)[i-1:1][j:BS] , (*mat)[i:BS][j-1:1], (*mat)[i:BS][j+BS:1])   depend(out: diff[cnt_iter])
                            {

                                //printf("Task inner diff %f cnt %d next %d done %d \n", diff[cnt_iter],cnt_iter,next_iter,done);

                                char spec;
                                unsigned status;
                                float diffL=0;
                                float temp;
                                int ii,jj;
                                //float matL[BS+2][BS+2];

Retry:

                                if (done) goto Exit;
/*
                                for (ii=i; ii<i+BS; ++ii)
                                {

                                        matL[ii-i+1][0]=(*mat)[ii][j-1];

                                }

                                for (jj=j; jj<j+BS; ++jj)
                                {

                                        matL[0][jj-j+1]=(*mat)[i-1][jj];

                                }
*/
/*
                                for (ii=i-1; ii<i+BS+1; ++ii)
                                   for (jj=j-1; jj<j+BS+1; ++jj)
				    {

                                      matL[ii-i+1][jj-j+1]=(*mat)[ii][jj];

                                }
                                
*/

                                if (cnt_iter!=next_iter)
                                {
                                    spec=1;
                                    status=_xbegin();
                                    if (status!=_XBEGIN_STARTED)
                                    {
                                        goto Retry;
                                    }
                                }
                                else {
                                    spec=0;
                                }


                                for (ii=i; ii<i+BS; ++ii)
                                {
                                    for (jj=j; jj<j+BS; ++jj)
                                    {

                                        //const int pos = (ii * m) + jj;
                                        temp = (*mat)[ii][jj];
						  
						  (*un)[ii][jj] = 
							0.25 * (
								//(*mat)[ii][jj]
								(*mat)[ii][jj-1]
								+ (*mat)[ii-1][jj]
								+ (*mat)[ii][jj+1]
								+ (*mat)[ii+1][jj]
							);
					  	  
						  /*
						  matL[ii-i+1][jj-j+1] = 
							0.25 * (
								//(*mat)[ii][jj]
								 matL[ii-i+1][jj-j]//+ (*mat)[ii][jj-1] 
								 + matL[ii-i][jj-j+1]//+ (*mat)[ii-1][jj]
								 +(*mat)[ii][jj+1]
								 +(*mat)[ii+1][jj]
							);
						   */
                                        //#pragma omp critical
					     //diff[cnt_iter]=fmaxf(fabs((*mat)[ii][jj] - temp),diff[cnt_iter]);		
                                        diffL = fmaxf(diffL,fabs((*un)[ii][jj] - temp));
					     //diffL = fmaxf(diffL,fabs(matL[ii-i+1][jj-j+1] - temp));
					     
					     //diff[cnt_iter]+=abs((*mat)[ii][jj] - temp);
                                    }
                                }


                                if (spec)
                                {
                                    //while (cnt_iter!=next_iter);
					 //;
					 if (cnt_iter!=next_iter) _xabort(0xff);
                                    _xend();

			               //printf("Comité  diff %f cnt %d next %d done %d \n", diffL,cnt_iter,next_iter,done);

                                }


                                
				    diff[cnt_iter]=fmaxf(diffL,diff[cnt_iter]);
				    /*
                                for (ii=i; ii<i+BS; ++ii)
                                {
                                    for (jj=j; jj<j+BS; ++jj)
                                    {

                                        //const int pos = (ii * m) + jj;
                                        (*mat)[ii][jj]=matL[ii-i+1][jj-j+1];

                                    }
                                }
				    */
Exit:; 
                                //next_iter++;

                            }
                        }
                    }

                   //#pragma omp taskwait

//printf("Task 1 fin diff %f cnt %d next %d done %d \n", diff[cnt_iter],cnt_iter,next_iter,done);
                //}
                //}

                //getchar()



                #pragma omp task  firstprivate(cnt_iter,mat,un,n,m) default(none) shared(diff,done,next_iter) depend(in: diff[cnt_iter])  depend(in:(*un)[1:n-2][j:n-2]) depend(out:(*mat)[1:n-2][j:n-2])
                {

                    //printf("Task 2 diff %f cnt %d next %d done %d \n", diff[cnt_iter],cnt_iter,next_iter,done);

                    char spec;
                    unsigned status;
		      char flag_w=0;
		      int doneL;
                    int ii,jj;
Retry:

                    if (done) goto Exit;

                    if (cnt_iter!=next_iter)
                    {
                        spec=1;
                        status=_xbegin();
                        if (status!=_XBEGIN_STARTED)
                        {
                            goto Retry;
                        }
                    }
                    else
                    {
                        spec=0;
                    }

                                for (ii=1; ii<n-1; ++ii)
                                {
                                    for (jj=1; jj<m-1; ++jj)
                                    {

		        	         (*mat)[ii][jj]=(*un)[ii][jj];

                                     }
                                 }



                    if (diff[cnt_iter] < TOL){
                        doneL = 1;
			   flag_w=1;
		      }

                    if (spec)
                    {
				//while (cnt_iter!=next_iter);
				//;
		      		if (cnt_iter!=next_iter) _xabort(0xff);
                               _xend();

                    }

		      if (flag_w) done=doneL;
                    if (!done) next_iter++;
		      //done=doneL;
Exit:	;		

                    //printf("Task 2 fin diff %f cnt %d next %d done %d \n", diff[cnt_iter],cnt_iter,next_iter,done);
                }


                cnt_iter++;
            }

            //printf(" single diff %f cnt %d next %d done %d \n", diff[next_iter],cnt_iter,next_iter,done);
        }
        //printf(" parallel diff %f cnt %d next %d done %d \n", diff[next_iter],cnt_iter,next_iter,done);

    }
    //printf(" final diff %f cnt %d next %d done %d \n", diff[next_iter],cnt_iter,next_iter,done);
    printf("Solver converged after %d iterations\n", next_iter+1);
}




int main(int argc, char *argv[])
{

    if (argc < 2)
    {
        printf("Call this program with two parameters: matrix_size communication \n");
        printf("\t matrix_size: Add 2 to a power of 2 (e.g. : 18, 1026)\n");
        exit(1);
    }

    const int n = atoi(argv[1]);
    const int BS= atoi(argv[2]);
    const int nthreads =atoi(argv[3]);

    // Start recording the time
    const double i_total_t = omp_get_wtime();

    float **mat, **un;
    alloc_matrix(&mat, n, n);
    alloc_matrix(&un, n, n);
    //print_matrix(&mat, n, n);
    // Calculate how many cells as maximum per thread
    const int max_threads = 4;//omp_get_max_threads();
    const int max_rows = get_max_rows(max_threads, n);
    const int max_cells = max_rows * (n-2);


    // Initial operation time
    const double i_exec_t = omp_get_wtime();

    // Parallelized solver
    solver(&mat, n, n, nthreads, max_cells, BS, &un);

    // Final operation time
    const double f_exec_t = omp_get_wtime();

    //print_matrix(&mat, n, n);
    free(mat);

    // Finish recording the time
    const double f_total_t = omp_get_wtime();

    const double total_time = f_total_t - i_total_t;
    const double exec_time = f_exec_t - i_exec_t;
    printf("Total time: %lf\n", total_time);
    printf("STE Operations time: %lf\n\n", exec_time);

    //write_to_file(n, "static", total_time, exec_time);
}

