#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
#include <ctype.h>
#include <string.h> 
#include <windows.h>
#include <omp.h>
#define N_THREADS 3
#define ullong unsigned long long
#define llong long long

const char* result[] = {"Quadrado magico\n","Quadrado imperfeito\n","Nao e quadrado magico\n","Nao e quadrado magico\n"};
int r = 0;
int size;
llong row_sum=0;
llong n_per_thread[N_THREADS];
llong total_drl;
llong total_dlr;
llong *total_cols;

//------------------------------
// Create a dinamically allocated array with capacity `n`
llong *ints_new(int n)
{
  //  return (int *) calloc(n, sizeof (int));
  return (llong *) calloc (n , sizeof(llong));
}
//-------------------------------

//obter o tamanho a ordem da matriz a partir do nome do ficheiro
void get_size(char *filename){
    char *f = filename;
    while(*f){
        if (isdigit(*f))  size = strtol(f,&f,10);
        else f++;   
    }
}

typedef struct{
    int th;
    llong *values;
    llong position;
    llong dlr_sum;
    llong drl_sum;
    llong *cols_sum;
}Magic_Square;

Magic_Square to_magic_square(int th,llong *src,llong position){
   Magic_Square result;
   result.values = ints_new(n_per_thread[th]);
   memcpy(result.values,src,n_per_thread[th] * sizeof(llong));
   result.th = th;
   result.position = position;
   result.cols_sum = ints_new(size);
   result.dlr_sum = 0;
   result.drl_sum = 0;
   return result;
} 

void check_magic_square(Magic_Square *arg){
    llong row_temp = 0;
    for(int i = 0; i < n_per_thread[arg->th] && r < 2 ;i++){

        int row = (int)((i+arg->position)/size); 
        int col = (int)((i+arg->position)%size); 
        
        arg->cols_sum[col] += arg->values[i];
        row_temp += arg->values[i];

        if(row == col) arg->dlr_sum += arg->values[i];
        if(col == ( size - 1 ) - row ) arg->drl_sum += arg->values[i];
        if(col == size - 1){
            if( row_sum == row_temp) row_temp = 0;
            else r = 2;
        } 
    }
    free(arg->values);
}

void read_file(char *file){

    FILE *fp = fopen(file,"r");
    Magic_Square ths[N_THREADS];
    llong n;
    int th=0;
    llong *data = ints_new(n_per_thread[N_THREADS-1]);
    llong start=0;
    for(int i = 0; i <  size*size; i++){
        fscanf(fp,"%d", &n);
        data [i-start] = n;
        row_sum += data[i-start] * (i < size); 

        if(i == (n_per_thread[th]-1)+start){
            ths[th] = to_magic_square(th,data,start);
            start += n_per_thread[th++];
        }    
    }

    fclose(fp);

    #pragma omp parallel 
    {
        int tid =omp_get_thread_num();
        if(r<2)
            check_magic_square(&ths[tid]);
    }
    
    total_cols = ints_new(size);
    for ( int i = 0; i < N_THREADS; i++)
    {
       total_dlr += ths[i].dlr_sum;
       total_drl += ths[i].drl_sum;
       for (int j = 0; j < size; j++)
           total_cols[j] += ths[i].cols_sum[j];
    }
    
    if (r < 2)
        for (int i = 0; i < size; ){
            r = (total_cols[i] != row_sum)*2;
            i = size*(r==2)+i+1;
        }

    r = 1*(total_dlr != row_sum || total_drl != row_sum) + 2*(r==2);

}

void magic_square( char *filename){
    get_size(filename);
    omp_set_num_threads(N_THREADS);
    
    for (int i = 0; i < N_THREADS-1; i++){
        n_per_thread[i] = (size/N_THREADS);
        n_per_thread[i]*= size;
    }
        
    n_per_thread[N_THREADS-1] = (size*size)-(n_per_thread[0] * (N_THREADS-1));
    read_file(filename);
    printf("%s",result[r]); 
}

int main(int argc, char *argv[])
{
    char *filename= "../inputs/p3.txt";
    if (argc >= 2 )
        filename = argv[1];
    magic_square(filename);
    return 0;
}
