#include <stdlib.h>
#include "dll.h"
#include "debug.h"

dll_cbp dll_create (void)
{
    dll_cbp control;

    control = (dll_cbp)malloc(sizeof(dll_cb));
    if(control == NULL)
    {
        DBG(0, "malloc() failed, dll_create(), dll.c")
        goto DLL_CREATE_FAILOUT;
    }

    control->dll_head = NULL;
    control->dll_tail = NULL;
    control->dll_size = 0;

DLL_CREATE_FAILOUT:
    return control;
}

int dll_add (dll_cbp control, void * data)
{
    int result = DLL_PASS;
    nodep new_node;

    new_node = (nodep)malloc(sizeof(node));
    if(control == NULL)
    {
        DBG(0, "malloc() failed, dll_add(), dll.c")
        result = DLL_FAIL;
        goto DLL_ADD_FAILOUT;
    }

    new_node->data = data;

    if(control->dll_head == NULL)
    {
        control->dll_head = new_node;
        control->dll_tail = new_node;
        new_node->next = new_node;
        new_node->prev = new_node;
    }
    else
    {
        control->dll_tail->next = new_node;
        control->dll_head->prev = new_node;
        new_node->prev = control->dll_tail;
        new_node->next = control->dll_head;
        control->dll_tail = new_node;
    }

    control->dll_size++;

DLL_ADD_FAILOUT:
    return result;
}

void * dll_remove (dll_cbp control, int index)
{
    int i;
    int result = DLL_PASS;
    void * data;
    nodep temp;

    if((index < 0) || (index > (control->dll_size - 1)))
    {
        DBG(0, "Index is out of range, dll_remove(), dll.c");
        result = DLL_FAIL;
        goto DLL_REMOVE_FAILOUT;
    }

    if((index == 0)&&(control->dll_size == 1))
    {
        temp = control->dll_head;
        control->dll_head = NULL;
        control->dll_tail = NULL;
    }
    else if(index == 0)
    {
        temp = control->dll_head;
        control->dll_tail->next = temp->next;
        control->dll_head = temp->next;
        control->dll_head->prev = control->dll_tail;
    }
    else if(index == (control->dll_size - 1))
    {
        temp = control->dll_tail;
        control->dll_tail = temp->prev;
        control->dll_tail->next = control->dll_head;
        control->dll_head->prev = control->dll_tail;
    }
    else
    {
        temp = control->dll_head;

        for(i = 0; i < index; i++)
        {
            temp = temp->next;
        }

        temp->next->prev = temp->prev;
        temp->prev->next = temp->next;
    }

    control->dll_size--;
    data = temp->data;
    free(temp);

DLL_REMOVE_FAILOUT:
    return data;
}

int dll_free (dll_cbp control)
{
    int result = DLL_PASS;
    void * data;

    while(control->dll_size != 0)
    {
        if((data = dll_remove(control, 0)) == NULL)
        {
            DBG(0, "Problem removing node, dll_free(), dll.c")
            result = DLL_FAIL;
            goto DLL_FREE_FAILOUT;
        }
        free(data);
    }

    free(control);

DLL_FREE_FAILOUT:
    return result;
}
