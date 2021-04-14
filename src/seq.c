#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
#include <ctype.h>
#include<string.h> 
#include <windows.h>


int size;
//int magic_const; 
int *cols_sum;
int row_sum=0;
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

char *check_magic_square(char *filename){
    FILE *fp = fopen(filename,"r"); 
    int n;
    int row_temp=0;
    int order=0;
    int dlr_sum = 0;
    int drl_sum = 0;
    while ( fscanf(fp,"%d", &n) != EOF){

        int row = (int)(order/size); 
        int col = (int)(order%size); 
      
        cols_sum[col] += n;
        row_temp += n;

        //printf("%d %d\n",row_sum,row_temp);
        if(row == col) dlr_sum += n;
        if(col == ( size - 1 ) - row ) drl_sum += n;
        if(row == 0) row_sum += n;
        if(col == size - 1){
            if( row_sum == row_temp) row_temp = 0;
            else return "Não é quadrado mágico\n";
        } 

        order++;
    }

    if(dlr_sum != row_sum || drl_sum != row_sum) return "Quadrado imperfeito\n";
    return "Quadrado mágico\n";
}

void magic_square( char *filename){
    get_size(filename);
    printf("%s",check_magic_square(filename));
}

int main(int argc, char *argv[])
{
    char *filename= "inputs/p3.txt";
    if (argc >= 2 )
        filename = argv[1];
    magic_square(filename);
    return 0;
}