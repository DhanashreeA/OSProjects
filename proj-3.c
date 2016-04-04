/*
MEMBERS:
  Name: Anuran Duttaroy
  ASU # : 1209340284

  Name: Dhanashree Adhikari
  ASU # : 1209381300

ASU Fall 2015 - CSE 430 - Project 3
Implementing Producer Consumer problem using semaphore.
Ref - Program/Code for producer consumer was referred from Partha Dasgupta's
class notes and implementing example provided.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "sem.h"

semaphore *empty, *full, *mutex;
int N = 10;
int buffer[10];
int in = 0, out = 0, item_num=0, prod_delay = 1, cons_delay = 1;

void prod()
{
  while (1){
	printf("Producer 1 : ready to produce\n");
    P(empty);
      //P(mutex);
        printf("Producer 1: inserting item#%d, into slot #%d\n",  item_num, in);
        sleep(1);
        buffer[in] = item_num++; in = (in+1) % N;
      //V(mutex);
    V(full);
	sleep(prod_delay);
  }
}

void prod2()
{
  while (1){
	printf("Producer 2 : ready to produce\n");
    P(empty);
      //P(mutex);
        printf("Producer 2 : inserting item#%d, into slot #%d\n",  item_num, in);
        sleep(1);
        buffer[in] = item_num++; in = (in+1) % N;
      //V(mutex);
    V(full);
	sleep(prod_delay);
  }
}

void cons()
{
  while(1){
	printf("    Consumer 1 : ready to consume\n");
    P(full);
      //P(mutex);
        printf("    Consumer 1 : deleting item#%d, from slot #%d\n", buffer[out], out);
        sleep(1);
        out = (out+1) % N;
      //V(mutex);
	  V(empty);
  sleep(cons_delay);
  }
}

void cons2()
{
  while(1){
	printf("    Consumer 2 : ready to consume\n");
    P(full);
      //P(mutex);
        printf("   Consumer 2 : deleting item#%d, from slot #%d\n", buffer[out], out);
        sleep(1);
        out = (out+1) % N;
      //V(mutex);
	  V(empty);
  sleep(cons_delay);
  }
}

int main()
{
    RunQ = (struct queue *) malloc(sizeof(struct queue));
    empty = (struct semaphore *) malloc(sizeof(struct semaphore));
    full = (struct semaphore *) malloc(sizeof(struct semaphore));
    mutex = (struct semaphore *) malloc(sizeof(struct semaphore));
    initQueue(RunQ);
    initSem(full, 0);
    initSem(empty, N);
    initSem(mutex, 1);

    start_thread(&prod);
    start_thread(&cons);
    start_thread(&prod2);
    start_thread(&cons2);
    run();


    return 0;
}
