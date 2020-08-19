#ifndef __MY_SOCKT_H__
#define __MY_SOCKT_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if defined(__WIN32__) || defined(_WIN32)
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")
#else
#include <sys/types.h>
#include <sys/types.h>
#include <netdb.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>

#define SOCKET int
#define INVALID_SOCKET -1
#define GetLastError() 1
#define Sleep(a) usleep(a * 1000)
#endif

#define MULTI_GROUP_ADDR "239.0.0.30"
#define MULTI_GROUP_PORT 5200


int initSocket();

#endif // __MY_SOCKT_H__
