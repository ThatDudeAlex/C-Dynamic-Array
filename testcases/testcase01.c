// Sean Szumlanski
// COP 3502, Fall 2017

// ========================
// SmartArray: testcase01.c
// ========================


#include <stdio.h>
#include <string.h>
#include "SmartArray.h"

int main(void)
{
	int i; char buffer[32];

	SmartArray *smarty1 = createSmartArray(-1);
	SmartArray *smarty2 = createSmartArray(-1);

	FILE *ifp = fopen("names.txt", "rb");

	// Read all names from the file and add them to smarty1.
	while (fscanf(ifp, "%s", buffer) != EOF)
		put(smarty1, buffer);

	// Add the names to smarty2 in reverse order.
	for (i = getSize(smarty1) - 1; i >= 0; i--)
		put(smarty2, get(smarty1, i));

	// Print the contents of smarty1.
	printf("\n-- SMART ARRAY 1: --\n");
	printSmartArray(smarty1);

	// Print the contents of smarty2.
	printf("\n-- SMART ARRAY 2 (First Names): --\n");
	printSmartArray(smarty2);

	// Swap last names with first names in smarty2.
	for (i = 0; i < getSize(smarty2); i++)
	{
		if (strcmp(get(smarty2, i), "Daniel") == 0)
			set(smarty2, i, "Mandragona");
		else if (strcmp(get(smarty2, i), "Kristjan") == 0)
			set(smarty2, i, "Arumae");
		else if (strcmp(get(smarty2, i), "Karan") == 0)
			set(smarty2, i, "Daei-Mojdehi");
		else if (strcmp(get(smarty2, i), "Shahidul") == 0)
			set(smarty2, i, "Islam");
		else if (strcmp(get(smarty2, i), "Fereshteh") == 0)
			set(smarty2, i, "Jafariakinabad");
		else if (strcmp(get(smarty2, i), "Pierre") == 0)
			set(smarty2, i, "LaBorde");
		else if (strcmp(get(smarty2, i), "Rachael") == 0)
			set(smarty2, i, "Sera");
		else if (strcmp(get(smarty2, i), "Richie") == 0)
			set(smarty2, i, "Wales");
	}

	// Print the contents of smarty2.
	printf("\n-- SMART ARRAY 2 (Last Names): --\n");
	printSmartArray(smarty2);

	// Print smarty1 (in reverse order) and smarty2, to match up first and last
	// names.
	printf("\n-- COMBINED ARRAYS (First and Last Names): --\n");
	for (i = 0; i < getSize(smarty2); i++)
		printf("%s %s\n", get(smarty1, getSize(smarty1) - 1 - i), get(smarty2, i));

	// Add elements from smarty1 to the end of smarty1 (in reverse order).
	printf("\n");
	for (i = getSize(smarty1) - 1; i >= 0; i--)
		printf("Adding %s to smarty1 ...\n", put(smarty1, get(smarty1, i)));

	// Print the contents of smarty1.
	printf("\n-- SMART ARRAY 1: --\n");
	printSmartArray(smarty1);

	// Insert a string at the beginning of array smarty1.
	insertElement(smarty1, 0, "List of Names:");

	// Print the contents of smarty1.
	printf("\n-- SMART ARRAY 1: --\n");
	printSmartArray(smarty1);

	// Remove all elements from smarty1.
	while (getSize(smarty1))
		removeElement(smarty1, 0);

	// Print smarty1, which is now an empty array.
	printf("\n-- SMART ARRAY 1: --\n");
	printSmartArray(smarty1);

	// Destroy our smart arrays.
	smarty1 = destroySmartArray(smarty1);
	smarty2 = destroySmartArray(smarty2);

	// Make sure smarty1 is good and destroyed (and that destroySmartArray
	// doesn't segfault when passed a NULL pointer).
	smarty1 = destroySmartArray(smarty1);

	// Print the empty arrays one last time.
	printf("\n-- SMART ARRAY 1: --\n");
	printSmartArray(smarty1);

	printf("\n-- SMART ARRAY 2: --\n");
	printSmartArray(smarty2);

	return 0;
}
