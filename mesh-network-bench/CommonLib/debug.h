#ifndef DEBUG_H
#define DEBUG_H

#include <stdio.h>
#include <Windows.h>

#define VERBOSE

#ifdef VERBOSE

#define INFO(message) printf(">%s\n", message);
#define INFO_DEC(message, amount) printf(">%s, %d\n", message, amount);
#define INFO_THREAD(message) printf(">%d, %s\n", GetCurrentThreadId(), message);

#else

#define INFO(message)
#define INFO_THREAD(message, thread)

#endif

#define DBG(priority, message) printf(">%d, %s.\n", priority, message);
#define DBG_CODE(priority, message, info, format) printf(">%d, %s, "format".\n", priority, message, info);

#endif
