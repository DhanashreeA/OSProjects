#include "q.h"
queue *RunQ;

void start_thread(void (*function)(void))
{ // begin pseudo code
        //    allocate a stack (via malloc) of a certain size (choose 8192)
	void *stack;
	TCB_t *item;
	stack = malloc(8192);
        //  allocate a TCB (via malloc)
	item = (TCB_t *)malloc(sizeof(TCB_t));
        // call init_TCB with appropriate arguments
	init_TCB(item, function, stack, 8192);
        // call addQ to add this TCB into the “RunQ” which is a global header pointer
	addQueue(RunQ,item);
  //end pseudo code
}

void run()
{       // real code
	ucontext_t parent;     // get a place to store the main context, for faking
	getcontext(&parent);   // magic sauce
	swapcontext(&parent, &(RunQ->head->context));  // start the first thread
}

void yield() // similar to run
{       // begin pseudo code
	ucontext_t currcontext;
	rotateQueue(RunQ);
	//printf("After rotate\n");
	getcontext(&currcontext);
        //  swap the context, from previous thread to the thread pointed to by RunQ
	swapcontext(&(RunQ->head->prev->context), &RunQ->head->context);
        // end pseudo code
}
