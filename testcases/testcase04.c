// Sean Szumlanski
// COP 3502, Fall 2017

// ========================
// SmartArray: testcase04.c
// ========================
// Does this segfault for you? If so, you might be re-allocating your entire
// smarty array struct inside the expandSmartArray() function. Since there's no
// way to get that pointer back to smarty in main() via the put() function, you
// should ensure that your expandSmartArray() function only re-allocates the
// array *within* the smart array struct. (I.e., leave the struct intact, but
// stuff a new array inside of it.)


#include <stdio.h>
#include <string.h>
#include "SmartArray.h"

int main(void)
{
	int i; char myString[100], *temp;
	SmartArray *smarty = createSmartArray(10);

	// add some strings to the smart array
	for (i = 0; i < 30; i++)
	{
		// format my string
		sprintf(myString, "(string %02d)", i);

		// add string to end of smart array
		temp = put(smarty, myString);

		// print a little notification that the string was added
		printf("Added string: %s\n", temp);
	}

	// print out the contents of the smart array
	printSmartArray(smarty);

	return 0;
}
