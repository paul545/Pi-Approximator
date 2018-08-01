#ifndef children_h
#define children_h


void spawnChildren(int numWorkers, int numDarts, int shmid);
void childLabor(int numWorkers, int numDarts, int shmid);


#endif //children_h
