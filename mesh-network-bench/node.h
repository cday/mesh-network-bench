#ifndef NODE_H
#define NODE_H

#include <Windows.h>
#include "CommonLib\queue.h"
#include "Transport\transport.h"
#include "packet.h"

#define MAX_NODES 9

#define NODE_PASS 0
#define NODE_FAIL -1

typedef struct {
	int id;
	transport_cbp transport;
	int neighbor_nodes[MAX_NODES];
	queuep outgoing_packets;
	queuep incoming_packets;
	queuep commands;
}node_cb;
typedef node_cb * node_cbp;

DWORD NodeStart (LPVOID param);

int SendPacket (packetp packet);

packetp ReceivePacket (void);

#endif
