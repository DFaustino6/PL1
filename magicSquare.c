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
    return result;
}

int row_sum(int n, int *a){
    int result = 0;
    for (int i = 0; i < n; i++)
        result+=a[i];
    return result;
}

int DLR_sum(int n,int **m){
    int result = 0;
    for (int i = 0; i < n; i++)
        result+=m[i][i];
    return result;
}

int DRL_sum(int n,int **m){
    int result = 0;
    for (int i = 0; i < n; i++)
        result+=m[i][n-(i+1)];
    return result;   
}

bool check_rows(int n,int **m,int row_value){
    for (int i = 1; i < n; i++)
        if(row_value != row_sum(n,m[i]))
            return false;
    return true;
}

bool check_cols(int n,int **m,int col_value){
    for (int i = 1; i < n; i++)
        if(col_value != col_sum(n,m,0))
            return false;
    return true;
}

char* check_magic_square(int n,int **m){
    int col_value = col_sum(n,m,0);
    int row_value = row_sum(n,m[0]);
    int dlr_value = DLR_sum(n,m);
    int drl_value = DRL_sum(n,m);

    //printf("col: %d, row %d, dlr %d, drl %d\n",col_value,row_value,dlr_value,drl_value);
    //printf("%d %d %d\n",check_cols(n,m,col_value),check_rows(n,m,row_value));

    if((col_value == row_value && row_value == dlr_value && dlr_value == drl_value) && check_cols(n,m,col_value)==1 && check_rows(n,m,row_value)==1)
        return "Magic Square";
    else if(!check_cols(n,m,col_value) && !check_rows(n,m,row_value) && dlr_value != drl_value)
        return "Not a Magic Square";
    else return "Defective Magic Square";


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

    printf("%s",check_magic_square(l,ms));
    
    fclose(fp);
    
}

int main(int argc, char const *argv[])
{
    magic_square();
    return 0;
}
