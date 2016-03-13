#include <stdio.h>
#include "CommonLib\queue.h"
#include "CommonLib\io.h"
#include "CommonLib\debug.h"
#include "node.h"
#include "packet.h"
#include "mcb.h"
#include "command.h"

DWORD GlobalListener (LPVOID parameter)
{
	mcbp control = (mcbp)parameter;

	INFO("Started listener.")

	while (control->status == STATUS_RUN)
	{
		if(((dll_cbp)control->global_queue)->dll_size != 0)
		{
			int i, j = 0;

			packetp packet = (packetp)queue_remove(control->global_queue);

			INFO("Packet in the air.")

			for (i = 0; i < control->node_count; i++)
			{
				for (j = 0; j < MAX_NODES; j++)
				{
					if (control->nodes[i]->neighbor_nodes[j] == 0)
						break;

					if (control->nodes[i]->neighbor_nodes[j] == packet->SenderId)
					{
						if (packet->TargetId == 0)
						{
							INFO("Packet sent to receiver.")

							if (queue_add(control->nodes[i]->incoming_packets, (void *)packet) == QUEUE_FAIL)
							{
								DBG(0, "Failed to add packet to node queue.")
							}
						}
						else
						{
							if (packet->TargetId == control->nodes[i]->id)
							{
								INFO("Packet sent to receiver.")

								if (queue_add(control->nodes[i]->incoming_packets, (void *)packet) == QUEUE_FAIL)
								{
									DBG(0, "Failed to add packet to node queue.")
								}
							}
						}
					}
				}
			}
		}
	}

	INFO("Stopped listener.")

	return 0;
}

int main()
{
	int i = 0;

	char * result = NULL;
	char buffer[100];

	mcb control;


	control.status = STATUS_RUN;
	control.global_queue = queue_create();

	GetInput("Number of nodes? (Max 9)", buffer);
	control.node_count = atoi(buffer);

	for (i = 0; i < control.node_count; i++)
	{
		char * token = NULL;
		int j = 0;

		control.nodes[i] = (node_cbp)malloc(sizeof(node_cb));

		control.nodes[i]->outgoing_packets = control.global_queue;
		control.nodes[i]->incoming_packets = queue_create();
		control.nodes[i]->commands = queue_create();
		control.nodes[i]->id = i+1;

		for (j = 0; j < MAX_NODES; j++)
		{
			control.nodes[i]->neighbor_nodes[j] = 0;
		}

		j = 0;

		printf(">Node %d\n", i+1);
		GetInput("Connected nodes?", buffer);

		token = strtok(buffer, " ");

		while (token != NULL)
		{
			int node = atoi(token);
			control.nodes[i]->neighbor_nodes[j++] = node;
			token = strtok(NULL, " ");
		}
	}

	INFO("Created nodes.")

	CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)GlobalListener, (LPVOID)&control, 0, NULL); 

	for (i = 0; i < control.node_count; i++)
	{
		CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)NodeStart, (LPVOID)&control, 0, (LPDWORD)&control.thread_id[i]);
	}

	INFO("Started command buffer.")

	while(control.status == STATUS_RUN)
	{
		int node = 0;
		int temp = 0;
		command_bp command;
		char * token = NULL;

		GetInput("Command?", buffer);

		token = strtok(buffer, "-");

		switch (*token)
		{
			case 'e':
			case 'E':
				control.status = STATUS_STOP;
				break;

			case 'h':
			case 'H':
				DisplayHelp();
				break;

			case 'j':
			case 'J':
				command = (command_bp)malloc(sizeof(command_b));
				command->command = *token;

				token = strtok(NULL, "-");
				node = atoi(token);

				queue_add(control.nodes[node - 1]->commands, command);
				break;

			case 'b':
			case 'B':
				command = (command_bp)malloc(sizeof(command_b));
				command->command = *token;
				
				token = strtok(NULL, "-");
				node = atoi(token);

				token = strtok(NULL, "-");
				temp = atoi(token);
				command->data = temp;

				command->to = 0;

				queue_add(control.nodes[node - 1]->commands, command);
				break;

			case 'd':
			case 'D':
				command = (command_bp)malloc(sizeof(command_b));
				command->command = *token;

				token = strtok(NULL, "-");
				node = atoi(token);

				token = strtok(NULL, "-");
				temp = atoi(token);
				command->to = temp;

				token = strtok(NULL, "-");
				temp = atoi(token);
				command->data = temp;

				queue_add(control.nodes[node - 1]->commands, command);
				break;

			case 'r':
			case 'R':
				command = (command_bp)malloc(sizeof(command_b));
				command->command = *token;
				
				token = strtok(NULL, "-");
				node = atoi(token);

				queue_add(control.nodes[node - 1]->commands, command);
				break;

			case 'l':
			case 'L':
				command = (command_bp)malloc(sizeof(command_b));
				command->command = *token;
				
				token = strtok(NULL, "-");
				node = atoi(token);

				queue_add(control.nodes[node - 1]->commands, command);
				break;

			default:
				INFO("Incorrect command.");
				break;
		}
	}

	INFO("Stopped command buffer.")
	Sleep(1000);

	return 0;
}
