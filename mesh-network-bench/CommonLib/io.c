#include <stdio.h>
#include "io.h"
#include "debug.h"

int GetInput (char * output, char * buffer)
{
	int return_status = IO_PASS;
	char * result;

	printf(">%s\n", output);
	result = gets(buffer);
	if (buffer != result)
	{
		return_status = IO_FAIL;
		DBG(0, "Failed to retrieve input.")
	}

	return return_status;
}

void DisplayHelp (void)
{
	printf(">-e: To exit.\n");
	printf(">-h: For help.\n");
	printf(">-j -[1-9]: For node join.\n");
	printf(">-l -[1-9]: For node leave.\n");
	printf(">-b -[1-9] -[0-255]: For broadcast message.\n");
	printf(">-d -[1-9] -[1-9] -[0-255]: For direct message.\n");
	printf(">-r -[1-9]: For receive message.\n");
}