
#include "myAssert.h"
#include <stdio.h>

int myAssert(int a, int b, int testDescriptor)
{
	if (a == b)
		return 0;
	else{
		printf("TEST FAILED!, %i\n", testDescriptor);
		return 1;
	}
}