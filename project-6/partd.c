//This code file is specifically for part B, in which we actually *wait* for the threads to finish.s

#include <stdio.h>
#include <pthread.h>

int count;
pthread_mutex_t countLock;
#define THREADS 4

void* incrementCounter (void* m);

int main(int argc, char* argv[])
{
	int valid;
	pthread_t threadList[THREADS];
	int ctr;
	for(ctr = 0; ctr < THREADS; ctr++)
	{
		valid = pthread_create(&threadList[ctr], NULL, incrementCounter, NULL);
		if(valid)
		{
			printf("One of the threads failed to initialize.  Aborting program.");
			return -1;
		}
	}
	for(ctr = 0; ctr < THREADS; ctr++)
		pthread_join(threadList[ctr], NULL);
	printf("The Value of Count is:  %d\n", count);
	return 0;
}

void* incrementCounter (void* m)
{
	int i;
	for (i = 0; i < 10; ++i)
	{
		pthread_mutex_lock(&countLock);
		int tempValue = count;//declaration on this should REALLY be outside of the loop, but I'm doing it just how I was told to...
		sleep(1);
		tempValue = tempValue + 1;
		count = tempValue;
		pthread_mutex_unlock(&countLock);
	}

	return NULL;
}


