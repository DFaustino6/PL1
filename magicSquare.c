#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

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
//-----------------------------------------our_ints.c------------------

int read_numbers(FILE *fp,int *m){
    int result=0;
    int n;
    while ( fscanf(fp,"%d", &n)!=EOF)
        m[result++] = n;  
    return result;
}

void to_magic_square(int l,int **ms,int *m,int n){

    for (int i = 0; i < n; i++)
    {
        int row = (int)(i/l); 
        int col = (int)(i%l); 
        ms[row][col]=m[i];  
    }
    
}   


int col_sum(int n,int **m,int c){
    int result = 0;
    for (int i = 0; i < n; i++)
        result+=m[i][c];
}

int row_sum(int n, int *a){
    int result = 0;
    for (int i = 0; i < n; i++)
        result+=a[i];
}

int DLR_sum(int n,int **m){
    int result = 0;
    for (int i = 0; i < n; i++)
        result+=m[i][i];
}

int DRL_sum(int n,int **m){
    int result = 0;
    for (int i = 0; i < n; i++)
        result+=m[i][n-(i+1)];   
}

bool check_magic_square(int n,int **m){
    bool b=false;
    int col_value = 0;
    int row_value = 0;

    for (int i = 0; i < n; i++)
    {
        int 
        if()
        
    }
    
    return false;
}

void magic_square(){
    FILE *fp = fopen("ms.txt","r"); 
    int m[1000];
    int n=0;
    n = read_numbers(fp,m);
    int l = sqrt(n);

    int **ms = malloc(l*sizeof(int));

    for (int i = 0; i < l; i++)
        ms[i] = malloc(l*sizeof(int));
    
    to_magic_square(l,ms,m,n);
    ints_println_basic(m,n);
    
    fclose(fp);
    
}

int main(int argc, char const *argv[])
{
    magic_square();
    return 0;
}
