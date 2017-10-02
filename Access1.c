#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "process.h"

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
	long int threadId;
#if defined(_WIN32_)
	if((threadId = _beginthread(threadA, 4096, NULL)) == (unsigned long)-1)	{
#else
	if((threadId = _beginthread(threadA, 4096, NULL)) == -1) 	{
#endif
		return;
	}
	printf("Thread A created!\n");

#if defined(_WIN32_)
	if((threadId = _beginthread(threadB, 4096, NULL)) == (unsigned long)-1)	{
#else
	if((threadId = _beginthread(threadB, 4096, NULL)) == -1) 	{
#endif
		return;
	}
	printf("Thread B created!\n");

#if defined(_WIN32_)
	if((threadId = _beginthread(threadC, 4096, NULL)) == (unsigned long)-1)	{
#else
	if((threadId = _beginthread(threadC, 4096, NULL)) == -1) 	{
#endif
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