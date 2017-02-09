/********************************
*       TOMASZ ADAMCZYK         *
*       Nr albumu: 243217       *
*       Informatyka II ROK      *
*       Projekt1b.c             *
********************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void Swap(int *a, int *b){
  int temp=*a;
  *a=*b;
  *b=temp;
}

void Heapify(int *A, int i, int heap_size){
  int k, j;
  k=A[i-1];
  while (i<=heap_size/2){
    j=2*i;
    if (j<heap_size && A[j-1]<A[j]) j++;
    if (k>=A[j-1]) break;
    else{
      A[i-1]=A[j-1];
      i=j;
    }
  }
  A[i-1]=k;
}

void BuildHeap(int *A, int length){
  int i;
  for (i=length/2; i>0; i--) Heapify(A, i, length);
}

void HeapSort(int *A, int length){
  int i;
  BuildHeap(A, length);
  for (i=length; i>1; i--){
    Swap(&A[i-1], &A[0]);
    length--;
    Heapify(A, 1, length);
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
  HeapSort(A, length);
  out=fopen(strcat(argv[1], ".out_b"), "w");
  for (i=0; i<length; i++) fprintf(out, "%d\n", A[i]);
  printf("Sortowanie zrobione. Zapisano w %s\n", argv[1]);
  fclose(out);
  return 0;
}
