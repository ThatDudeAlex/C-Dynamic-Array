#ifndef __SMART_ARRAY_H
#define __SMART_ARRAY_H

// Default capacity for new SmartArrays
#define DEFAULT_INIT_LEN 10

typedef struct SmartArray
{
	// We will store an array of strings (i.e., an array of char arrays)
	char **array;

	// Size of array (i.e., number of elements that have been added to the array)
	int size;

	// Length of the array (i.e., the array's current maximum capacity)
	int capacity;

} SmartArray;


// Functional Prototypes

SmartArray *createSmartArray(int length);

SmartArray *destroySmartArray(SmartArray *smarty);

SmartArray *expandSmartArray(SmartArray *smarty, int length);

SmartArray *trimSmartArray(SmartArray *smarty);

char *put(SmartArray *smarty, char *str);

char *get(SmartArray *smarty, int index);

char *set(SmartArray *smarty, int index, char *str);

char *insertElement(SmartArray *smarty, int index, char *str);

int removeElement(SmartArray *smarty, int index);

int getSize(SmartArray *smarty);

void printSmartArray(SmartArray *smarty);

double difficultyRating(void);

double hoursSpent(void);


#endif
