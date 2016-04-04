#include<stdio.h>
#include<stdlib.h>
#include "TCB.h"
typedef struct queue{
	TCB_t *head;
}queue;

void initQueue(queue *header){
	//head->context = NULL;
	header->head = NULL;
}

TCB_t *newItem(){
	TCB_t *item;
	item = (TCB_t *)malloc(sizeof(TCB_t));
	//printf("\nEnter data for new node:");
	//scanf("%d",&item->data);
	//printf("%d",item->data);
	item->next = NULL;
	item->prev = NULL;
	return item;
}

void addQueue(queue *header, TCB_t *item){
	if(header->head == NULL){
		header->head = item;
		item->next = item;
		item->prev = item;
	}
	else{
		item->prev = header->head->prev;
		item->next = header->head;
		header->head->prev->next = item;
		header->head->prev = item;
	}
}

TCB_t * delQueue(queue *header){
	if(header->head == NULL)
		return NULL;
	TCB_t *temp = header->head;
	if(header->head->next == header->head){
		header->head = NULL;
		return temp;
	}
	header->head->next->prev = header->head->prev;
	header->head->prev->next = header->head->next;
	header->head = header->head->next;
	temp->next = temp->prev = NULL;
	return temp;
}

void rotateQueue(queue *header){
	TCB_t *temp;
	//temp = delQueue(header);
	//printf("Temp:%x",temp);
	if(header->head != NULL)
		header->head = header->head->next;
}


void printQueue(queue *header){
	TCB_t *temp;
	temp = header->head;
	//printf("%d",temp->data);
	printf("\nData in queue:\n");
	int i=0;
	do{
		printf("%d",i);
		printf("\n");
		i++;
		temp = temp->next;
	}while(temp != header->head);
}
