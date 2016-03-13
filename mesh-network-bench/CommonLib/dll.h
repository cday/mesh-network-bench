#ifndef DLL_H
#define DLL_H

#define DLL_PASS 0
#define DLL_FAIL -1

typedef struct nd node;
typedef struct nd * nodep;
struct nd{
    void * data;
    nodep next;
    nodep prev;
};

typedef struct {
    nodep dll_head;
    nodep dll_tail;
    int dll_size;
} dll_cb;
typedef dll_cb * dll_cbp;

dll_cbp dll_create (void);

int dll_add (dll_cbp control, void * data);

void * dll_remove (dll_cbp control, int index);

int dll_free (dll_cbp control);

#endif
