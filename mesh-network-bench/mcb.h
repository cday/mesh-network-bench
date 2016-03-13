#ifndef MCB_H
#define MCB_H

#include <Windows.h>

#define STATUS_RUN 1
#define STATUS_STOP 0

typedef struct {
	int node_count;
	node_cbp nodes[MAX_NODES];
	DWORD thread_id[MAX_NODES];
	queuep global_queue;
	int status;
} mcb;
typedef mcb * mcbp;

#endif
