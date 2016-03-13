#include <stdlib.h>
#include "queue.h"
#include "debug.h"

queuep queue_create (void)
{
    queuep q;
    
    q = (queuep)dll_create();
    if(q == NULL)
    {
        DBG(1, "malloc() failed, queue_create(), queue.c")
        goto QUEUE_CREATE_FAILOUT;
    }
    
QUEUE_CREATE_FAILOUT:
    return q;
}

int queue_add (queuep q, void * data)
{
    int result = QUEUE_PASS;

    result = dll_add((dll_cbp)q, data); 

    if(result == DLL_FAIL)
    {
        DBG(1, "Failed to queue entry, queue_add(), queue.c")
    }

QUEUE_ADD_FAILOUT:
    return result;
}

void * queue_remove (queuep q)
{
    void * data;
    
    data = dll_remove((dll_cbp)q, ((dll_cbp)q)->dll_size - 1);

QUEUE_REMOVE_FAILOUT:
    return data;
}

int queue_empty (queuep q)
{
    int result = QUEUE_PASS;

    if(((dll_cbp)q)->dll_size > 0)
    {
        result = QUEUE_FAIL;
    }

QUEUE_EMPTY_FAILOUT:
    return result;
}

int queue_free (queuep q)
{
    int result;
    
    result = dll_free((dll_cbp)q);
    if(result == DLL_FAIL)
    {
        DBG(1, "Freeing the queue failed, queue_free(), queue.c")
    }
    
QUEUE_FREE_FAILOUT:
    return result;
}
