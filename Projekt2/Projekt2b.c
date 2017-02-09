/********************************
*       TOMASZ ADAMCZYK         *
*       Nr albumu: 243217       *
*      Informatyka II ROK       *
*     Projekt2b.c - ALL.4.5     *
********************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void Swap(int *a, int *b){
  int temp=*a;
  *a=*b;
  *b=temp;
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

void QuickSort(int *A, int p, int r){
  int q;
  if (p<r){
    q=Partition(A, p, r);
    QuickSort(A, p, q);
    QuickSort(A, q+1, r);
  }
}

int main(int argc, char* argv[]){
  FILE *in, *out;
  in=fopen(argv[1], "r");
  if (!in){
    fprintf(stderr, "Nie ma takiego pliku %s\n", argv[1]);
    exit(-1);
  }
  int length, i;
  fscanf(in, "%d", &length);
  int *A=(int*)malloc(length*sizeof(*A));
  for (i=0; i<length; i++) fscanf(in, "%d", &A[i]);
  fclose(in);
  QuickSort(A, 0, length-1);
  out=fopen(strcat(argv[1], ".out_a"), "w");
  for (i=0; i<length; i++) fprintf(out, "%d\n", A[i]);
  printf("Sortowanie zrobione. Zapisano w %s\n", argv[1]);
  fclose(out);
  return 0;
}
