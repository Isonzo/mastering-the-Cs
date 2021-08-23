#include "k_header.h" //Initial linked list functions and the headers in it
#include <limits.h> //INT_MIN

void List_PushFront(List* list, int value);
unsigned int List_Count(List const* list);

int main()
{
	List* test;
	int array[5] = {1, 2, 3, 4, 5};
	int* ptr = array;

	// test = List_Alloc();
	// while (number != 0) //make a test list
	// {
	// 	printf("Input your number (or 0 to break): ");
	// 	scanf("%d", &number);
	// 	List_PushBack(test, number);
	// }

	test = List_FromArray(ptr, 5);
	List_Print(test);

	free(test); //Frees up head and tail
	return 0;
}

//Pushes value into the front of the list
void List_PushFront(List* list, int value)
{
	if(!list) return;
	Node* new_node;

	new_node = malloc(sizeof(Node));
	if(!new_node) return;  //If malloc fails, don't try to add the node
	new_node->data = value;
	if (List_IsEmpty(list)) //If list is empty, assign first and last pointers
	{
		list->first = new_node;
		list->last = new_node;
		return;
	}
	new_node->next = list->first;
	list->first = new_node;
}

//Counts the number of nodes in the list and returns the value
unsigned int List_Count(List const* list)
{
	if(!list) return 0;
	Node* current = list->first;
	int count = 0;

  while(current)  //While current address is a valid one, we assume it's a node
  {
    ++count;
    current = current->next;
  }
	return count;
}

//Adds the data of the nodes in a list
int List_Sum(List const* list)
{
	if (!list) return 0;
	int sum = 0;
	Node* current = list->first;

  while(current)  //While address is valid, access data and add it to "sum"
  {
    sum += current->data;
    current = current->next;
  }
	return sum;
}

//Checks to see if it is sorted in ascending order
bool List_IsSorted(List const* list)
{
	if (!list) return false; //Is a non-existing list sorted? That's something for the philosophers to answer
	int previous_num = INT_MIN;
	Node* current = list->first;

	while(current)
	{
		if(current->data < previous_num) return false; // if number is ever less than the previous one, it's unsorted
		else
		{
			previous_num = current->data;
			current = current->next;
		}
	}
	return true;
}
//Checks if list is empty
bool List_IsEmpty(List const* list)
{
	if(!list) return true; //Is a non-existent list empty? I refer back to the conundrum of the sorted list
	if (!(list->first)) return true; //if the first element is invalid, either something's wrong or the list is simply empty
	else return false;
}

//Adds a node at the end of the list
void List_PushBack(List* list, int value)
{
	if(!list) return;
	Node* new_node;
	Node* temp;

	new_node = malloc(sizeof(Node));
	if(!new_node) return;  //If malloc fails, don't try to add the node
	new_node->data = value;

	if (List_IsEmpty(list)) //If list is empty, assign first and last pointers
	{
		list->first = new_node;
		list->last = new_node;
	}
	else
	{
		temp = list->last;
		temp->next = new_node;
		list->last = new_node;
	}
}

//It turns the array into a linked list. In goes array, out goes linked list.
List* List_FromArray(int const* array, unsigned int arrayLength)
{
	List* list = List_Alloc();
	Node* temp;
	Node* previous;
	for(int i = 0; i <= arrayLength; ++i)
	{
		// This avoids an unneccesary malloc at the end
		if(i < arrayLength)
		{
			temp = malloc(sizeof(Node));
			if(!temp) return NULL;
			temp->data = *(array + i);
		}

		if(i == 0)
		{
			list->first = temp;
			previous = temp;
		}
		else if(i == arrayLength)
		{
			list->last = temp;
			previous->next = NULL;
			previous = temp;
		}
		else
		{
			previous->next = temp;
			previous = temp;
		}


	}
	// Check if linked list is the same length. If it isn't, proccess has failed
	if (List_Count(list) != arrayLength) return NULL;
	return list;
}

//Insert value at a certain index, assuming linked list is 0-indexed and has at least one value
void List_Insert(List* list, int value, unsigned int index)
{
	Node* new_node = malloc(sizeof(Node));
	if (!new_node) return;
	new_node->data = value;

	// If the index is bigger than the list, abort
	if (index > List_Count(list))
		return;

	// If the node is at the beginning or end, let's just save ourselves the hassle
	if(index == 0)
	{
		new_node->next = list->first;
		list->first = new_node;
		return;
	}
	else if(index == List_Count(list))
	{
		list->last->next = new_node;
		new_node->next = NULL;
		list->last = new_node;
		return;
	}
	// Since it's not the first or last, we make some variables to help us keep track and iterate through the list to insert
	Node* previous;
	Node* temp = list->first;
	for (int count = 0; count < index; ++count)
	{
		previous = temp;
		temp = temp->next;
	}
	previous->next = new_node;
	new_node->next = temp;
	return;
}
