#include "k_header.h" //Initial linked list functions and the headers in it
#include <limits.h> //INT_MIN

void List_PushFront(List* list, int value);
unsigned int List_Count(List const* list);

int main()
{
	List* test;
	List** ptr_to_test = &test;
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
	List_Reverse(test);
	List_Print(test);
	List_Free(ptr_to_test);
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

//Insert a new item into the list. Assume the list is already sorted.
//Obviously, it should remain sorted after the insertion.
void List_SortedInsert(List* list, int value)
{
	Node* new_node = malloc(sizeof(Node));
	if (!new_node) return;
	new_node->data = value;
	// Check if it should be first
	if (list->first->data >= value)
	{
		new_node->next = list->first;
		list->first = new_node;
		return;
	}
	// Check if it is last, to skip everything and avoid pointer issues
	if (list->last->data <= value)
	{
		list->last->next = new_node;
		list->last = new_node;
		return;
	}
	Node* temp = list->first;
	Node* prev = temp;
	for (int count = 0; count < List_Count(list); ++count)
	{
		if (temp->data >= value)
			break;
		else
		{
			prev = temp;
			temp = temp->next;
		}
	}
	prev->next = new_node;
	new_node->next = temp;
}

//Returns true if the list has no duplicate elements (i.e. all elements are unique).
bool List_IsUnique(List const* list)
{
	if (!list)
		return true;  // If it has no elements, they can't be duplicate, right?
	int list_count = List_Count(list);
	int values_present[list_count];
	Node* temp = list->first;
	int count = 0;

	for(int count = 0; count < list_count; ++count)
	{
		values_present[count] = temp->data;
		for (int i = 0; i < count; ++i)
		{
			if (values_present[i] == temp->data)
				return false;
		}
		temp = temp->next;
	}
	return true;
}

//Remove the first node in the list that has the specified value. If such a node does not exist, do nothing.
void List_Remove(List* list, int value)
{
	if (!list) return;
	Node* temp = list->first;
	Node* prev;
	if (list->first->data == value)
	{
		list->first = list->first->next;
		free(temp);
		return;
	}
	while(temp != list->last) // We want alternate behavior if we reach the end.
	{
		if (temp->data == value) // Found the number on death row.
		{
			// Connect previous and node that comes after temp, then eliminate temp.
			prev->next = temp->next;
			free(temp);
			return;
		}
		prev = temp;
		temp = temp->next;
		printf("prev: %d, temp: %d\n",prev->data, temp->data);
	}
	if (temp->data == value) // Double-checking.
	{
		prev->next = NULL;
		list->last = prev;
		free(temp);
	}
	return;
}

//Free the list and its contents from memory, then set the pointer to it to NULL.
void List_Free(List** list)
{
	Node* node_to_die;
	Node* temp = (*list)->first;
	while (temp != NULL)
	{
		node_to_die = temp;
		temp = temp->next;
		free(node_to_die);
	}
	free(*list);
	*list = NULL;
	list = NULL;
}

//Reverse the order of nodes in the list
void List_Reverse(List* list)
{
	Node* prev = NULL;
	Node* current = list->first;
	Node* next = NULL;

	while (current != NULL)
	{
		next = current->next;
		current->next = prev;
		prev = current;
		current = next;
	}
	list->last = list->first;
	list->first = prev;
}

//Create a new list with the same contents in the same order as the input list and return it.
List* List_Copy(List* list);
