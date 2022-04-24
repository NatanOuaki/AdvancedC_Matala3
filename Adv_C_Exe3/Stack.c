#include "Stack.h"

/***************** Stack ADT Implementation *****************/

void initStack(Stack* s)
{
	s->head = 0;
}

void destroyStack(Stack* s)
{
	charNode* tmp = s->head;
	while (s->head != 0) {
		s->head = s->head->next;
		tmp->data = 0; // delete the data
		free(tmp);
		tmp = s->head;
	}
}

void push(Stack* s, char data)
{
	charNode* node1 = (charNode*)malloc(sizeof(charNode));
	if (node1 == 0) {
		printf("allocation failed");
	}
	if (s->head == 0) {
		s->head = node1;
		node1->next = 0;
		node1->data = data;
	}
	else {
		node1->data = data;
		node1->next = s->head;
		s->head = node1;
	}
}

char pop(Stack* s)
{
	char momt;
	momt = s->head->data;
	charNode* temp = s->head;
	s->head = s->head->next;
	temp->data = 0;
	free(temp);
	temp = 0;
	return momt;
}

int isEmptyStack(const Stack* s)
{
	if (s->head == 0)
		return 1;
	else return 0;
}

/*************** Functions using stacks - Implementation/definition **************************/

void flipBetweenHashes(const char* sentence)
{
	Stack* helpStack = (Stack*)malloc(sizeof(Stack));
	if (helpStack == 0)
		printf("allocation failed");
	int i = 0, counter = 0;
	while (sentence[i] != '\0') {
		if (sentence[i] != '#')
			printf("%c", sentence[i]);
		else {
			counter++; // count the number of #
			i++;
			int tmpI = 0;
			while (sentence[i] != '#') {
				push(helpStack, sentence[i]); // Push the items between 2 hashes to new stack
				i++;
				tmpI++; // count how much letters between 2 hashes
			}
			counter++; // Here we get to the second hashes
			if (counter % 2 == 0 && counter != 0) { // if you get to another hashes (the second) - start print 
				while (tmpI != 0) {
					printf("%c", helpStack->head->data);
					pop(helpStack);
					tmpI--;
				}
			}
		}
		i++;
	}
	free(helpStack);
}

int isPalindrome(Stack* s)
{
	if (s->head == 0)
		return 1;

	int size = 0, counter = 1;
	charNode* tmp1 = s->head;
	charNode* tmp2 = s->head;

	while (tmp1 != 0) {
		size++;
		tmp1 = tmp1->next;
	}
	tmp1 = s->head;
	for (int i = 1; i <= (size + 1) / 2; i++) {
		for (int j = 1; j < size; j++) {
			tmp2 = tmp2->next;
		}
		if (tmp2->data != tmp1->data) {
			return 0;
		}
		tmp1 = tmp1->next;
		size -= 2;
		tmp2 = tmp1;
		if (size == 1 || size == 0) {
			return 1;
		}
	}
}

void rotateStack(Stack* s, int n)
{
	if (n < 0 || s->head == 0)
		return;
	Stack* tmp1 = (Stack*)malloc(sizeof(Stack));
	Stack* tmp = (Stack*)malloc(sizeof(Stack));
	if (tmp == 0 || tmp1 == 0)
		printf("allocation failed");
	initStack(tmp1);
	initStack(tmp);
	charNode* tmp2 = s->head;
	tmp->head = s->head;
	int count = 0;
	while (tmp2 != 0) {
		count++;
		tmp2 = tmp2->next;
	}
	if (n > count)
	{
		return;
	}
	for (int i = 0; i < count - n; i++) // cut the stack by count - n letters to new stack
	{
		char chr = pop(s);
		push(tmp, chr);
	}
	for (int i = 0; i < n; i++) //  cut the stack by n letters to new stack
	{
		char chr = pop(s);
		push(tmp1, chr);
	}

	for (int i = 0; i < count - n; i++) // push the items to stack by order
	{
		char chr = pop(tmp);
		push(s, chr);
	}
	for (int i = 0; i < n; i++) //push the items to stack by order
	{
		char chr = pop(tmp1);
		push(s, chr);
	}
	while (s->head != 0) // print new stack
	{
		printf("%c\n", s->head->data);
		s->head = s->head->next;
	}
	free(tmp);
	free(tmp1);
}
