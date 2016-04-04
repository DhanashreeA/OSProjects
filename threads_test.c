// Name: Anuran Duttaroy			| ASU # : 1209340284
// Name: Dhanashree Adhikari	| ASU # : 1209381300
// Class: CSE430
// Assignment: Project 2


#include "threads.h"
int global = 0;

void function1() {
	int local1 = 1;

	while(1) {
		printf("Thread 1:\tLocal: %d\tGlobal: %d\n", local1, global);
		global++;
		local1 = local1*1;
		sleep(2);
		yield();
	}

}

void function2() {
	int local2 = 2;

	while(1) {
		printf("Thread 2:\tLocal: %d\tGlobal: %d\n", local2, global);
		global++;
		local2 = local2*2;
		sleep(2);
		yield();
	}
}

void function3() {
	int local3 = 3;
	while(1){
		printf("Thread 3:\tLocal: %d\tGlobal: %d\n", local3, global);
		global++;
		local3 = local3*3;
		sleep(2);
		yield();
	}
}

void function4() {
	int local4 = 4;
	while(1){
		printf("Thread 4:\tLocal: %d\tGlobal: %d\n", local4, global);
		global++;
		local4 = local4*3;
		sleep(2);
		yield();
	}
}

int main() {

	RunQ = (struct queue*) malloc(sizeof(struct queue));
	initQueue(RunQ);
	start_thread(function1);
	start_thread(function2);
	start_thread(function3);
	start_thread(function4);
	run();
	return 0;
}
