// Sean Szumlanski
// COP 3502, Fall 2017

// ========================
// SmartArray: testcase03.c
// ========================


#include <stdio.h>
#include "SmartArray.h"

void nullAssert(void *ptr, char *s)
{
	if (ptr != NULL)
		printf("ERROR: %s failed to return NULL as required.\n", s);
}

int main(void)
{
	char *str = NULL;

	SmartArray *smarty1 = createSmartArray(0);
	SmartArray *smarty2 = NULL;

	smarty2 = destroySmartArray(NULL);
	nullAssert(smarty2, "destroySmartArray()");

	str = put(smarty1, NULL);
	nullAssert(str, "put()");

	str = get(NULL, -1);
	nullAssert(str, "get() (1/2)");

	str = get(smarty1, -1);
	nullAssert(str, "get() (2/2)");

	return 0;
}
