#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

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
  for(int i=0; i < size; i++) {
		printf("V[%d]: %d\n", i, v[i]);
	}
}


int radomizeNum() {
	return rand() % 100;
}

void *threadA(void *parg) {
	int x = *((int*) parg);
	printf("X value is: %d.\n", x);
	v[ind++] = x + 5;
	stop = 0;
}

void startThreadA() {
	int i, a;
	for(i=0; i < 5; i++) {
		pthread_t threadt;
		a = radomizeNum();
		pthread_create(&threadt, NULL, threadA, (void *)&a);
		pthread_join(threadt, NULL);
		printf("Criada thread %d - ", i);
		while(stop == 1);
		stop = 1;
	}
}

void *print(void* arg) {
	while(ind != 5);
	bubbleSort(v, 5);
	stop = 2;
}

void startThreadB() {
	pthread_t threadt;
	pthread_create(&threadt, NULL, print, NULL);
	pthread_join(threadt, NULL);
}

int main() {
	srand(time(NULL));
	startThreadA();
	startThreadB();

	while(stop != 2);
	return 0;
}
