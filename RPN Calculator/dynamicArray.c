/*	dynamicArray.c: Dynamic Array implementation. */
#include <assert.h>
#include <stdlib.h>
#include "dynamicArray.h"

struct DynArr
{
	TYPE *data;		/* pointer to the data array */
	int size;		/* Number of elements in the array */
	int capacity;	/* capacity ofthe array */
};


/* ************************************************************************
	Dynamic Array Functions
************************************************************************ */

/* Initialize (including allocation of data array) dynamic array.

	param: 	v		pointer to the dynamic array
	param:	cap 	capacity of the dynamic array
	pre:	v is not null
	post:	internal data array can hold cap elements
	post:	v->data is not null
*/
void initDynArr(DynArr *v, int  capacity)
{
	assert(capacity > 0);
	assert(v!= 0);
	v->data = (TYPE *) malloc(sizeof(TYPE) * capacity);
	assert(v->data != 0);
	v->size = 0;
	v->capacity = capacity;
}

/* Allocate and initialize dynamic array.

	param:	cap 	desired capacity for the dyn array
	pre:	none
	post:	none
	ret:	a non-null pointer to a dynArr of cap capacity
			and 0 elements in it.
*/
DynArr* createDynArr(int cap)
{
	assert(cap > 0);
	DynArr *r = (DynArr *)malloc(sizeof( DynArr));
	assert(r != 0);
	initDynArr(r, cap);
	return r;
}

/* Deallocate data array in dynamic array.

	param: 	v		pointer to the dynamic array
	pre:	none
	post:	d.data points to null
	post:	size and capacity are 0
	post:	the memory used by v->data is freed
*/
void freeDynArr(DynArr *v)
{
	if(v->data != 0)
	{
		free(v->data); 	/* free the space on the heap */
		v->data = 0;   	/* make it point to null */
	}
	v->size = 0;
	v->capacity = 0;
}

/* Deallocate data array and the dynamic array ure.

	param: 	v		pointer to the dynamic array
	pre:	none
	post:	the memory used by v->data is freed
	post:	the memory used by d is freed
*/
void deleteDynArr(DynArr *v)
{
	freeDynArr(v);
	free(v);
}

/* Resizes the underlying array to be the size cap

	param: 	v		pointer to the dynamic array
	param:	cap		the new desired capacity
	pre:	v is not null
	post:	v has capacity newCap
*/
void _dynArrSetCapacity(DynArr *v, int newCap)
{

	//Create a new array with new cap
	DynArr* newArr = createDynArr(newCap);
	//Assert new array is not null
	assert(newArr != 0);

	//copy the data to new array
	for(unsigned int i = 0; i < sizeDynArr(v); ++i)
    {
        addDynArr(newArr, v->data[i]);
    }
    //free the old DynArr
    freeDynArr(v);

	//Set the new capacity & size
	v->capacity = newCap;
	v->size = newArr->size;

    //Point to the newly created array
    v->data = newArr->data;


}

/* Get the size of the dynamic array

	param: 	v		pointer to the dynamic array
	pre:	v is not null
	post:	none
	ret:	the size of the dynamic array
*/
int sizeDynArr(DynArr *v)
{
	return v->size;
}

/* 	Adds an element to the end of the dynamic array

	param: 	v		pointer to the dynamic array
	param:	val		the value to add to the end of the dynamic array
	pre:	the dynArray is not null
	post:	size increases by 1
	post:	if reached capacity, capacity is doubled
	post:	val is in the last utilized position in the array
*/
void addDynArr(DynArr *v, TYPE val)
{

	assert(v != 0);

	//If max capacity is reached, a new array will have to be created
	if (sizeDynArr(v) >= v->capacity)
	{
        _dynArrSetCapacity(v, 2 * v->capacity);
	}

    //Add new data to the end and increase the size
    v->data[sizeDynArr(v)] = val;
    v->size++;

}

/*	Get an element from the dynamic array from a specified position

	param: 	v		pointer to the dynamic array
	param:	pos		integer index to get the element from
	pre:	v is not null
	pre:	v is not empty
	pre:	pos < size of the dyn array and >= 0
	post:	no changes to the dyn Array
	ret:	value stored at index pos
*/

TYPE getDynArr(DynArr *v, int pos)
{

	//Assert v is not pointing to NULL & is not empty
	assert(v != 0);
    assert(!isEmptyDynArr(v));
	//Assert position is valid in the array
	assert(pos >= 0 && pos < sizeDynArr(v));

	//Return the data at the requested position
	return v->data[pos];
}

/*	Put an item into the dynamic array at the specified location,
	overwriting the element that was there

	param: 	v		pointer to the dynamic array
	param:	pos		the index to put the value into
	param:	val		the value to insert
	pre:	v is not null
	pre:	v is not empty
	pre:	pos >= 0 and pos < size of the array
	post:	index pos contains new value, val
*/
void putDynArr(DynArr *v, int pos, TYPE val)
{

	//Assert v is not pointing to NULL & is not empty
	assert(v != 0);
	assert(!isEmptyDynArr(v));
	//Assert position is valid in the array
	assert(pos >= 0 && pos < sizeDynArr(v));

	//Place the value into the array at specific position
	v->data[pos] = val;
}

/*	Swap two specified elements in the dynamic array

	param: 	v		pointer to the dynamic array
	param:	i,j		the elements to be swapped
	pre:	v is not null
	pre:	v is not empty
	pre:	i, j >= 0 and i,j < size of the dynamic array
	post:	index i now holds the value at j and index j now holds the value at i
*/
void swapDynArr(DynArr *v, int i, int  j)
{

	//Assert v is not pointing to NULL & is not empty
	assert(v != 0);
	assert(!isEmptyDynArr(v));
	//Assert passed integers are valid
	assert(i >= 0 && j >= 0);
	assert(i < sizeDynArr(v) && j < sizeDynArr(v));

	//Get values at specified positions
	TYPE x = getDynArr(v, i);
	TYPE y = getDynArr(v, j);

	//Swap them
	putDynArr(v, i, y);
	putDynArr(v, j, x);
}

/*	Remove the element at the specified location from the array,
	shifts other elements back one to fill the gap

	param: 	v		pointer to the dynamic array
	param:	idx		location of element to remove
	pre:	v is not null
	pre:	v is not empty
	pre:	idx < size and idx >= 0
	post:	the element at idx is removed
	post:	the elements past idx are moved back one
*/
void removeAtDynArr(DynArr *v, int idx)
{

	//Assert v is not pointing to NULL & is not empty
	assert(v != 0);
	assert(!isEmptyDynArr(v));
	//Assert passed index is valid
	assert(idx < sizeDynArr(v) && idx >= 0);

	for (unsigned int i = idx; i < sizeDynArr(v) - 1; ++i)
	{
		v->data[i] = v->data[i + 1];
	}

	v->size--;
}

/* ************************************************************************
	Stack Interface Functions
************************************************************************ */

/*	Returns boolean (encoded in an int) demonstrating whether or not the
	dynamic array stack has an item on it.

	param:	v		pointer to the dynamic array
	pre:	the dynArr is not null
	post:	none
	ret:	1 if empty, otherwise 0
*/
int isEmptyDynArr(DynArr *v)
{

	//Assert v is not pointing to NULL
	assert(v != 0);

	return(sizeDynArr(v) == 0);

}

/* 	Push an element onto the top of the stack

	param:	v		pointer to the dynamic array
	param:	val		the value to push onto the stack
	pre:	v is not null
	post:	size increases by 1
			if reached capacity, capacity is doubled
			val is on the top of the stack
*/
void pushDynArr(DynArr *v, TYPE val)
{

	//Assert v is not pointing to NULL
	assert(v != 0);

	addDynArr(v, val);
}

/*	Returns the element at the top of the stack

	param:	v		pointer to the dynamic array
	pre:	v is not null
	pre:	v is not empty
	post:	no changes to the stack
*/
TYPE topDynArr(DynArr *v)
{

	//Assert v is not null & not empty
	assert(v != 0 && !isEmptyDynArr(v));

	//Get & return value at the top of the stack
	return getDynArr(v, sizeDynArr(v) - 1);
}

/* Removes the element on top of the stack

	param:	v		pointer to the dynamic array
	pre:	v is not null
	pre:	v is not empty
	post:	size is decremented by 1
			the top has been removed
*/
void popDynArr(DynArr *v)
{

	//Assert v is not null & is not empty
	assert(v != 0 && !isEmptyDynArr(v));

	//Remove the value at the top of the stack
	removeAtDynArr(v, sizeDynArr(v) - 1);
}

/* ************************************************************************
	Bag Interface Functions
************************************************************************ */

/*	Returns boolean (encoded as an int) demonstrating whether or not
	the specified value is in the collection
	true = 1
	false = 0

	param:	v		pointer to the dynamic array
	param:	val		the value to look for in the bag
	pre:	v is not null
	pre:	v is not empty
	post:	no changes to the bag
*/
int containsDynArr(DynArr *v, TYPE val)
{

	//Assert v is not null & not empty
	assert(v != 0 && !isEmptyDynArr(v));

	//Search the array for the passed value
	//Return 1 if found, 0 if not
	for (unsigned int i = 0; i < sizeDynArr(v); ++i)
	{
		if (EQ(v->data[i], val))
			return 1;
	}

	return 0;

}

/*	Removes the first occurrence of the specified value from the collection
	if it occurs

	param:	v		pointer to the dynamic array
	param:	val		the value to remove from the array
	pre:	v is not null
	pre:	v is not empty
	post:	val has been removed
	post:	size of the bag is reduced by 1
*/
void removeDynArr(DynArr *v, TYPE val)
{

	//Assert v is not null & v is not empty
	assert(v != 0 && !isEmptyDynArr(v));

	//Search the array for the specified value
	int position = -1;
	int index = 0;
	int found = 0;

	while (index < sizeDynArr(v) && found == 0)
	{
		if (EQ(val, v->data[index]))
		{
			position = index;
			found = 1;
		}
		index++;
	}

	if (position == -1)
	{
		return;
	}
	else
	{
		removeAtDynArr(v, position);
	}
}
