#ifndef TRANSPORT_H
#define TRANSPORT_H

typedef struct {
	int test;
} transport_cb;
typedef transport_cb * transport_cbp;

transport_cbp JoinGroup (void);

unsigned char BroadcastMessage (transport_cbp control, unsigned char data);

unsigned char DirectMessage (transport_cbp control, unsigned char receiver, unsigned char data);

unsigned char ReceiveMessage (transport_cbp control);

unsigned char ReceiveMessageFrom (transport_cbp control, unsigned char sender);

unsigned char LeaveGroup (transport_cbp control);

#endif
