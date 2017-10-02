#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

char *v, ind = 0, stop = 0;

void threadA(void *parg) {
	while(ind < 30) {
		if(ind%3 == 0) {
			v[ind++] = 'A';
		}
	}
}

void threadB(void *parg) {
	while(ind < 30) {
		if(ind%3 == 1) {
			v[ind++] = 'B';
		}
	}
}

void threadC(void *parg) {
	while(ind < 30) {
		if(ind%3 == 2) {
			v[ind++] = 'C';
		}
	}

	for(int i=0; i < 30; i++) {
		printf("V[%d]: %c\n", i, v[i]);
	}
	stop = 1;
}

void startThreads() {
	pthread_t thread1;
	pthread_t thread2;
	pthread_t thread3;

	if(pthread_create(&thread1, NULL, threadA, NULL)) {
		return;
	}
	if(pthread_join(thread1, NULL)) {
		return;
	}
	printf("Thread A created!\n");

	if(pthread_create(&thread2, NULL, threadB, NULL)) {
		return;
	}
	if(pthread_join(thread2, NULL)) {
		return;
	}
	printf("Thread B created!\n");

	if(pthread_create(&thread3, NULL, threadC, NULL)) {
		return;
	}
	if(pthread_join(thread3, NULL)) {
		return;
	}
	printf("Thread C created!\n");
}

int main() {
	v = malloc(30*sizeof(char));
	startThreads();

	while(stop != 1);
	return 0;
}