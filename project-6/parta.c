//This is the code for part A, in which we don't wait at all for anything to finish.

#include <stdio.h>
#include <pthread.h>

int count;
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
	printf("The Value of Count is:  %d\n", count);
	return 0;
}

void* incrementCounter (void* m)
{
	int i;
	for (i = 0; i < 10; ++i)
	{
		int tempValue = count;
		sleep(1);
		tempValue = tempValue + 1;
		count = tempValue;
	}

	return NULL;
}


