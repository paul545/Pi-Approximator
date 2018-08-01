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

//Paul Bosonetto

sem_t mutex;

int main(int argc, char**argv){

	
	//create shared memory 
	key_t key = ftok("shmfile", 65);
	int shmid = shmget(key, sizeof(unsigned long long), 0666 |IPC_CREAT);
	int *numHits = (int*) shmat(shmid, (void*)0, 0);

	
	if (argc < 3 || argc > 3){
		printf("Wrong number of arguments. Usage: ./my-pi <numWorkers> <numDarts>\n");
		exit(0);
	}
	int numWorkers = atoi(argv[1]);
	int numDarts = atoi(argv[2]);
	
	
	spawnChildren(numWorkers, numDarts, shmid);
	
	
	//wait for child slaves to finish and exit
	int status;
	pid_t pid;
	while (numWorkers > 0){
		pid = wait(&status);
		printf("\nChild with PID %ld exited with status 0x%x. \n\n", (long)pid, status);
		numWorkers--;
	}
	
	double pi_estimate = 4 * (double) *numHits / numDarts;
	
	printf("Our pi estimate is %f. Woo.\n", pi_estimate);
	
	shmctl(shmid, IPC_RMID, NULL);
	

}

































