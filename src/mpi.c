#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
#include <ctype.h>
#include<string.h> 

#include <mpi.h>
#define N_THREADS 3
#define ullong unsigned long long
#define llong long long

const char* result[] = {"Quadrado magico\n","Quadrado imperfeito\n","Nao e quadrado magico\n","Nao e quadrado magico\n"};
int r = 0;
int size;
int *cols_sum;
int row_sum=0;
int n_per_thread[N_THREADS];
int dlr_sum = 0;
int drl_sum = 0;

//------------------------------
// Create a dinamically allocated array with capacity `n`
int *ints_new(int n)
{
  //  return (int *) calloc(n, sizeof (int));
  return (int *) calloc (n , sizeof(int));
}
//-------------------------------

//obter o tamanho a ordem da matriz a partir do nome do ficheiro
void get_size(char *filename){
    char *f = filename;
    while(*f){
        if (isdigit(*f))  size = strtol(f,&f,10);
        else f++;   
    }
    //magic_const= size * ( size * size + 1 ) / 2; //calcular o valor da constante magica
    cols_sum = ints_new(size); //alocar memoria para a matriz que guarda a soma das colunas
}

typedef struct{
    int th;
    int *values;
    int position;
}Magic_Square;

Magic_Square to_magic_square(int th,int *src,int position){
   Magic_Square result;
   result.values = ints_new(n_per_thread[th]);
   memcpy(result.values,src,n_per_thread[th] * sizeof(int));
   result.th = th;
   result.position = position;
   return result;
} 

void check_magic_square(void *arg){
    Magic_Square *ms = (Magic_Square *)arg;
    int row_temp = 0;

    for(int i = 0; i < n_per_thread[ms->th] && r < 2 ;i++){

        int row = (int)((i+ms->position)/size); 
        int col = (int)((i+ms->position)%size); 
        
        cols_sum[col] += ms->values[i];
        row_temp += ms->values[i];

        if(row == col) dlr_sum += ms->values[i];
        if(col == ( size - 1 ) - row ) drl_sum += ms->values[i];
        if(row == 0) row_sum += ms->values[i];
        if(col == size - 1){
            if( row_sum == row_temp) row_temp = 0;
            else { r = 2;}
        } 
    }
   
}

int *n_per_thread(){

}

void read_file_master(char *file){

    FILE *fp = fopen(file,"r");
    Magic_Square ths[N_THREADS];
    int n;
    int th=0;
    int *data = ints_new(n_per_thread[N_THREADS-1]);
    int start=0;
    for(int i = 0; i <  size*size && r < 2 ;i++){
        fscanf(fp,"%d", &n);
        data [i-start] = n;
      
        if(i == (n_per_thread[th]-1)+start){
            ths[th] = to_magic_square(th,data,start);
            
            start += n_per_thread[th++];
        }    
    }

    fclose(fp);  

    if (r < 2)
        for (int i = 0; i < size; ){
            r = (cols_sum[i] != row_sum)*2;
            i = size*(r==2)+i+1;
        }

    r = 1*(dlr_sum != row_sum || drl_sum != row_sum) + 2*(r==2);
}

void magic_square( char *filename){
    get_size(filename);
    MPI_Init(NULL,NULL);

    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    
    read_file(filename,world_size);
    
    MPI_Finalize();

    //
    //printf("%s",result[r]); 


  
}

int main(int argc, char *argv[])
{
    char *filename= "inputs/p3.txt";
    if (argc >= 2 )
        filename = argv[1];
    magic_square(filename);
    return 0;
}
