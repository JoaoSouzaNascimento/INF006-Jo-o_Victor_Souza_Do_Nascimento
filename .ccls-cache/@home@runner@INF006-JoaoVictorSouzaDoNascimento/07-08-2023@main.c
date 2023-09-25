//

#include <stdio.h>
#define tam 5
int main(void) {

  int v[tam]={5,4,3,2,1},j=0,i=0,aux;
  
  for(i=0;i<tam;i++){
    for(j=tam-j;j-1>=0;j--){
      if(v[j]<v[j-1]){
        v[j]=v[j-1]+v[j];
        v[j-1]=v[j]-v[j-1];
        v[j]=v[j]-v[j-1];
      }
    }
  }
  
  printf("Hello World\n");
  return 0;
}