#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <time.h>
#include <stdlib.h>
#include <pthread.h>

#include "children.h"


sem_t mutex;







void spawnChildren(int numWorkers, int numDarts, int shmid){
	pid_t pids[numWorkers];

	

	int i;
	srand(time(NULL));
	
	for (i = 0; i < numWorkers; i++){
		if ((pids[i] = fork()) < 0){
			perror("fork");
			abort();		
		} else if (pids[i] == 0){
			//implement child labor here 
			childLabor(numWorkers,numDarts, shmid);
		}
	}
}
	
	
void childLabor(int numWorkers, int numDarts, int shmid){

						
	int *numHits = (int*) shmat(shmid, (void*)0, 0);
	
	int j;
	int localNumHits = 0;
	for (j = 0; j < numDarts; j++){
		double x = (double) rand()/ (double)RAND_MAX;
		double y = (double) rand()/ (double)RAND_MAX;
		double distance = x*x + y*y;
		if (distance <= 1){
			localNumHits++;
		}
		
		printf("%d darts have hit the circle---\n", localNumHits); //optional but i like to see things printed
	}
	

	double z = ((double) rand()/ (double)RAND_MAX)/100;
	sleep(z);

	*numHits = localNumHits;
	sem_post(&mutex);
	
	shmdt(numHits);		

	exit(0);

}






	
