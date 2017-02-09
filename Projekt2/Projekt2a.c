/********************************
*       TOMASZ ADAMCZYK         *
*       Nr albumu: 243217       *
*      Informatyka II ROK       *
*     Projekt2a.c - ALL.4.5     *
********************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define MLDD 1000000000.0

void Swap(int *a, int *b){
  int temp=*a;
  *a=*b;
  *b=temp;
}

void BubbleSort(int *A, int n){
  int i;
  if (n==0 || n==1) return;
  for (i=0; i<n-1; i++){
    if (A[i+1]<A[i]) Swap(&A[i], &A[i+1]);
  }
  BubbleSort(A, n-1);
}

int Partition(int *A, int p, int r){
  int x=A[r];
  int i=p-1, j;
  for (j=p; j<=r; j++){
    if (A[j]<=x){
      i++;
      Swap(&A[i], &A[j]);
    }
  }
  if (i<r) return i;
  else return i-1;
}

void QuickSort(int *A, int p, int r, int c){
  int q;
  if (p<r && r-p+1>=c){
    q=Partition(A, p, r);
    QuickSort(A, p, q, 0);
    QuickSort(A, q+1, r, 0);
  }
  if (p<r && r-p+1<c) BubbleSort(A, r-p+1);
}

void RandomArray(int *A, int size){
  int i;
  srand(time(NULL));
  for (i=0; i<size; i++)
    A[i]=rand()%size+1;
}

void BadArray(int *A, int size){
  int i;
  for (i=0; i<size; i++)
    A[i]=size-i;
}

int main(){
  struct timespec tp0, tp1;
  int length, c, i, j;
  printf("Podaj wartość całkowitą c (c < 100): ");
  scanf("%d", &c);
  printf("DANE LOSOWE:\n");
  printf("rozmiar tablicy N |  QuickSort  | QuickSort + BuubleSort \n");
  printf("------------------|-------------|-----------------------\n");
  for (length=100; length<1001; length=length+100){
    double Tn=0, Tn2=0, TnTotal=0, TnTotal2=0;
    for (i=0; i<(length/10); i++){
      int A[length], A1[length];
      RandomArray(A, length);
      for (j=0; j<length; j++)
        A1[j]=A[j];
      clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&tp0);
      QuickSort(A, 0, length, 0);
      clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&tp1);
      Tn=(tp1.tv_sec+tp1.tv_nsec/MLDD)-(tp0.tv_sec+tp0.tv_nsec/MLDD);
      TnTotal+=Tn;
      clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&tp0);
      QuickSort(A1, 0, length, c);
      clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&tp1);
      Tn2=(tp1.tv_sec+tp1.tv_nsec/MLDD)-(tp0.tv_sec+tp0.tv_nsec/MLDD);
      TnTotal2+=Tn2;
    }
    TnTotal=TnTotal/(length/10);
    TnTotal2=TnTotal2/(length/10);
    printf("%17d | %3.9lf | %3.9lf \n", length, TnTotal, TnTotal2);
  }
  printf("\nDANE NIEKORZYSTNE:\n");
  printf("rozmiar tablicy N |  QuickSort  | QuickSort + BuubleSort \n");
  printf("------------------|-------------|-----------------------\n");
  for (length=100; length<1001; length=length+100){
    int A[length], A1[length];
    BadArray(A, length);
    BadArray(A1, length);
    double Tn, Tn2;
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&tp0);
    QuickSort(A, 0, length, 0);
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&tp1);
    Tn=(tp1.tv_sec+tp1.tv_nsec/MLDD)-(tp0.tv_sec+tp0.tv_nsec/MLDD);
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&tp0);
    QuickSort(A1, 0, length, c);
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&tp1);
    Tn2=(tp1.tv_sec+tp1.tv_nsec/MLDD)-(tp0.tv_sec+tp0.tv_nsec/MLDD);
    printf("%17d | %3.9lf | %3.9lf \n", length, Tn, Tn2);
  }
  return 0;
}
