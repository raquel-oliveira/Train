#include "semaphore.h"

/*Constructor
Parameters:
  key_t key: key for creating semaphores
  int initialValue: initial value of the semaphore's counter (1)
 */
Semaphore::Semaphore(key_t key, int initialValue){
  //Allocating one semaphore
  semaphoreId = semget(key,1,IPC_CREAT|0600);
  //Verifying errors
  if (semaphoreId == -1){
    perror("Error while creating semaphore\n");
    exit(1);
  }
  //Modifying the semaphore's configuration structure value
  arg.val = initialValue;

  //Updating the semaphore's counter with the SETVAL command
  semctl(semaphoreId,0,SETVAL,arg);
}

/*Destructor
*/

Semaphore::~Semaphore(){
  semctl(semaphoreId,0,IPC_RMID,arg);
}

/*
Function used when entereing the critical region.
Decrements the semaphore's counter.
*/

void Semaphore::P(){
  operationStructure.sem_num = 0; //the group has only one semaphore
  operationStructure.sem_op = -1; //P()
  //When the process finished, other processes that are waiting for the semaphores will be blocked
  operationStructure.sem_flg = SEM_UNDO;
  semop(semaphoreId,&operationStructure,1);
}

/*
Function used when exiting the critical region.
Increments the semaphore's counter.
*/

void Semaphore::V(){
  operationStructure.sem_num = 0; //the group has only one semaphore
  operationStructure.sem_op = 1; //V()
  //When the process finished, other processes that are waiting for the semaphores will be unblocked
  operationStructure.sem_flg = SEM_UNDO;
  semop(semaphoreId,&operationStructure,1);
}

/*
Returns the private attribute sempahoreId
*/
int Semaphore::getSemaphoreId(){
  return semaphoreId;
}


/*
Returns the semaphore's counter
*/
int Semaphore::getCounter(){
  return semctl(semaphoreId,0,GETVAL,arg);
}



