#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "process.h"

int v[5] = {-1, -1, -1, -1, -1}, ind = 0, stop = 1;

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
  for(i=0; i < size; i++) {
		printf("V[%d]: %d\n", i, v[i]);
	}
}

int radomizeNum() {
	return rand() % 100;
}

void threadA(void *arg) {
	int x = *((int *) arg);
	printf("X value is: %d.\n", x);
	v[ind++] = x + 5;
	stop = 0;
}

void startThreadA() {
	int i, a;
	for(i=0; i < 5; i++) {
		long int threadId;
		a = radomizeNum();
	#if defined(_WIN32_)
		if((threadId = _beginthread(threadA, 4096, (void *)&a)) == (unsigned long)-1)	{
	#else
		if((threadId = _beginthread(threadA, 4096, (void *)&a)) == -1) 	{
	#endif
			printf("Unable to create a thread %d.\n", i);
			return;
		}
		printf("Criada thread %d - ", i);
		while(stop == 1);
		stop = 1;
	}
}

void print() {
	while(ind != 5);
	bubbleSort(v, 5);
	stop = 2;
}

void startThreadB() {
	long int threadId;
#if defined(_WIN32_)
	if((threadId = _beginthread(print, 4096, NULL)) == (unsigned long)-1)	{
#else
	if((threadId = _beginthread(print, 4096, NULL)) == -1) 	{
#endif
		return;
	}
}

int main() {
	srand(time(NULL));
	startThreadA();
	startThreadB();

	while(stop != 2);
	return 0;
}