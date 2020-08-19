#include "mysock.h"

#if defined(__WIN32__) || defined(_WIN32)
#include <WinSock2.h>

#define WS_VERSION_CHOICE1 0x202/*MAKEWORD(2,2)*/
#define WS_VERSION_CHOICE2 0x101/*MAKEWORD(1,1)*/
#endif

int initSocket()
{
#if defined(__WIN32__) || defined(_WIN32)
    WSADATA	wsadata;
    if ((WSAStartup(WS_VERSION_CHOICE1, &wsadata) != 0)
        && ((WSAStartup(WS_VERSION_CHOICE2, &wsadata)) != 0)) 
    {
        return -1;
    }
    if ((wsadata.wVersion != WS_VERSION_CHOICE1)
        && (wsadata.wVersion != WS_VERSION_CHOICE2)) 
    {
        WSACleanup();
        return -1;
    }
#endif
    return 0;
}
