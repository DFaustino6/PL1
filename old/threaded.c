#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
#include <ctype.h>
#include <string.h> 
#include <windows.h>
#include <pthread.h>
#define N_THREADS 3
#define ullong unsigned long long
#define llong long long

const char* result[] = {"Quadrado mágico\n","Quadrado imperfeito\n","Não é quadrado mágico\n"};

int size;
int *cols_sum;
char *f;
//int n_per_thread;
int start_position=0;
int r = 0;
int dlr_sum;
int drl_sum;
int row_sum;
int row_temp = 0; 

int lock[] = {0,1,1};
int n_per_thread[N_THREADS];
//------------------------------
// Create a dinamically allocated array with capacity `n`
int *ints_new(int n)
{
  //  return (int *) calloc(n, sizeof (int));
  return (int *) malloc (n * sizeof(int));
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

int check_magic_square(int *data,int order){
    
    for (int i = 0; i < n_per_thread[order]; i++){

        int row = (int)(((order*n_per_thread[0])+i)/size); 
        int col = (int)(((order*n_per_thread[0])+i)%size); 
        
        //printf("%d %d %d\n",row,col,data[i]);
        cols_sum[col] += data[i];

        row_temp += data[i];
        printf("th:%d row: %d col: %d value: %d dlr: %d drl: %d r: %d rt: %d\n",order,row,col,data[i],dlr_sum,drl_sum,row_sum,row_temp);
        if(row == col) dlr_sum += data[i];
        if(col == ( size - 1 ) - row ) drl_sum += data[i];
        if(row == 0) row_sum += data[i];
        if(col == size - 1){
            if( row_temp == row_sum) row_temp = 0;
            else{
                //printf("th:%d value: %d dlr: %d drl: %d r: %d rt: %d col: %d row: %d\n",order,data[i],dlr_sum,drl_sum,row_sum,row_temp,col,row);
                return 2;
            }
        } 
    }
    free(data);
    if(order == N_THREADS-1 && (dlr_sum != row_sum || drl_sum != row_sum)) return 1;
    return 0;
}

void *read_file(){
    
    while (lock[pthread_self()-1]==1){
    }
    
    if(r == 0 ){
        FILE *fp = fopen(f,"r");
        fseek(fp,start_position,SEEK_SET);
        int n;
        int *data = ints_new(n_per_thread[pthread_self()-1]);

        for (int i = 0; i < n_per_thread[pthread_self()-1]; i++){
            fscanf(fp,"%d", &n);
            data[i]=n;
            //printf("%d %d\n",pthread_self(),n);
        }

        int *temp = ints_new(n_per_thread[pthread_self()-1]);
        memcpy(temp,data,n_per_thread[pthread_self()-1] * sizeof(int));

        r = check_magic_square(temp,pthread_self()-1);
        free(data);
        start_position = ftell(fp);
        if(pthread_self() < N_THREADS) lock[pthread_self()] = 0;
        fclose(fp);  
    }   
}

void magic_square( char *filename){
    f = filename;
    get_size(filename);

    for (int i = 0; i < N_THREADS-1; i++){
        n_per_thread[i] = (size/N_THREADS);
        n_per_thread[i]*= size;
    }
        
    n_per_thread[N_THREADS-1] = (size*size)-(n_per_thread[0] * (N_THREADS-1));

    pthread_t threads[N_THREADS];

    for (int i = 0; i < N_THREADS; i++)
        printf("%d\n",n_per_thread[i]);
   
    
    for (int i = 0; i < N_THREADS; i++)
        pthread_create(&threads[i],NULL,read_file,NULL);
        
    for (int i = 0; i < N_THREADS; i++)
        pthread_join(threads[i],NULL);

    printf("%s",result[r]);
    pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
    char *filename= "inputs/p3.txt";
    if (argc >= 2 )
        filename = argv[1];
    magic_square(filename);
    return 0;
}