#include "Queue.h"

/***************** Queue ADT Implementation *****************/
void reverse(Queue* queue);
void initQueue(Queue* q)
{
	q->tail = 0;
	q->head = 0;
}

void destroyQueue(Queue* q)
{
	intNode* tmp = q->head;
	while (q->head != 0) {
		q->head = q->head->next;
		tmp->data = 0; // delete the exist data
		free(tmp); // free the item
		tmp = q->head;
	}
}

void enqueue(Queue* q, unsigned int data)
{
	intNode* new = (intNode*)malloc(sizeof(intNode));
	if (new == 0)
		printf("allocation failed");
	new->data = data;
	new->next = 0;
	if (q->head == 0) { // if the queue is empty
		q->head = new;
		q->tail = new;
	}
	else // if there is items in the queue
	{
		q->tail->next = new;
		q->tail = new;
	}
}

unsigned int dequeue(Queue* q)
{
	int tmpd = q->head->data;
	intNode* tmp = q->head;
	if (q->head == q->tail) { // if there is only one item in queue
		q->head = 0;
		q->tail = 0;
	}
	else {
		// if there are more than one items in queue
		q->head = q->head->next;
	}


	free(tmp); // free the item the was removed
	return tmpd;
}

int isEmptyQueue(const Queue* q)
{
	if (q->head == 0) // if the queue is empty return 1, else return 0
		return 1;
	else return 0;
}

/***************** Functions using Queues - Implementation/definition **************************/

void rotateQueue(Queue* q)
{
	if (q == 0) { // is queue is empty
		printf("There is no queue");
		return;
	}
	intNode* tmp1 = q->head;
	intNode* tmp2 = q->tail;
	intNode* tmp3 = 0;
	while (tmp1 != tmp2) {
		tmp1 = tmp1->next;
		if (tmp1->next->next == 0) { // save the one before last item.
			tmp3 = tmp1;
			break;
		}
	}
	q->tail->next = q->head;
	q->head = q->tail;
	q->tail = tmp3;
	q->tail->next = 0;
}

void cutAndReplace(Queue* q)
{
	Queue* newQ1 = (Queue*)malloc(sizeof(Queue));
	if (newQ1 == 0)
		printf("allocation failed");
	initQueue(newQ1);
	intNode* tmp1 = q->head;
	intNode* tmp2 = q->tail;
	int queueCounter = 0;
	int queueDataSum = 0;
	while (q->head != 0) { // count the queue items in queue and the sum of data.
		queueDataSum += q->head->data;
		q->head = q->head->next;
		queueCounter++;
	}
	q->head = tmp1;
	q->tail = tmp2;
	if (queueCounter % 2 != 0) { // if the queue items are odd - enqueue more item.
		enqueue(q, (queueDataSum / queueCounter));
		queueCounter++;
	}
	for (int i = 0; i < (queueCounter / 2); i++) { // seperate queue by 2
		enqueue(newQ1, dequeue(q));
	}
	reverse(q); // reverse half of the q
	q->tail->next = newQ1->head; // connect between 2 new queues
	q->tail = newQ1->tail;
	free(newQ1);
}

void sortKidsFirst(Queue* q)
{
	intNode* tmp1 = q->head;
	intNode* tmp2 = q->tail;
	intNode* tmp3 = (intNode*)malloc(sizeof(intNode));
	if (tmp3 == 0)
		printf("allocation failed");
	int min = q->head->data;
	int queueCounter = 0;
	Queue* newQ = (Queue*)malloc(sizeof(Queue));
	initQueue(newQ);
	while (q->head != 0) { // count the queue items in queue
		q->head = q->head->next;
		queueCounter++;
	}
	q->head = tmp1;
	q->tail = tmp2;
	for (int j = 0; j < queueCounter; j++) {
		for (int i = 0; i < queueCounter; i++) {
			if (q->head->data < min && q->head->data != 0) { //find the lowest data and put him in newq
				min = q->head->data;
				tmp3 = q->head;
			}
			q->head = q->head->next;
		}
		tmp3->data = 0;
		enqueue(newQ, min); // put in the newq the items be order
		q->head = tmp1;
		q->tail = tmp2;
		if (q->head->data == newQ->tail->data) {
			q->head->data = 0;
			min = 1000;
		}
		else
			min = q->head->data;
	}
	q->head = newQ->head;
	free(tmp3);
}


void RotateQueue2(Queue* q) {
	intNode* tmp1 = q->head;
	intNode* tmp2 = q->tail;
	intNode* tmp3 = 0;
	while (tmp1 != tmp2) {
		tmp1 = tmp1->next;
		if (tmp1->next->next == 0) { // save the one before last item
			tmp3 = tmp1;
			break;
		}
	}
	q->tail->next = q->head;
	q->head = q->head->next;
	q->tail = q->tail->next;
	q->tail->next = 0;

}

void reverse(Queue* queue) {
	int element;
	if (isEmptyQueue(queue)) { // if the queue is empty, return
		return;
	}
	element = dequeue(queue);
	reverse(queue);
	enqueue(queue, element);
}


void printQueue(Queue* q) {
	intNode* tmp1 = q->head;
	intNode* tmp2 = q->tail;
	int inter = 1;
	while (tmp1 != 0) {
		printf("the %d item is: %d\n", inter, tmp1->data);
		tmp1 = tmp1->next;
		inter++;
	}
}
