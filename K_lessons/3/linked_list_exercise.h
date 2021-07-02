////I didn't try compiling this before sending it to you, so you may need to correct a stray semicolon or missing #include somewhere.
////This exercise is designed to take some time to complete. I advise you to work on it over the course of several days.
////I strongly advise you to write your own test cases and try to cover as many bases as you can.
////I will test your code myself when it's done, as well as evaluate it for quality and efficiency.
////If any of your implementations are too naive or too slow I may ask you to do them over.

////Finally, there are some style requirements:
////You must document all headers you include as shown in this example, listing every function you use from that header.
////You must follow the naming convention for structs and functions provided. If you implement any helper functions they should also follow this format.
////All functions require at minimum one comment explaining what they do. I've documented the required ones for you already.
////All functions must be const-correct.
////You are not allowed to use any global or static variables for any reason. Local function variables only.

////This won't be painless but I think you will find it transformative.
////As always you can ask me for help on anything! <3

#include <stdlib.h> //calloc

typedef struct
{
	Node* next;
	int data;
} Node;

typedef struct
{
	Node* first;
	Node* last;
} List;

//Prints the contents of a list.
//args:
//    - List:
//        The list to print.
void List_Print(List const* list)
{
	//no list supplied
	if(!list) return;
	
	Node* current = list->first;
	int count = 0;
	while(current)
	{
		printf("============\n");
		printf("Node #%d\n", ++count);
		printf("Data: %d", current->data);
		current = current->next;
	}
}


//Creates a new dynamically-allocated list.
//The first and last pointers will be defaulted to NULL.
List* List_Alloc()
{
	return calloc(1, sizeof(List));
}


////You have to implement these////
////Place the implementations in a separate C file////
////I STRONGLY STRONGLY recommend going in order ////

////If the input list is NULL for any of these functions, do nothing or return -1 (unless otherwise specified).////

//Pushes a new value to the front of a list.
//i.e. if the list was 1->2->6 and you pushed a 9 to the front, it should then be 9->1->2->6.
//Note the input is not const because you should be modifying the list.
void List_PushFront(List* list, int value);

//Return the number of nodes in the list.
////Note that the input is const because you should not be modifying the list.
unsigned int List_Count(List const* list);

//Returns the sum of all nodes in a list
int List_Sum(List const* list);

//Return true if the nodes in the list are in sorted (ascending) order.
bool List_IsSorted(List const* list);

//Return true if the list is empty (no nodes).
bool List_IsEmpty(List const* list);

//Like PushFront, but should be added to the end instead.
void List_PushBack(List* list, int value);

//Create a new list (use List_Alloc) from a given array of integers.
//The list should contain the same elements as the array in the same order.
//Return NULL if this fails for any reason.
List* List_FromArray(int const* array, unsigned int arrayLength);

////Don't forget to maintain the first and last pointers!////

//Insert a new item into the list at the specified index.
//It should be inserted so that the specified index is the index of the new entry. i.e. index of 0 should have identical behavior to push_front.
//If the index would be invalid for the list (i.e. it is beyond the end- such as index 2 in a list with 1 node), do nothing.
void List_Insert(List* list, int value, unsigned int index);

//Insert a new item into the list. Assume the list is already sorted.
//Obviously, it should remain sorted after the insertion.
void List_SortedInsert(List* list, int value);

//Returns true if the list has no duplicate elements (i.e. all elements are unique).
bool List_IsUnique(List const* list);

//Remove the first node in the list that has the specified value. If such a node does not exist, do nothing.
void List_Remove(List* list, int value);

//Free the list and its contents from memory, then set the pointer to it to NULL.
void List_Free(List** list);

//Reverse the order of nodes in the list
void List_Reverse(List* list);

////This is the hardest one I'm going to "require"
//Create a new list with the same contents in the same order as the input list and return it.
//If this fails for any reason, return NULL.
//If this fails due to malloc failing, you must also clean up any allocated memory before returning.
List* List_Copy(List* list);



/////////////////////////
/////////////////////////
////////EXTRA CREDIT/////
/////////////////////////
/////////////////////////


////Everything beyond this point is "extra credit"- hard or unusual problems that I think you would find interesting
////These are good if you want to really grow your abilities and become completely comfortable with pointers and data manipulation
////They also will give you some useful context if you ever delve into C++.

////Pointer practice
//Swap the position of the nodes located at the two indices in the given list.
void List_SwapNodes(List* list, unsigned int firstIndex, unsigned int secondIndex);

////C++ practice
//Run the specified function for every node in the list.
void List_ForEach(List const* list, void(*fn)(Node const*));

////C++ practice
//Same as above but non-const. Do NOT try to reuse code between these two functions.
void List_Transform(List* list, void(*fn)(Node*));

////C++ practice
//Replace the contents of list1 with the contents of list2, and vice versa.
void List_Swap(List* list1, List* list2);

////C++ practice
//Clear the list stored at newList, and move the contents of oldList there.
//The fate of oldList is irrelevant. You may leave it in a garbage state if you wish.
////Hint: There's a very bad and slow way to do this, and a very nice and fast way.
////Hint 2: Don't forget the user might surprise you with their inputs...
void List_Move(List* oldList, List* newList);

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
