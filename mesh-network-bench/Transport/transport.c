#include <stdlib.h>
#include "transport.h"

transport_cbp JoinGroup (void)
{
	return NULL;
}

unsigned char BroadcastMessage (unsigned char data)
{
	return '\0';
}

unsigned char DirectMessage (unsigned char receiver, unsigned char data)
{
	return '\0';
}

unsigned char ReceiveMessage (void)
{
	return '\0';
}

unsigned char ReceiveMessageFrom (unsigned char sender)
{
	return '\0';
}

unsigned char LeaveGroup (void)
{
	return '\0';
}
