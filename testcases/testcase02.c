// Sean Szumlanski
// COP 3502, Fall 2017

// ========================
// SmartArray: testcase02.c
// ========================


#include <stdio.h>
#include "SmartArray.h"

int main(void)
{
	SmartArray *smarty = createSmartArray(-1);

	// Trim smart array. This should reduce its capacity to 0.
	trimSmartArray(smarty);

	// Trim again. This should produce no output since capacity is already 0.
	trimSmartArray(smarty);

	// Print the empty array.
	printSmartArray(smarty);
	printf("Size of array: %d\n", getSize(smarty));

	// Destroy smart array. Hopefully this won't segfault.
	smarty = destroySmartArray(smarty);

	// Print the empty array.
	printSmartArray(smarty);
	printf("Size of array: %d\n", getSize(smarty));

	// Since smarty has been destroyed and is now NULL, the put() function should
	// return NULL
	if (put(smarty, "Hello, world!\n") == NULL)
		printf("Awesome!\n");
	else
		printf("Not so awesome!\n");

	// Create new array and add strings to the end. Print out the strings we're
	// adding (to ensure put() is returning pointers to those strings).
	printf("%s\n", put(smarty = createSmartArray(-1), "Hello,"));
	printf("%s\n", put(smarty, "world!"));

	// Print smarty again.
	printf("SmartArray contents:\n");
	printSmartArray(smarty);

	smarty = destroySmartArray(smarty);

	return 0;
}
