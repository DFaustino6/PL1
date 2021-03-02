#include <stdio.h>
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

void to_magic_square(int **ms,int *m,int n){
    int result = sqrt(n);

    for (int i = 0; i < n; i++)
    {
        int row = (int)(i/result); 
        int col = (int)(i%result); 
        printf("%d %d %d\n",row,col,m[4]);
        ms[row][col]=m[i];  
    }
    
}   


void test_magic_square(){
    FILE *fp = fopen("ms.txt","r"); 
    int m[1000];
    int ms[100][100];
    int n=0;
    n = read_numbers(fp,m);
    to_magic_square(ms,m,n);
    ints_println_basic(m,n);
    
    fclose(fp);
    
}

int main(int argc, char const *argv[])
{
    test_magic_square();
    return 0;
}
