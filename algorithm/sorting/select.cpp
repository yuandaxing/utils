#include <iostream>
#include <stdlib.h>

using namespace std;
int cmp(const void *a, const void *b)
{
    const int *a1 = (const int *)a;
    const int *b1 = (const int *)b;
    return *a1 - *b1;
}
void init(int a[], int n, int b[], int m)
{
     qsort(a, n, sizeof(int), cmp);
     for(int i = 0; i < m; i++){
             b[i] = a[i];
     }
     
}
bool computer(int a[], int n, int b[], int m)
{
     int j = n - 1, i = 0;
     
     
     //find the first least import digit we need to exchange
     for(i = m - 1; i >= 0; i--){
           if(b[i] >= a[j]){
                   j--;
           }
           else
               break;
     }
     if(i < 0)
          return false;
          
    b[i] = b[i] + 1;
     
     for( j = b[i] + 1, i = i + 1;  i < m && j < n; i++, j++) 
          b[i] = j;
          
     return true;
}
int main()
{
    int a[] = {1, 2, 3, 4, 5, 6, 7};
    int b[10];
    const int len = sizeof(a) / sizeof(a[0]);
    int select = 3;
    init(a, len, b, select);
    do{
       for(int i = 0; i < select; i++){
               cout<<b[i]<<" ";
       }
       cout<<endl;
    }while(computer(a, len, b, select));
    
    getchar();
    return 0;
}
