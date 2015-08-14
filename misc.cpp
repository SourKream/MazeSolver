#include "misc.h"

void printAndExit(string message = "")
{
	perror(message.data());
	exit(1);
}
