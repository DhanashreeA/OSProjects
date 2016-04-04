#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "sem.h"


semaphore * rsem;
semaphore * wsem;
semaphore * mutex;
int rwc = 0, wwc = 0, rc = 0, wc = 0;
int readerID=0, writerID = 0;


void writerEntry(int ID)					// Writer Entry function
{
	printf("\t\t\t\t[writer: #%d]\tEntering in entry section\n", ID);
	P(mutex);
	if (rc > 0 || wc > 0) {				// Checking the reader count and the writer count
	    printf("\t\t\t\t[writer: #%d] BLOCKED\n", ID);
	    wwc++;
	    V(mutex);
	    P(wsem);
	    wwc--;
	}
	wc++;
	V(mutex);
}

void writerExit(int ID)						// Writer exit code.
{
	P(mutex);
	wc--;
	printf("\t\t\t\t[writer: #%d] In exit section\n", ID);
	if (rwc > 0) {								// Checks for the Waiting Reader Count. It should be 0 for a writer to enter the critical section.
	    V(rsem);
	} else if (wwc > 0) {					// Checks for the Waiting writer count. It should be 0 as well.
	    V(wsem);
	} else {
	    V(mutex);
	}
}

void readerEntry(int ID)				// function for the reader entry.
{
	printf("[reader: #%d]\tEntering entry section\n", ID);
	P(mutex);
	if (wwc > 0 || wc > 0) {			// Just the count of the writers are required for the reader entry
	    printf("[reader: #%d]\tBLOCKED\n", ID);
	    rwc++;
	    V(mutex);
	    P(rsem);
	    printf("[reader: #%d]\tUNBLOCKED\n", ID);
	    rwc--;			}
	rc++;
	if (rwc > 0)
	    V(rsem);
	else
	    V(mutex);
}

void readerExit(int ID)
{
	P(mutex);
	rc--;
	if (rc == 0 && wwc > 0) {		// If the reader count is 0, it allows the writers to enter the CS.
	    V(wsem);
	} else
	    V(mutex);

}




void reader(void)				// Defination of readers
{
	int ID;
  	P(mutex);
	ID = readerID++;
	V(mutex);
	while(1){
		readerEntry(ID);
		printf("[reader #%d]\t######READING######\n", ID);
		sleep(1);
		readerExit(ID);
  	}
}

void writer(void)				// Defination of writers
{
	int ID;
	P(mutex);
	ID = writerID++;
	V(mutex);
	while(1){
	 	writerEntry(ID);
		printf("\t\t\t\t[writer: #%d]\t-----WRITING-----\n", ID);
		sleep(1);
		writerExit(ID);
  	}
}


int main()
{			// Allocating memory for data types.
  RunQ = (struct queue *) malloc(sizeof(struct queue));
	wsem = (struct semaphore *) malloc(sizeof(struct semaphore));
	rsem = (struct semaphore *) malloc(sizeof(struct semaphore));
	mutex = (struct semaphore *) malloc(sizeof(struct semaphore));
	initQueue(RunQ);
	initSem(rsem, 1);
	initSem(wsem, 1);
	initSem(mutex, 1);

	void (*reader1)();
	reader1 = &reader;
	void (*reader2)();
	reader2 = &reader;
	void (*writer1)();
	void (*reader3)();
	reader3 = &reader;
	writer1 = &writer;

	void (*writer2)();
	writer2 = &writer;

	// Starting the reader and writer threads.
	start_thread(reader1);
	start_thread(reader2);
	start_thread(reader3);

	start_thread(writer1);
	start_thread(writer2);

	run();

    while (1) sleep(1);
}
