#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
#include <ctype.h>
#include<string.h> 
#include <mpi.h>

#define ullong unsigned long long
#define llong long long

const char* result[] = {"Quadrado magico\n","Quadrado imperfeito\n","Nao e quadrado magico\n","Nao e quadrado magico\n"};
int r = 0;
int size;
int *cols_sum;

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

void check_magic_square(int n, int position, int *values){
    int row_temp = 0;
    int position;
    int n;
    int dlr_sum = 0;
    int drl_sum = 0;
    
    for(int i = 0; i < n && r < 2 ;i++){

        int row = (int)((i+position)/size); 
        int col = (int)((i+position)%size); 
        
        cols_sum[col] += values[i];
        row_temp += values[i];

        if(row == col) dlr_sum += values[i];
        if(col == ( size - 1 ) - row ) drl_sum += values[i];
        if(col == size - 1){
            if( mc == row_temp) row_temp = 0;
            else { r = 2;}
        } 
    }
   
}

void child(){
    int mc = 0;

    MPI_Recv(&position, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    MPI_Recv(&mc, 1, MPI_INT, 0, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

    MPI_Recv(&n, 1, MPI_INT, 0, 2, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

    int *values = ints_new(n);
    MPI_Recv(values, n, MPI_INT, 0, 3, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

    printf("position: %d n: %d mc: %d\n",position,n,mc);
    for (int i = 0; i < n; i++)
    {
        printf("%d\n",values[i]);
    }

    check_magic_square()
}


void read_file_parent(char *file,int np){
    int n_per_pro[np];
    for (int i = 0; i < np-1; i++){
        n_per_pro[i] = (size/np);
        n_per_pro[i]*= size;
    }
        
    n_per_pro[np-1] = (size*size)-(n_per_pro[0] * (np-1));

    //for (int i = 0; i < np; i++)
    //{
    //    printf("%d\n",n_per_pro[i]);
    //}
    
    FILE *fp = fopen(file,"r");
    int n;
    int p=1;
    int *data = ints_new(n_per_pro[np-1]);
    int start=0;
    int msg=0;
    int row_sum = 0;
    int dlr_sum = 0;
    int drl_sum = 0;

    for(int i = 0; i <  size*size && r < 2 ;i++){
        fscanf(fp,"%d", &n);
        data [i-start] = n;
        row_sum += data[i-start] * (i < size); 

        if(i == (n_per_pro[p]-1)+start){
            printf("%d\n",(n_per_pro[p]-1)+start);
            MPI_Send(&start, 1, MPI_INT, p, 0, MPI_COMM_WORLD);
            MPI_Send(&row_sum,1,MPI_INT, p, 1, MPI_COMM_WORLD);
            MPI_Send(&n_per_pro[p], 1, MPI_INT, p, 2, MPI_COMM_WORLD);
            MPI_Send(data, n_per_pro[p], MPI_INT, p, 3, MPI_COMM_WORLD);
            start += n_per_pro[p++];
            //int *data = ints_new(n_per_pro[p]);
        }    
    }

    //for (int i = 0; i < 3; i++)
    //{
    //    printf("%d\n",data[i]);
    //}
    
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

    if(world_rank == 0)
        read_file_master(filename,world_size);
    else check_magic_square();

    MPI_Finalize();

    //
    //printf("%s",result[r]); 


  
}

int main(int argc, char *argv[])
{
    char *filename= "../inputs/p3.txt";
    if (argc >= 2 )
        filename = argv[1];
    magic_square(filename);
    return 0;
}
