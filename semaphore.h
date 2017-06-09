#ifndef SEMAPHORE_H
#define SEMAPHORE_H

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

class Semaphore {
    public:
        Semaphore(key_t, int, int);
        ~Semaphore();
        void P();
        void V();
        int getSemaphoreId();
        int getCounter();
        int getId();

    private:
      union semun{int val;} arg;
      int semaphoreId;
      int id;
      struct sembuf operationStructure;
};


#endif // SEMAPHORE_H
