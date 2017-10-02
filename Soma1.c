#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "process.h"

int v[5] = {-1, -1, -1, -1, -1}, ind = 0, stop = 0;

void bubbleSort(int *array, int size) {
  int i, j, aux;
  
  for (i = 0 ; i < (size - 1); i++) {
    for (j = 0 ; j < size - i - 1; j++) {
      if (array[j] > array[j+1]) {
        aux = array[j];
        array[j] = array[j+1];
        array[j+1] = aux;
      }
    }
  }
 
  printf("\nVetor ordenado:\n");
  for(int i=0; i < size; i++) {
		printf("V[%d]: %d\n", i, v[i]);
	}
}


int radomizeNum() {
	srand((unsigned)time(NULL));
	return rand() % 100;
}

void threadA(void *parg) {
	int x = *((int*) parg);
	printf("X value is: %d.\n", x);
	v[ind++] = x + 5;
}

void startThreadA() {
	long int threadId;
	int param = radomizeNum();
	int *pparam = &param;
#if defined(_WIN32_)
	if((threadId = _beginthread(threadA, 4096, (void*)pparam)) == (unsigned long)-1)	{
#else
	if((threadId = _beginthread(threadA, 4096, (void*)pparam)) == -1) 	{
#endif
		// printf("Unable to create a thread A.\n");
		return;
	}

	// printf("Created a thread A.\n");
}

void print() {
	while(ind != 5);
	bubbleSort(v, 5);
	stop = 1;
}

void startThreadB() {
	long int threadId;
#if defined(_WIN32_)
	if((threadId = _beginthread(print, 4096, NULL)) == (unsigned long)-1)	{
#else
	if((threadId = _beginthread(print, 4096, NULL)) == -1) 	{
#endif
		// printf("Unable to create a thread B.\n");
		return;
	}

	// printf("Created a thread B.\n");
}

int main() {
	for(int i=0; i < 5; i++) {
		startThreadA();
	}
	startThreadB();

	while(stop != 1);
	return 0;
}