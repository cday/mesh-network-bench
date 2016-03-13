#ifndef COMMAND_H
#define COMMAND_H

typedef struct {
	char command;
	char data;
	int to;
} command_b;
typedef command_b * command_bp;

#endif