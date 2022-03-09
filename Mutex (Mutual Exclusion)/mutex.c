//Author: Jeffrey Jordan
//Date: 2/18/20
//File: Mutex.c - Simulated bank functions with mutex protection.

#include <pthread.h>
#include <stdio.h>
#include <unistd.h> 
#include <stdlib.h>

/* Shared Variables */

int balance = 100;
pthread_t wThread1; // referenced project 2 (sudoku)
pthread_t wThread2;
pthread_t dThread1;
pthread_t dThread2;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; // lock. Referenced linux.die.net/man/3/pthread_mutex_init

void *p1; // thread identifiers
void *p2;
void *p3;
void *p4;

void withdraw(int tid);
/*
 * Function: void withdraw(int tid)
 *
 *
 * Parameters: int tid
 * Thread ID
 *
 *
 * Return: void function. Thread alters the amount of balance by decreasing by 10.
 *
 */

void deposit(int tid);
/*
 * Function: void deposit(int tid)
 *
 *
 * Parameters: int tid
 * Thread ID
 *
 *
 * Return: void function. Thread alters the amount of balance by increasing by 11.
 *
 */

int main(){
	/* Creates threads with their instructions */
  pthread_create(&wThread1, NULL, (void *)withdraw, &p1); // referenced sudoku project
  pthread_create(&wThread2, NULL, (void *)withdraw, &p2);
  pthread_create(&dThread1, NULL, (void *)deposit, &p3);
  pthread_create(&dThread2, NULL, (void *)deposit, &p4);
	/* Waits for threads to complete */
  pthread_join(wThread1, NULL);
  pthread_join(wThread2, NULL);
  pthread_join(dThread1, NULL);
  pthread_join(dThread2, NULL);

  return 0;
    
}

void withdraw(int tid){

  for (int i=0; i<10; i++){ 
    pthread_mutex_lock(&mutex); // the thread that gets mutex locks the critical region
    int readbalance = balance;
    printf("At time %d, the balance for withdrawal thread %d is %d", i, tid, balance);
    if (readbalance < 10) // balance check for enough credit.
        printf("not enough");
    else {
        readbalance -= 10;
        usleep(1);
        balance = readbalance;
        printf("At time %d, the balance after withdrawal thread %d is %d", i, tid, balance);
        usleep(1);
	pthread_mutex_unlock(&mutex); // unlocks it for other threads
    }
  }

  pthread_exit(0); // tidying up after itself

}

void deposit(int tid){
        
  for (int i=0; i<10; i++){ 
    pthread_mutex_lock(&mutex);  // eg.Bucknell.edu/~xmeng/course/cs4334/example/pthread/bank.c
    int readbalance = balance;
    printf("At time %d, the balance before depositing thread %d is %d", i, tid, balance);
    readbalance += 11;
    usleep(10);
    balance = readbalance;
    printf("At time %d, the balance after depositing thread %d is %d", i, tid, balance);
    usleep(10);
    pthread_mutex_unlock(&mutex);
  }

  pthread_exit(0);
}
