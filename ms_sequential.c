#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
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
  //  return (int *) calloc(n, sizeof (int));
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


//-----------------------------------------------------------

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
        result += m[i][c];
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
        if(col_value != col_sum(n,m,i))
            return false;
    return true;
}

char* check_magic_square(int n,int **m){
    int col_value = col_sum(n,m,0);
    int row_value = row_sum(n,m[0]);
    int dlr_value = DLR_sum(n,m);
    int drl_value = DRL_sum(n,m);

    if (col_value != row_value) return "Not a MagicSquare\n";
    else if ( !check_cols(n,m,col_value) || !check_rows(n,m,row_value) ) return "Not a MagicSquare\n";
    else if ( dlr_value != col_value || drl_value != col_value) return "Defective MagicSquare\n";
    else return "MagicSquare\n";
}

void magic_square(const char *filename){
    clock_t start, end;
    start = clock();
    FILE *fp = fopen(filename,"r"); 
    int *a = ints_new(max_size);
    int n = read_numbers(fp,a);
    int l = sqrt(n);

    int **m = ints2_new(l,l);
    
    to_magic_square(l,m,a,n);
    printf("%s",check_magic_square(l,m));
    
    fclose(fp);
    end = clock();

    FILE *f = fopen("results.txt","w");
    double total_time = difftime(end,start)/CLOCKS_PER_SEC;
    printf("%lf\n",total_time);
    //fprintf(f,"%lf",total_time);
    fclose(f);
}

int main(int argc, char const *argv[])
{
    const char *filename= "input3000x3000.txt";
    if (argc >= 2 )
    {
        filename = argv[1];
    }
    
    magic_square(filename);
    return 0;
}
