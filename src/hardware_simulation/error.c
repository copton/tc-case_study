#include "error.h"
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

void errorExit(const char* what)
{
	int e = errno;
	fprintf(stderr, "%s failed: '%s'\n", what, strerror(e));
	exit(1);
}
