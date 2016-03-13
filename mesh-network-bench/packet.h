#ifndef PACKET_H
#define PACKET_H

#define MAX_DATA_SIZE 28

typedef struct pk packet;
typedef struct pk * packetp;
struct pk{
	unsigned char SenderId;
	unsigned char TargetId;
	unsigned char Operand;
	unsigned char DataSize;
	unsigned char Data[MAX_DATA_SIZE];
};

#endif