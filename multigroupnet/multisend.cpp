#include "mysock.h"

int main(int argc, char** argv)
{
    struct sockaddr_in tLocalAddr, tSevAddr;
    SOCKET tSockFd;

    if (argc < 3)
    {
        printf("usage: multisend \"localip\" port\n");
        return -1;
    }

    initSocket();

    tSockFd = socket(AF_INET, SOCK_DGRAM, 0);
    if (INVALID_SOCKET == tSockFd)
    {
        printf("create socket error \n");
        return -1;
    }

    memset(&tLocalAddr, 0, sizeof(struct sockaddr_in));
    tLocalAddr.sin_family = AF_INET;
    tLocalAddr.sin_addr.s_addr = inet_addr(argv[1]);
    tLocalAddr.sin_port = htons(atoi(argv[2]));
    int nRet = bind(tSockFd, (struct sockaddr*)&tLocalAddr, sizeof(tLocalAddr));
    if (0 != nRet)
    {
        int nError = GetLastError();
        printf("bind error %d\n", nError);
        return -1;
    }

    int nTtl = 200;
//    nRet = setsockopt(tSockFd, IPPROTO_IP, IP_MULTICAST_TTL, (char*)&nTtl, sizeof(nTtl));
    if (-1 == nRet)
    {
        printf("setsockopt IP_MULTICAST_TTL  error \n");
        return -1;
    }

//    nRet = setsockopt(tSockFd, IPPROTO_IP, IP_MULTICAST_IF, (char*)&(tLocalAddr.sin_addr.s_addr), sizeof(tLocalAddr.sin_addr.s_addr));
    if (-1 == nRet)
    {
        printf("setsockopt IP_MULTICAST_IF  error \n");
        return -1;
    }
    char byLoop = 1;
//    nRet = setsockopt(tSockFd, IPPROTO_IP, IP_MULTICAST_LOOP, &byLoop, sizeof(byLoop));
    if (-1 == nRet)
    {
        printf("setsockopt  IP_MULTICAST_LOOP error \n");
        return -1;
    }

    memset(&tSevAddr, 0, sizeof(tSevAddr));
    tSevAddr.sin_family = AF_INET;
    tSevAddr.sin_addr.s_addr = inet_addr(MULTI_GROUP_ADDR);
    tSevAddr.sin_port = htons(MULTI_GROUP_PORT);

    char buf[1024];
    for (int i = 1; i < 1024; ++i)
    {
        memset(buf, i, 1024);
        nRet = sendto(tSockFd, buf, 1024, 0, (sockaddr*)&tSevAddr, sizeof(tSevAddr));
        printf("sendto buf size = %d\n", nRet);
        Sleep(500);
    }
    return 0;
}