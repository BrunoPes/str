#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

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
	pthread_t threadt;
	int param = radomizeNum();
	int *pparam = &param;

	if(pthread_create(&threadt, NULL, threadA, (void*)pparam)) {
		return;
	}
}

void print(void* arg) {
	while(ind != 5);
	bubbleSort(v, 5);
	stop = 1;
}

void startThreadB() {
	pthread_t threadt;

	if(pthread_create(&threadt, NULL, print, NULL)) {
		return;
	}
}

int main() {
	for(int i=0; i < 5; i++) {
		startThreadA();
	}
	startThreadB();

	while(stop != 1);
	return 0;
}