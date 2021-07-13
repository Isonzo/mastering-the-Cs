#include "k_header.h" //Initial linked list functions
#include <stdlib.h>

void List_PushFront(List* list, int value);
unsigned int List_Count(List const* list);

int main()
{
	List* test;
	int number;

	test = List_Alloc();
	while (number != 0) //make a test list
	{
		printf("Input your number (or 0 to break): ");
		scanf("%d", &number);
		List_PushFront(test, number);
	}


	List_Print(test);


	free(test); //Frees up head and tail
}

void List_PushFront(List* list, int value)
{
	if(!list) return;
	Node* new_node;

	new_node = malloc(sizeof(Node));
	if(!new_node) return;
	new_node->data = value;
	new_node->next = list->first;
	list->first = new_node;
}
				
void append_list(int data, List* list) //Add an item at the end of a list
{
	Node* new_node;
	Node* temp = list->first;
	new_node = malloc(sizeof(Node));
	new_node->data = data;

	if (list->first == 0)
		list->first = new_node;
	while (1) //Loop until you find a null next value
	{
		if (temp->next != 0)
			temp = temp->next;
		else
			temp->next = new_node;
	}
}

unsigned int List_Count(List const* list)
{

}
void List_PushFront(List* list, int value);
