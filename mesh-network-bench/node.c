#include <Windows.h>
#include <stdio.h>
#include "CommonLib\dll.h"
#include "CommonLib\debug.h"
#include "Transport\transport.h"
#include "node.h"
#include "mcb.h"
#include "command.h"

mcbp control = NULL;

int NodeId (void)
{
	int i = 0;

	for (i = 0; i < control->node_count; i++)
	{
		if (control->thread_id[i] == GetCurrentThreadId())
			break;
	}

	return i;
}

DWORD NodeStart (LPVOID param)
{
	int id = 0;

	control = (mcbp)param;
	id = NodeId();

	INFO_THREAD("Node started.")

	while (control->status == STATUS_RUN)
	{
		if (((dll_cbp)control->nodes[id]->commands)->dll_size != 0)
		{
			command_bp command = (command_bp)queue_remove(control->nodes[id]->commands);

			INFO_THREAD("Command received.")

			switch (command->command)
			{
				case 'j':
				case 'J':
					INFO_THREAD("Joining group.")
					control->nodes[id]->transport = JoinGroup();
					break;

				case 'b':
				case 'B':
					INFO_THREAD("Broadcasting message.")
					BroadcastMessage(control->nodes[id]->transport, command->data);
					break;

				case 'd':
				case 'D':
					INFO_THREAD("Directing message.")
					DirectMessage(control->nodes[id]->transport, command->to, command->data);
					break;

				case 'r':
				case 'R':
					INFO_THREAD("Receiving message.")
					printf("%c", ReceiveMessage(control->nodes[id]->transport));
					break;

				case 'l':
				case 'L':
					INFO_THREAD("Leaving group")
					LeaveGroup(control->nodes[id]->transport);
					break;

				default:
					break;
			}

			free((void *)command);
		}
	}

	return 0;
}

int SendPacket (packetp packet)
{
	int return_status = NODE_FAIL;

	INFO_THREAD("Sending packet.")

	if (queue_add(control->nodes[NodeId()]->outgoing_packets, (void *)packet) == QUEUE_PASS)
		return_status = NODE_PASS;

	return return_status;
}

packetp ReceivePacket (void)
{
	INFO_THREAD("Receiving packet.")

	return (packetp)queue_remove(control->nodes[NodeId()]->incoming_packets);
}
