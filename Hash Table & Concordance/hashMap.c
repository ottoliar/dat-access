#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "hashMap.h"



/*the first hashing function you can use*/
int stringHash1(char * str)
{
	int i;
	int r = 0;
	for (i = 0; str[i] != '\0'; i++)
		r += str[i];
	return r;
}

/*the second hashing function you can use*/
int stringHash2(char * str)
{
	int i;
	int r = 0;
	for (i = 0; str[i] != '\0'; i++)
		r += (i+1) * str[i]; /*the difference between stringHash1 and stringHash2 is on this line*/
	return r;
}

/* initialize the supplied hashMap struct*/
void _initMap (struct hashMap * ht, int tableSize)
{
	int index;
	if(ht == NULL)
		return;
	ht->table = (hashLink**)malloc(sizeof(hashLink*) * tableSize);
	ht->tableSize = tableSize;
	ht->count = 0;
	for(index = 0; index < tableSize; index++)
		ht->table[index] = NULL;
}

/* allocate memory and initialize a hash map*/
hashMap *createMap(int tableSize) {
	assert(tableSize > 0);
	hashMap *ht;
	ht = malloc(sizeof(hashMap));
	assert(ht != 0);
	_initMap(ht, tableSize);
	return ht;
}

/*
 Free all memory used by the buckets.
 Note: Before freeing up a hashLink, free the memory occupied by key and value
 */
void _freeMap (struct hashMap * ht)
{

	hashLink *temp1 = 0;
	hashLink *temp2 = 0;
	int i;

	//Free data, including values & key
	for (i = 0; i < ht->tableSize; i++)
    {
        if (ht->table[i] != 0)
        {
            //free link data, then move on to next link (if any)
            temp1 = &ht->table[i][0];
            temp2 = temp1->next;
            while (temp1 != 0)
            {
                temp2 = temp1->next;
                free(temp1->key);
                free(temp1);
                temp1 = temp2;
            }
        }
    }

    //Reset table
    free(ht->table);
    ht->tableSize = 0;
    ht->count = 0;
    

}

/* Deallocate buckets and the hash map.*/
void deleteMap(hashMap *ht) {
	assert(ht!= 0);
	/* Free all memory used by the buckets */
	_freeMap(ht);
	/* free the hashMap struct */
	free(ht);
}

/*
Resizes the hash table to be the size newTableSize
*/
void _setTableSize(struct hashMap * ht, int newTableSize)
{
	int old_size = ht->tableSize;
    struct hashLink **oldData = ht->table;
	int i;

	//Make a new table with 2x the capacity
	_initMap(ht, newTableSize);

	//Copy over old data
	for (i = 0; i < old_size; i++)
    {
        struct hashLink *cur = oldData[i];
        struct hashLink *next;
        while (cur != 0)
        {
            next = cur->next;
            insertMap(ht, cur->key, cur->value);
            free(cur);
            cur = next;
        }
    }

    //Free the old array of hashLinks
    free(oldData);
}

/*
 insert the following values into a hashLink, you must create this hashLink but
 only after you confirm that this key does not already exist in the table. For example, you
 cannot have two hashLinks for the word "taco".

 if a hashLink already exists in the table for the key provided you should
 replace that hashLink--this requires freeing up the old memory pointed by hashLink->value
 and then pointing hashLink->value to value v.

 also, you must monitor the load factor and resize when the load factor is greater than
 or equal LOAD_FACTOR_THRESHOLD (defined in hashMap.h).
 */
void insertMap (struct hashMap * ht, KeyType k, ValueType v)
{
    int keyIdx;

    //Compute index key will hash to
    if (HASHING_FUNCTION == 1)
    {
        keyIdx = stringHash1(k);
    }
    else if (HASHING_FUNCTION == 2)
    {
        keyIdx = stringHash2(k);
    }

    //Reduce key index to valid table index
    keyIdx %= ht->tableSize;

    //Ensure index is positive
    if (keyIdx < 0)
    {
        keyIdx += ht->tableSize;
    }


    //Check to see if there is the key already exists in the table
    if (containsKey(ht, k))
    {
        //Replace the hash link with the new value so the key now contains value v
        ht->table[keyIdx]->value = v;
    }
    else //Key is not in table; make a new link and add to the table
    {
        //Create new link to hold the information & set it's data
        hashLink * newLink = (hashLink *)malloc(sizeof(hashLink));
        newLink->key = (char *)malloc(128*sizeof(char *));
        assert(newLink != 0);
        strcpy(newLink->key, k);
        newLink->value = v;
        newLink->next = ht->table[keyIdx];

        //Add new link to table
        ht->table[keyIdx] = newLink;
        ht->count++;
    }

    //If we reach threshold, resize the table
    if (tableLoad(ht) >= LOAD_FACTOR_THRESHOLD)
    {
        _setTableSize(ht, ht->tableSize * 2);
    }
}

/*
 this returns the value (which is void*) stored in a hashLink specified by the key k.

 if the user supplies the key "taco" you should find taco in the hashTable, then
 return the value member of the hashLink that represents taco.

 if the supplied key is not in the hashtable return NULL.
 */
ValueType* atMap (struct hashMap * ht, KeyType k)
{
    int keyIdx;

    //Compute index key will hash to
    if (HASHING_FUNCTION == 1)
    {
        keyIdx = stringHash1(k);
    }
    else if (HASHING_FUNCTION == 2)
    {
        keyIdx = stringHash2(k);
    }

    //Reduce key index to valid table index
    keyIdx %= ht->tableSize;

    //Ensure index is positive
    if (keyIdx < 0)
    {
        keyIdx += ht->tableSize;
    }

    //Go to table at index
    hashLink * ptr = ht->table[keyIdx];

    //Check to see if a value is associated with the index
    while (ptr != 0)
    {
        if (strcmp(ptr->key, k) == 0)
        {
            //Return the address of value member if found
            return(&(ptr->value));
        }
        ptr = ptr->next;
    }

    //Return null if value is not found
    return 0;
}

/*
 a simple yes/no if the key is in the hashtable.
 0 is no, all other values are yes.
 */
int containsKey (struct hashMap * ht, KeyType k)
{
    int keyIdx;

    //Compute index key will hash to
    if (HASHING_FUNCTION == 1)
    {
        keyIdx = stringHash1(k);
    }
    else if (HASHING_FUNCTION == 2)
    {
        keyIdx = stringHash2(k);
    }

    //Reduce key index to valid table index
    keyIdx %= ht->tableSize;

    //Ensure index is positive
    if (keyIdx < 0)
    {
        keyIdx += ht->tableSize;
    }

    hashLink * ptr = ht->table[keyIdx];

    while (ptr != 0)
    {
        if (strcmp(ptr->key, k) == 0)
        {
            //Return 1 if key found
            return 1;
        }

        ptr = ptr->next;
    }

    //Return 0 if key not found
    return 0;
}

/*
 find the hashlink for the supplied key and remove it, also freeing the memory
 for that hashlink. it is not an error to be unable to find the hashlink, if it
 cannot be found do nothing (or print a message) but do not use an assert which
 will end your program.
 */
void removeKey (struct hashMap * ht, KeyType k)
{
    //Check to see if the key is present in the table
    //If so, remove it. Else, return.
    if (containsKey(ht, k))
    {
        int keyIdx;

        if (HASHING_FUNCTION == 1)
        {
            keyIdx = stringHash1(k);
        }
        else if (HASHING_FUNCTION == 2)
        {
            keyIdx = stringHash2(k);
        }

        //Convert index to valid table location
        keyIdx %= ht->tableSize;
        //Make sure it is positive
        if (keyIdx < 0)
            keyIdx += ht->tableSize;

        //Now find the key to be removed
        hashLink * ptr = ht->table[keyIdx];

        //Case 1: Parent link is the key to be removed
        if (strcmp(ptr->key, k) == 0)
        {
            hashLink *temp = ptr->next;
            free(ptr->key);
            free(ptr);
            ht->table[keyIdx] = temp;
            ht->count--;
            return;
        }

        //Case 2: Check child links of the bucket
        while (ptr->next != 0)
        {
            //If next one matches key to be removed, remove it and point to the next link
            if (strcmp(ptr->next->key, k) == 0)
            {
                hashLink *temp = ptr->next->next;
                free(ptr->next->key);
                free(ptr->next);
                ptr->next = temp;
                ht->count--;
                return;
            }
            ptr = ptr->next;
        }
    }
    else
    {
        printf("Key to be removed wasn't in the table!\n");
        return;
    }
}

/*
 returns the number of hashLinks in the table
 */
int size (struct hashMap *ht)
{
    assert (ht != 0);

    return (ht->count);
}

/*
 returns the number of buckets in the table
 */
int capacity(struct hashMap *ht)
{
    assert(ht != 0);

    return (ht->tableSize);
}

/*
 returns the number of empty buckets in the table, these are buckets which have
 no hashlinks hanging off of them.
 */
int emptyBuckets(struct hashMap *ht)
{
    assert(ht != 0);

    int count = 0;
    int i;

    for (i = 0; i < ht->tableSize; i++)
    {
        if (ht->table[i] == 0)
        {
            count++;
        }
    }

    return count;
}

/*
 returns the ratio of: (number of hashlinks) / (number of buckets)

 this value can range anywhere from zero (an empty table) to more then 1, which
 would mean that there are more hashlinks then buckets (but remember hashlinks
 are like linked list nodes so they can hang from each other)
 */
float tableLoad(struct hashMap *ht)
{
    assert (ht != 0);
    return (float)(ht->count) / (float)(ht->tableSize);
}

void printMap (struct hashMap * ht)
{
	int i;
	struct hashLink *temp;
    printf("\n--------Table Layout--------\n");
	for(i = 0;i < capacity(ht); i++){
		temp = ht->table[i];
		if(temp != 0) {
			printf("\nBucket Index %d -> ", i);
		}
		while(temp != 0){
			printf("Key:%s|", temp->key);
			printValue(temp->value);
			printf(" -> ");
			temp=temp->next;
		}
	}
    printf("\n----------------------------\n");

    printf("\n---------Word Count---------\n");
    for (i = 0; i < capacity(ht); i++)
    {
        temp = ht->table[i];
        if (temp != 0)
        {
            while (temp != 0)
            {
                printf("%s: %d\n", temp->key, temp->value);
                temp = temp->next;
            }
        }
    }
    printf("-----------------------------\n");
}


