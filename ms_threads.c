#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <pthread.h>
#include <string.h>

const int max_size=100000000;

//-------------Prof. Pedro Guerreiro-----------------------
void ints_println_basic(const int *a, int n)
{
  if (n > 0)
  {
    printf("%d", a[0]);
    for (int i = 1; i < n; i++)  // i = 1
      printf(" %d", a[i]);
  }
  printf("\n");
}

int *ints_new(int n)
{
  //  return (int *) malloc(n, sizeof (int));
  return (int *) malloc (n * sizeof(int));
}

int **ints2_new(int rows, int cols)
{
  int **result = (int **) malloc(rows * sizeof(int *));
  int *p  = ints_new(rows * cols);
  for (int i = 0; i < rows; i++)
    result[i] = p + i * cols;
  return result;
} 

void matrix_write(int **m,int n){
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%d ",m[i][j]);
        }
        printf("\n");
    }
    
}
//-----------------------------------------------------------

typedef struct
{
    int size;
    int **m;
    int magic_const;
}Magic_Square;

Magic_Square ms(int **m, int size){

    Magic_Square result;
    result.size = size;
    result.magic_const = ( size * ( size * size + 1 ) ) / 2;
    result.m = ints2_new(size,size);
    memcpy (result.m, m, size*size*sizeof(int) );
    return result;
}

int read_numbers(FILE *fp,int *m){
    int result=0;
    int n;
    while ( fscanf(fp,"%d", &n)!=EOF)
        m[result++] = n;  
    return result;
}

void to_magic_square(int l,int **m,int *a,int n){

    for (int i = 0; i < n; i++)
    {
        int row = (int)(i/l); 
        int col = (int)(i%l); 
        m[row][col]=a[i];  
    }
}   


void magic_square(const char *filename){
    FILE *fp = fopen(filename,"r"); 
    int *a = ints_new(max_size);
    int n = read_numbers(fp,a);
    int l = sqrt(n);
    int **m = ints2_new(l,l);
    Magic_Square m_square = ms(m,l);
    printf("%d %d\n",m_square.size,m_square.magic_const);
    matrix_write(m_square.m,m_square.size);
    fclose(fp);
    
}

int main(int argc, char const *argv[])
{
    const char *filename= "ms.txt";
    magic_square(filename);
    return 0;
}
