#include <ucontext.h>
#include <string.h>
#include "threads.h"


typedef struct semaphore {
  struct queue *s_queue;
  int value;
} semaphore;

void initSem(semaphore *s, int val) {
  s->s_queue = (struct queue*) malloc(sizeof(struct queue));
  initQueue(s->s_queue);
  s->value = val;
}

void P(semaphore *s) {
  struct TCB_t *tcb;
  s->value = s->value - 1;
  if (s->value < 0) {
    tcb = delQueue(RunQ);
    addQueue(s->s_queue, tcb);
    swapcontext(&(tcb->context), &(RunQ->head->context));
  }
}

void V(semaphore *s) {
  struct TCB_t *tcb;
  s->value = s->value + 1;
  //printf("%d ----\n",s->value);
  if (s->value <= 0) {
    tcb = delQueue(s->s_queue);
    if (tcb != NULL){
      addQueue(RunQ, tcb);
    }
  }
  yield();
}
