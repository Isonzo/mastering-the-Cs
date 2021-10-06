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
	List* list = List_Alloc();
	int array[5] = {1, 4, 2, 3, 6};
	list = List_FromArray(array, 5);
	List_Insert(list, 7, 0);

	List_Print(list);
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
		new_node->next = NULL;
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
	if(!list) return false; //Is a non-existent list empty? I refer back to the conundrum of the sorted list
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
		new_node->next = NULL;
	}
	else
	{
		temp = list->last;
		temp->next = new_node;
		list->last = new_node;
	}
}

//Adds a node at the end of the list
bool List_PushBackBool(List* list, int value)
{
	if(!list) return false;
	Node* new_node;
	Node* temp;

	new_node = malloc(sizeof(Node));
	if(!new_node) return false;  //If malloc fails, don't try to add the node
	new_node->data = value;

	if (List_IsEmpty(list)) //If list is empty, assign first and last pointers
	{
		list->first = new_node;
		list->last = new_node;
		new_node->next = NULL;
	}
	else
	{
		temp = list->last;
		temp->next = new_node;
		list->last = new_node;
	}
	return true;
}

//It turns the array into a linked list. In goes array, out goes linked list.
List* List_FromArray(int const* array, unsigned int arrayLength)
{
	List* list = List_Alloc();
	unsigned int count = 0;

	while (count < arrayLength)
	{
		if (!List_PushBackBool(list, *(array + count))) // Modified Pushback that returns whether it was successful or not (handy!)
		{
			List_Free(&list);
			return NULL;
		}
		++count;
	}
	return list;
}

//Insert value at a certain index, assuming linked list is 0-indexed and has at least one value
void List_Insert(List* list, int value, unsigned int index) // TODO: test function
{
	if (!list) return;
	unsigned int list_count = List_Count(list);
	Node* new_node = malloc(sizeof(Node));
	if (!new_node) return;
	new_node->data = value;

	// If the index is bigger than the list, abort
	if (index > list_count)
		return;

	// If the node is at the beginning or end, let's just save ourselves the hassle
	if(index == 0)
	{
		new_node->next = list->first;
		list->first = new_node;
		return;
	}
	else if(index == list_count)
	{
		list->last->next = new_node;
		new_node->next = NULL;
		list->last = new_node;
		return;
	}
	// Since it's not the first or last, we make some variables to help us keep track and iterate through the list to insert
	Node* previous = list->first;
	Node* temp = previous->next;
	unsigned int count = 1; // starts at 1 since we already know it's not 0
	while (temp != NULL && count != index)
	{
		previous = temp;
		temp = temp->next;
		++count;
	}
	previous->next = new_node;
	new_node->next = temp;
	return;
}

//Insert a new item into the list. Assume the list is already sorted.
//Obviously, it should remain sorted after the insertion.
void List_SortedInsert(List* list, int value) // TODO: test function
{
	// Check if it should be first
	if (list->first->data >= value)
	{
		List_PushFront(list, value);
		return;
	}
	// Check if it is last, to skip everything and avoid pointer issues
	if (list->last->data <= value)
	{
		List_PushBack(list, value);
		return;
	}
	Node* temp = list->first;
	Node* prev = temp;
	Node* new_node;
	new_node = malloc(sizeof(Node));
	if (new_node) return;
	new_node->data = value;
	while (temp != NULL)
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
bool List_IsUnique(List const* list) // TODO: test function
{
	if (!list)
		return true;  // If it has no elements, they can't be duplicate, right?
	int list_count = List_Count(list);
	int* values_present = malloc(list_count * sizeof(int));
	Node* temp = list->first;
	int count = 0;

	while (temp != NULL)
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
void List_Remove(List* list, int value) // TODO: test function
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
void List_Free(List** list) // TODO: test function
{
	if (!list) return;
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
void List_Reverse(List* list) // TODO: test function
{
	if (!list) return;
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
List* List_Copy(List* list) // TODO: test function
{
	if (!list) return NULL;
	List* new_list;
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
			List_Free(&new_list);
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
void List_SwapNodes(List* list, unsigned int firstIndex, unsigned int secondIndex) // TODO: test function
{
	if (!list) return;
	if (firstIndex == secondIndex) return;
	if (firstIndex >= List_Count(list) || secondIndex >= List_Count(list)) return;
	Node* temp = list->first;
	Node* first;
	Node* second;
	unsigned int count = 0;
	while (temp != NULL || (first == NULL && second == NULL))
	{
		if (count == firstIndex)
			first = temp;
		else if (count == secondIndex)
			second = temp;
		temp = temp->next;
		++count;
	}
	// Commence the new and improved swap.
	int temp_data = first->data;
	first->data = second->data;
	second->data = temp_data;
	return;
}

////C++ practice
//Run the specified function for every node in the list.
void List_ForEach(List const* list, void(*fn)(Node const*)) // TODO: test function
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
void List_Transform(List* list, void(*fn)(Node*)) // TODO: test function
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
void List_Swap(List* list1, List* list2) // TODO: test function
{
	if (!list1 || !list2) return;
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
void List_Move(List* oldList, List* newList) // TODO: test function + leakylist
{
	if (!oldList || !newList) return;
	if (oldList == newList) return;
	List_Swap(oldList, newList);
	List_Free(&oldList);
}

////Pointer and general data structure practice
//Remove all duplicate items in the list, if any. Leave the first occurrence in the list.
void List_RemoveDuplicates(List* list) // TODO: test function
{
	if (!list) return;
	// Initialize an array
	int list_count = List_Count(list);
	int data_seen[list_count];
	int array_count = 0;
	for (int i = 0; i < list_count; ++i)
		data_seen[i] = INT_MIN;

	Node* temp = list->first;
	Node* prev;
	while (temp != NULL)
	{
		// Check if current node is in data_seen.
		for (int i = 0; i < list_count; ++i)
		{
			if(data_seen[i]== INT_MIN)
			{
				data_seen[array_count++] = temp->data;
				prev = temp;
				temp = temp->next;
				break;
			}
			else if (temp->data == data_seen[i])
			{
				prev->next = temp->next;
				free(temp);
				temp = prev->next;
				break;
			}
		}
	}
	return;
}

////Pointer practice
//Sort the contents of the list. It should contain the same notes, but in ascending order.
////I'm not concerned with the efficiency of the sort itself, but I do care about the efficiency that nodes are moved with.
////I recommend implementing a selection sort for this.
////DO NOT try to use your List_SwapNodes function!!
void List_Sort(List* list) // TODO: test function
{
	if (!list) return;
	Node* starting_point = list->first;
	Node* min_node;

	while (starting_point != NULL)
	{
		Node* temp = starting_point;
		min_node = temp;
		temp = temp->next;
		while (temp != NULL)
		{
			if (min_node->data > temp->data)
				min_node = temp;
			temp = temp->next;
		}
		Node * swap_node = starting_point;
		starting_point = starting_point->next;
		// Swappin' time
		int temp_data = swap_node->data;
		swap_node->data = min_node->data;
		min_node->data = temp_data;
	}
	return;
}

////Pointer practice
//Copy all the nodes from the "extra" list to the destination list.
//You may assume the destination list is already sorted.
//The destination list should remain sorted afterwards.
void List_Blend(List* destination, List const* extra) // TODO: test function
{
	Node* temp_extra = extra->first;
	while (temp_extra != NULL)
	{
		Node* temp = destination->first->next;
		Node* prev = destination->first;
		// This is to save time if the node is lower than the minimum or greater than the maximum.
		if (temp_extra->data <= destination->first->data)
		{
			List_PushFront(destination, temp_extra->data);
			temp_extra = temp_extra->next;
			continue;
		}
		else if (temp_extra->data >= destination->last->data)
		{
			List_PushBack(destination, temp_extra->data);
			temp_extra = temp_extra->next;
			continue;
		}
		while (temp != NULL)
		{
			if (temp->data >= temp_extra->data)
			{
				Node* new_node;
				new_node = malloc(sizeof(Node));
				if (!new_node) return;
				new_node->next = prev->next;
				prev->next = new_node;
				new_node->data = temp_extra->data;
				break;
			}
			prev = temp;
			temp = temp->next;
		}
		temp_extra = temp_extra->next;
	}
	return;
}

//Same as List_Blend, except the nodes from the extra list should be moved and not copied.
//The extra list should have no nodes on it afterward.
void List_Merge(List* destination, List* extra) // TODO: test function
{
	Node* temp_extra = extra->first;
	while (temp_extra != NULL)
	{
		Node* temp = destination->first->next;
		Node* prev = destination->first;
		// This is to save time if the node is lower than the minimum or greater than the maximum.
		if (temp_extra->data <= destination->first->data)
		{
			temp = temp_extra;
			temp_extra = temp_extra->next;
			temp->next = destination->first;
			destination->first = temp;
			continue;
		}
		else if (temp_extra->data >= destination->last->data)
		{
			destination->last->next = temp_extra;
			destination->last = temp_extra;
			temp_extra = temp_extra->next;
			continue;
		}
		while (temp != NULL)
		{
			if (temp->data >= temp_extra->data)
			{
				Node* extra_copy = temp_extra;
				temp_extra = temp_extra->next;
				prev->next = extra_copy;
				extra_copy->next = temp;
			}
			prev = temp;
			temp = temp->next;
		}
	}
	extra->first = NULL;
	extra->last = NULL;
	return;
}

////C++ practice
//Return the difference between the two lists.
//The return value for this should mimic the same pattern as strcmp() from the standard C library.
//For example, if the lists are identical you should return zero.
//If either list is null, return INT_MAX.
int List_Compare(List const* list1, List const* list2) // TODO: test function
{
	if (!list1 || !list2) return INT_MAX;

	int result = List_Sum(list1) - List_Sum(list2);
	return result;
}


////These two are probably the hardest functions in this exercise. I think that they'd be standard material for a second-year CS student at a decent uni. Have fun!

////C++ and pointer practice
//Splice the contents of source onto destination. What this means is do the following:
//Remove all nodes from sourceIndexStart to sourceIndexEnd on source,
//and then insert them in the same order at destIndex on destination.
//If sourceIndexEnd < sourceIndexStart, insert them in destination in reverse order.
void List_Splice(List* destination, unsigned int destIndex, List* source, unsigned int sourceIndexStart, unsigned int sourceIndexEnd) // TODO: test function
{
	if (!source || !destination) return; // Missing lists is a big no-no
	if (sourceIndexStart == sourceIndexEnd) return; // If they're the same, slice size is 0, no point in running program.
	Node* temp = source->first;
	Node* slice_first;
	Node* slice_last;
	Node* prev = NULL;
	Node* post = NULL;
	unsigned int count = 0;

	// Acquire donation from source, treat patient slightly different depending if reversed or not.
	if (sourceIndexStart < sourceIndexEnd)
	{
		while (temp != NULL)
		{
			if (count == sourceIndexStart - 1)
			{
				prev = temp;
				slice_first = temp->next;
				if (sourceIndexEnd >= List_Count(source) - 1) // Don't want users to accidentally overshoot it.
				{
					slice_last = source->last;
					break;
				}
			}
			else if (count == sourceIndexEnd)
			{
				slice_last = temp;
				post = temp->next;
				break;
			}
			temp = temp->next;
			count += 1;
		}
	}
	else
	{
		while (temp != NULL)
		{
			if (count == sourceIndexEnd - 1)
			{
				prev = temp;
				slice_first = temp->next;
				if (sourceIndexStart >= List_Count(source) - 1) // Same generosity as before.
				{
					slice_last = source->last;
					break;
				}
			}
			else if (count == sourceIndexStart)
			{
				slice_last = temp;
				post = temp->next;
				break;
			}
			temp = temp->next;
			count += 1;
		}
	}
	// Fix up source post-op, this makes sure pointers are in the correct place.
	if (prev)
		prev->next = post;
	else if (post)
		source->first = post;
	else
	{
		source->first = NULL;
		source->last = NULL;
	}

	// Do the transplant, but without using List_Insert (We have pointers!).
	temp = destination->first;
	count = 0;
	if (sourceIndexStart < sourceIndexEnd)
	{
		if (destIndex == 0)
		{
			destination->first = slice_first;
			slice_last->next = temp;
		}
		else if (destIndex >= List_Count(destination)) // Give a bit of lee-way, if it's above the maximum, put it at the end.
		{
			destination->last->next = slice_first;
			slice_last->next = NULL;
			destination->last = slice_last;
		}
		else
		{
			while (temp != NULL)
			{
				if (count == destIndex - 1) // Engaging insertion, temp is currently at node prev to slice.
				{
					Node* suture = temp->next;
					temp->next = slice_first;
					slice_last->next = suture; // And with this, the open wound we made is sealed.
					break;
				}
				count += 1;
				temp = temp->next;
			}
		}
	}
	else // Non-conforming splice, time to fix it up!
	{
		// Reverse Splice
		Node* before = NULL;
		Node* current = slice_first;
		Node* after = NULL;
		slice_last->next = NULL;

		while (current != NULL)
		{
			after = current->next;
			current->next = before;
			before = current;
			current = after;
		}
		temp = slice_last;
		slice_last = slice_first;
		slice_first = temp;
		temp = destination->first;
		if (destIndex == 0)
		{
			destination->first = slice_first;
			slice_last->next = temp;
		}
		else if (destIndex >= List_Count(destination)) // Give a bit of lee-way, if it's above the maximum, put it at the end.
		{
			destination->last->next = slice_first;
			slice_last->next = NULL;
			destination->last = slice_last;
		}
		else
		{
			while (temp != NULL)
			{
				if (count == destIndex - 1) // Engaging insertion, temp is currently at node prev to slice.
				{
					Node* suture = temp->next;
					temp->next = slice_first;
					slice_last->next = suture; // And with this, the open wound we made is sealed.
					break;
				}
				count += 1;
				temp = temp->next;
			}
		}
	}
	return;
}

////C++ and pointer practice
//Takes a pointer to a function that takes a Node const* as an argument, and returns true(nonzero) or false(zero).
//This function will then remove all nodes from the given list where the predicate returned false.
//It should return the number of nodes that were removed.
unsigned int List_RemoveIf(List* list, int(*predicate)(Node const*)) // TODO: test function
{
	if (!list) return 0;
	int removed_nodes = 0;
	Node* temp = list->first;
	Node* prev = NULL;

	while (temp != NULL)
	{
		if (predicate(temp))
		{
			if (prev == NULL)
			{
				list->first = temp->next;
				free(temp);
				temp = list->first;
				++removed_nodes;
				continue;
			}
			else
			{
				prev->next = temp->next;
				free(temp);
				temp = prev->next;
				++removed_nodes;
				continue;
			}
		}
		prev = temp;
		temp = temp->next;
	}
	return removed_nodes;
}
