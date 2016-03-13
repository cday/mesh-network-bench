#ifndef QUEUE_H
#define QUEUE_H

#include "dll.h"

#define QUEUE_PASS DLL_PASS
#define QUEUE_FAIL DLL_FAIL

typedef struct dll_cb queue;
typedef dll_cb * queuep;

queuep queue_create (void);

int queue_add (queuep q, void * data);

void * queue_remove (queuep q);

int queue_empty (queuep q);

int queue_free (queuep q);

#endif
