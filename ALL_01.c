// kompilowac z opcjami -lrt -lm, tj. np. gcc ALL_01.c -lrt -lm
#include <time.h>
#include <stdio.h>
#include <math.h>

#define MLDD 10000000000.0 //10**10

double procedura1(long int n){
 float x=0;
 long int i,j,k;

 for(i=n;i>=1;i--) {
  if((i % 2) == 1) {
    for(j=1;j<i+1;j++) ;
    for(k=i+1;k<n+1;k++) x=x+1;
    }
 }
 return x;
}

int main(){
  struct timespec tp0, tp1;
  double Tn,Fn,x;
  long int n;

for(n=10;n<10011;n=n+100){

clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&tp0);

// przykladowe obliczenia
    x=procedura1(n);

clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&tp1);

// zgadywana funkcja czasu
//     Fn=5*n ; // np. funkcja liniowa
//     Fn=2000000*n;
//     Fn=n*n*n;
//     Fn=n*log(n);
//     Fn=n*n*sqrt(n);
//     Fn=n*n*log(n);
//     Fn=n*n;
   Fn=n*n/450000;

  Tn=(tp1.tv_sec+tp1.tv_nsec/MLDD)-(tp0.tv_sec+tp0.tv_nsec/MLDD);
  printf("n: %5ld \tczas: %3.5lf \twspolczynnik: %3.5lf\n",n,Tn, Fn/Tn);
}

return 1;
}
