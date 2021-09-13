#include "k_header.h" //Initial linked list functions and the headers in it
#include <limits.h> //INT_MIN

void List_PushFront(List* list, int value);
unsigned int List_Count(List const* list);

void Test_Function(Node* node)
{
	++(node->data);
}

int main()
{
	List* test;
	List** ptr_to_test = &test;
	int array[5] = {1, 2, 3, 4, 5};
	int* ptr = array;
	List* new_test;
	List** ptr_to_new = &new_test;

	void (*function_ptr)(Node*);
	function_ptr = &Test_Function;

	// test = List_Alloc();
	// while (number != 0) //make a test list
	// {
	// 	printf("Input your number (or 0 to break): ");
	// 	scanf("%d", &number);
	// 	List_PushBack(test, number);
	// }

	test = List_FromArray(ptr, 5);
	List_Transform(test, function_ptr);
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

//Create a new list with the same contents in the same order as the input list and return it. Returns NULL if fails.
List* List_Copy(List* list)
{
	if (!list) return NULL;
	List* new_list;
	List** ptr_to_new;
	new_list = List_Alloc();
	if (!new_list) return NULL;
	Node* temp = list->first;
	// I'm gonna go ahead and and assume that I can't simply point to the original list's nodes
	while (temp != NULL)
	{
		Node* prev_last = new_list->last;
		List_PushBack(new_list, temp->data);
		temp = temp->next;
		if (prev_last == list->last)
		{
			List_Free(ptr_to_new);
			return NULL;
		}
	}
	return new_list;
}

/////////////////////////
/////////////////////////
////////EXTRA CREDIT/////
/////////////////////////
/////////////////////////

////Pointer practice
//Swap the position of the nodes located at the two indices in the given list.
void List_SwapNodes(List* list, unsigned int firstIndex, unsigned int secondIndex)
{
	if (!list) return;
	Node* first_node = NULL;
	Node* second_node = NULL;
	Node* prev_first = NULL;
	Node* prev_second = NULL;
	Node* future_first = NULL;
	Node* future_second = NULL;
	Node* temp = list->first;
	int count = 0;

	if (firstIndex == secondIndex) return;
	if (firstIndex >= List_Count(list) || secondIndex >= List_Count(list)) return;

	// Get first_node and second_node, as well as surrounding nodes.
	while (temp != NULL || (first_node == NULL) && (second_node == NULL))
	{
		if (count == firstIndex - 1)
		{
			future_first = temp->next->next;
			first_node = temp->next;
			prev_first = temp;
		}
		else if (count == secondIndex - 1)
		{
			future_second = temp->next->next;
			second_node = temp->next;
			prev_second = temp;
		}

		temp = temp->next;
		++count;
	}
	// Time for the switcheroo
	prev_first->next = second_node;
	second_node->next = future_first;
	prev_second->next = first_node;
	first_node->next = future_second;

	// Fix up first and last pointers, assuming something happened to them
	if (first_node == list->last)
		list->last = second_node;
	else if (first_node == list->first)
		list->first = second_node;
	else if (second_node == list->last)
		list->last = first_node;
	else if (second_node == list->first)
		list->first = first_node;
	return;
}

////C++ practice
//Run the specified function for every node in the list.
void List_ForEach(List const* list, void(*fn)(Node const*))
{
	if (!list) return;
	Node* temp = list->first;

	while (temp != NULL)
	{
		fn(temp);
		temp = temp->next;
	}
}

////C++ practice
//Same as above but non-const. Do NOT try to reuse code between these two functions.
// Using the same code works in my test case ;_;
void List_Transform(List* list, void(*fn)(Node*))
{
	if (!list) return;
	Node* temp = list->first;

	while (temp != NULL)
	{
		fn(temp);
		temp = temp->next;
	}
}

////C++ practice
//Replace the contents of list1 with the contents of list2, and vice versa.
void List_Swap(List* list1, List* list2)
{
	Node* temp_first = list1->first;
	Node* temp_last = list1->last;

	list1->first = list2->first;
	list1->last = list2->last;

	list2->first = temp_first;
	list2->last = temp_last;
}

////C++ practice
//Clear the list stored at newList, and move the contents of oldList there.
//The fate of oldList is irrelevant. You may leave it in a garbage state if you wish.
////Hint: There's a very bad and slow way to do this, and a very nice and fast way.
////Hint 2: Don't forget the user might surprise you with their inputs...
void List_Move(List* oldList, List* newList)
{

}

////Pointer and general data structure practice
//Remove all duplicate items in the list, if any. Leave the first occurrence in the list.
void List_RemoveDuplicates(List* list);

////Pointer practice
//Sort the contents of the list. It should contain the same notes, but in ascending order.
////I'm not concerned with the efficiency of the sort itself, but I do care about the efficiency that nodes are moved with.
////I recommend implementing a selection sort for this.
////DO NOT try to use your List_SwapNodes function!!
void List_Sort(List* list);

////Pointer practice
//Copy all the nodes from the "extra" list to the destination list.
//You may assume the destination list is already sorted.
//The destination list should remain sorted afterwards.
void List_Blend(List* destination, List const* extra);

//Same as List_Blend, except the nodes from the extra list should be moved and not copied.
//The extra list should have no nodes on it afterward.
void List_Merge(List* destination, List* extra);

////C++ practice
//Return the difference between the two lists.
//The return value for this should mimic the same pattern as strcmp() from the standard C library.
//For example, if the lists are identical you should return zero.
//If either list is null, return INT_MAX.
int List_Compare(List const* list1, List const* list2);


////These two are probably the hardest functions in this exercise. I think that they'd be standard material for a second-year CS student at a decent uni. Have fun!

////C++ and pointer practice
//Splice the contents of source onto destination. What this means is do the following:
//Remove all nodes from sourceIndexStart to sourceIndexEnd on source,
//and then insert them in the same order at destIndex on destination.
//If sourceIndexEnd < sourceIndexStart, insert them in destination in reverse order.
void List_Splice(List* destination, unsigned int destIndex, List* source, unsigned int sourceIndexStart, unsigned int sourceIndexEnd);

////C++ and pointer practice
//Takes a pointer to a function that takes a Node const* as an argument, and returns true(nonzero) or false(zero).
//This function will then remove all nodes from the given list where the predicate returned false.
//It should return the number of nodes that were removed.
unsigned int List_RemoveIf(List* list, int(*predicate)(Node const*));
