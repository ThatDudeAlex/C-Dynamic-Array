// Jose Nunez

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "SmartArray.h"

// Dynamically allocates space for a new SmartArray
SmartArray *createSmartArray(int length)
{
    // Create a pointer to our SmartArray struct and set it to NULL
    // before Dynamically allocating memory for it.
    int i;
    SmartArray *smarty = NULL;

    smarty = malloc(sizeof(SmartArray));

    // if smarty fails to allocate memory and it stays the same
    // return NULL
    if(smarty == NULL)
        return NULL;

    // Since its a new array it has 0 elements so by default
    // size = 0
    smarty->size = 0;

    // Checks to see if the length passed into the function is greater than
    // our default length, if it is then Array capacity = length, else we
    // use our default size of 10
    if(length > DEFAULT_INIT_LEN)
		     smarty->capacity = length;
    else
        smarty->capacity = DEFAULT_INIT_LEN;

    // Dynamically allocate the required memory for our array
    // based on our capacity;
    smarty->array = malloc(sizeof(char *) * smarty->capacity);

    // Initialize every slot in the array to NUll
    for(i =0; i < smarty->capacity; i++)
        smarty->array[i] = NULL;

    printf("-> Created new SmartArray of size %d.\n", smarty->capacity);

    return smarty;
}

// Frees any Dynamically allocated memory associated with the SmartArray struct
SmartArray *destroySmartArray(SmartArray *smarty)
{
    int i;

    // checks to see if smarty pointer we recieved is NULL, and just
    // return NULL if it is
    if(smarty == NULL)
      return NULL;

    // start at the last element in our array and start freeing them
    // from from last to first.
    for(i = getSize(smarty) - 1; i >= 0; i--)
        free(smarty->array[i]);

    free(smarty);
	  return NULL;
}

// Expands our existing array by creating a new Array of the specify lenght
// so long as length is greater than our current capacity, and Copying everything
// from the old Array into our new Array.
SmartArray *expandSmartArray(SmartArray *smarty, int length)
{
    char **newArray = NULL;
    int i;

    // if the lenght passed in is smaller than our current capacity or smarty
    // is NULL, there's nothing to do so just return NULL.
    if(length <= smarty->capacity || smarty == NULL)
        return NULL;

    // Dynamically allocate memory for our newArray and then checks to see if it
    // allocated correctly, and if a problem happenned while allocating return NULL
    newArray = malloc(sizeof(char *) * length);
    if(newArray == NULL)
      return NULL;

    // runs through the entire lenght of our old Array and copies everything
    // into our new Array.
    for(i = 0; i < smarty->capacity; i++)
        newArray[i] = smarty->array[i];

    // Initializes all the new slots that we expanded into our
    // new Array to NULL
    for(i = smarty->capacity; i < length; i++)
        newArray[i] = NULL;

    // frees any memory associated with our old Array, and then we make smarty point
    // towards our new Array, and set our new Array capacity to be equal to lenght
    free(smarty->array);
    smarty->array = newArray;
    smarty->capacity = length;

    printf("-> Expanded SmartArray to size %d.\n", smarty->capacity);

    return smarty;
}

// If our array capacity is bigger than our size, trims the array capacity to
// equal its size.
SmartArray *trimSmartArray(SmartArray *smarty)
{
  char **newArray = NULL;
  int i;

  // checks to see if smarty is NULL or if our capacity is 0, if it is there's
  // nothing to do so just return NULL.
  if(smarty == NULL || smarty->capacity == 0)
    return NULL;

  // checks to see if our capacity is greater than our size, and if it is we trim,
  // otherwise we do nothing
  if(smarty->capacity > getSize(smarty))
  {
    // Dynamically allocate memory for our new Array based on the number of
    // elements in our old Array, and then checks to see if it allocated
    // correctly, and if a problem happenned while allocating return NULL
    newArray = malloc(sizeof(char *) * getSize(smarty));
    if(newArray == NULL)
      return NULL;

    // runs through all the elements in our old Array and copy them in our new
    // Array
    for(i = 0; i < getSize(smarty); i++)
      newArray[i] = smarty->array[i];

    // set our Array capacity to equal its size, and then we free our old Array
    // and make smarty point towards our new Array
    smarty->capacity = getSize(smarty);
    free(smarty->array);
    smarty->array = newArray;

    printf("-> Trimmed SmartArray to size %d.\n", smarty->capacity);
  }

	return smarty;
}

// inserts a string into the first unused cell in our Array
char *put(SmartArray *smarty, char *str)
{
    int  stringLenght = 0, i;
    char *strAddress = NULL;

    // checks to see if smarty or str are equal to NULL, and if so there's
    // nothing to do so just return NULL.
    if(smarty == NULL || str == NULL)
      return NULL;

    // obtains the number of characters in str and Dynamically allocates memory
    // for strAddress based on that.
    stringLenght = strlen(str) + 1;
    strAddress = malloc(sizeof(char) * stringLenght);

    // checks to see if strAddress allocated memory correctly, and if
    // a problem happenned while allocating return NULL
    if(strAddress == NULL)
      return NULL;


    // checks to see if our Array is full, and if it is calls expandSmartArray()
    // before we can put anything into the Array
    if(smarty->size == smarty->capacity)
       expandSmartArray(smarty, smarty->capacity * 2 + 1);

    // we know that the next empty index in our array is equal to our array size
    // so we can just copy str in that spot in our array.
    if(smarty->array[getSize(smarty)] == NULL)
    {
      smarty->array[getSize(smarty)] = strcpy(strAddress, str);
      smarty->size += 1;
    }

	return strAddress;
}

// Returns a pointer to a specify index in the Array
char *get(SmartArray *smarty, int index)
{
  // checks to see if smarty equals NULL or if the index passed in is out of
  // bounds, and if they are return NULL.
  if(smarty == NULL || index < 0 || index >= smarty->capacity)
    return NULL;

	return smarty->array[index];
}

// replace a valid string index in our array with a copy of str, and Returns
// a pointer to the copy of str in our array
char *set(SmartArray *smarty, int index, char *str)
{
  int strLenght = strlen(str) + 1;
  char *newString = NULL;

  // checks to see if smarty or str are NULL, or if the index is out of bounds
  // and if they are just return NULL.
  if(smarty == NULL || str == NULL || index < 0 || index >= smarty->capacity)
    return NULL;

  // checks to see if the index in our array is valid, and if not returns NULL
  if(smarty->array[index] == NULL)
    return NULL;

  newString = malloc(sizeof(char *) * strLenght);

  // checks to see if a problemed happenned while allocating memory for newString
  // and if there was return NULL
  if(newString == NULL )
    return NULL;

  // frees the specify index in our array, and then we replace it with a copy
  // of the new string.
  free(smarty->array[index]);
  smarty->array[index] = strcpy(newString,str);

	return smarty->array[index];
}

// inserts a copy of a string at a specify index in the array and returns a
// pointer to the copy of the string in our array.
char *insertElement(SmartArray *smarty, int index, char *str)
{
  char *newString = NULL, **newArray = NULL;
  int stringLenght, i;

  // checks to see if smarty or str are NULL, or if the index is out of bounds,
  // if they are return NULL.
  if(smarty == NULL || str == NULL || index < 0 || index >= smarty->capacity)
    return NULL;
  // checks to see if the index is greater than the size of the array and if
  // it is, we can just use the put() function.
  else if(index > smarty->size)
    put(smarty,str);
  // checks to see if our array is full, and if it is we call expandSmartArray()
  // before inserting anything
  else if(smarty->size == smarty->capacity)
    expandSmartArray(smarty,smarty->capacity * 2 + 1);

    // obtains the required lenght we need to allocate for our new stringLenght
    // and then allocate memory for our new Array and string.
    stringLenght = strlen(str) + 1;
    newArray = malloc(sizeof(char *) * smarty->capacity);
    newString = malloc(sizeof(char *) * stringLenght);

    // checks to see if malloc failed for either newArray or newString and
    // if it did, we return NULL
    if(newArray == NULL || newString == NULL)
      return NULL;

    // copy everything from our old Array before the index into our new Array
    for(i = 0; i < index; i++)
      newArray[i] = smarty->array[i];

    // set the specify index in our new Array to be the new string
    newArray[index] = strcpy(newString,str);

    // after copying in str into our new array, if we still need to copy more
    // from the old array, we continue copying the remaining elements
    for(i = index + 1; i < smarty->capacity; i++)
      newArray[i] = smarty->array[i - 1];

    // increase the size of the array by 1, and then free the old array and
    // point towards our new one
    smarty->size += 1;
    free(smarty->array);
    smarty->array = newArray;

	  return newString;
}

// removes and element in our array and returns 1 if successful, 0 otherwise
int removeElement(SmartArray *smarty, int index)
{
  char ** newArray = NULL;
  int i;

  // checks to see if smarty is NULL, or if our array is empty and if they are
  // we return 0.
  if(smarty == NULL || smarty->size == 0)
    return 0;

  // checks to see if the index passed in, is out of bounds and if it is
  // we return 0.
  if(index < 0 || index >= smarty->capacity || index > smarty->size)
    return 0;

  // Dynamically allocate memory for our new Array, and we allocate memory
  // of equal size to our old Array.
  newArray = malloc(sizeof(char *) * smarty->capacity);

  // checks to see if a problemed occurred while allocating memory to the new
  // Array, and there was we return 0
  if(newArray == NULL)
    return 0;

  // if the index we are removing from our array is the first one, we remove
  // this way.
  if(index == 0)
  {
    // run a loop up to the second to last cell in our new Array, and then we
    // start copying elements of the old Array into the new one, after skipping
    // the first cell of the old Array.
    for(i = 0; i < smarty->capacity - 2; i++)
      newArray[i] = smarty->array[i + 1];

    // we make the last cell of our array be NUll
    newArray[smarty->capacity - 1] = NULL;
  }

  // if the index we are removing from our array is the last one, we remove it
  // this way.
  else if(index == smarty->capacity - 1)
  {
    // we copy everything before the last cell of our old array, into our
    // new Array.
    for(i = 0; i < index; i++)
      newArray[i] = smarty->array[i];

    // and then we just set the last cell of our new Array to NULL
    newArray[index] = NULL;
  }

  // else if the index we are removing is in between both ends of the
  // Array we remove it this way.
  else
  {
    // we copy everything before the specify index of our old array, into our
    // new Array.
    for(i = 0; i < index; i++)
      newArray[i] = smarty->array[i];

    // we skip the specify index in our Array, and then start copying everything
    // afterwards in our new Array
    for(i = index; i < smarty->capacity - 1; i++)
      newArray[i] = smarty->array[i + 1];

    // we set the last index in the Array to NUll.
    newArray[smarty->capacity - 1] = NULL;
  }

  // decrease the size of the array by 1, and then we free our old array and
  // point towards our new one.
  smarty->size -= 1;
  free(smarty->array);
  smarty->array = newArray;

	return 1;
}

// returns the number of elements in our array
int getSize(SmartArray *smarty)
{
  // checks to see if smarty is NULL and if it is return NULL
  if(smarty == NULL)
    return -1;

	return smarty->size;
}

// prints out our entire Array
void printSmartArray(SmartArray *smarty)
{
	int i;

  // checks to see if smarty is NULL or if our array is empty, and if they are
  // print empty array, else runs through the array and print everything
  if(smarty == NULL || smarty->size == 0)
  {
    printf("(empty array)\n");
  }
  else
  {
      for(i = 0; i < smarty->size; i++)
      {
        printf("%s\n", smarty->array[i]);
      }
  }
}

// returns difficulty rating
double difficultyRating(void)
{
	return 3.5;
}

// returns amounts of hours i worked on this.
double hoursSpent(void)
{
	return 11.0;
}
