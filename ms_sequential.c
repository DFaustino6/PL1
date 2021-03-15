#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
const int max_size=400041001;

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
typedef struct{
    int size;
    int **m;
    int col_value;
    int row_value;
    int dlr_value;
    int drl_value;
}Magic_Square;

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

Magic_Square ms(int *a, int size){
    Magic_Square result;
    result.size = sqrt(size);
    result.m = ints2_new(result.size,result.size);
    to_magic_square(result.size,result.m,a,size);
    result.col_value=col_sum(result.size,result.m,0);
    result.row_value=row_sum(result.size,result.m[0]);
    result.dlr_value=DLR_sum(result.size,result.m);
    result.drl_value=DRL_sum(result.size,result.m);
    return result;
}

int read_numbers(FILE *fp,int *m){
    int result=0;
    int n;
    while ( fscanf(fp,"%d", &n)!=EOF)
        m[result++] = n;  
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

char* check_magic_square(Magic_Square ms){
    //printf("%d %d\n",ms.col_value,ms.row_value);
    if (ms.col_value != ms.row_value) return "Não é quadrado mágico";
    else if ( !check_cols(ms.size,ms.m,ms.col_value) || !check_rows(ms.size,ms.m,ms.row_value) ) return "Não é quadrado mágico";
    else if ( ms.dlr_value != ms.col_value || ms.drl_value != ms.col_value) return "Quadrado mágico imperfeito";
    else return "Quadrado mágico";
}

void magic_square(const char *filename){
    clock_t start, end;
    start = clock();
    FILE *fp = fopen(filename,"r"); 
    int *a = ints_new(max_size);
    
    int n = read_numbers(fp,a);
    Magic_Square m_square = ms(a,n);
    check_magic_square(m_square);
    //matrix_write(m_square.m,m_square.size);
    fclose(fp);
    free(a);
    free(m_square.m);
    end = clock();
    double total_time = difftime(end,start)/CLOCKS_PER_SEC;
    printf("%lf\n",total_time);
}

int main(int argc, char const *argv[])
{
    const char *filename= "inputs/p501.txt";
    if (argc >= 2 )
        filename = argv[1];
    magic_square(filename);
    return 0;
}
