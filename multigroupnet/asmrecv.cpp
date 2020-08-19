#include "mysock.h"

int main(int argc, char** argv)
{
    struct sockaddr_in tLocalAddr, tSevAddr;
    SOCKET tSockFd;
    struct ip_mreq	    tMreq = { 0 };

    initSocket();

    tSockFd = socket(AF_INET, SOCK_DGRAM, 0);
    if (INVALID_SOCKET == tSockFd)
    {
        printf("create socket error \n");
        return -1;
    }

    int nTtl = 200;
    int nRet = setsockopt(tSockFd, SOL_SOCKET, SO_REUSEADDR, (char*)&nTtl, sizeof(nTtl));
    if (-1 == nRet)
    {
        printf("setsockopt IP_MULTICAST_TTL  error \n");
        return -1;
    }

    memset(&tLocalAddr, 0, sizeof(struct sockaddr_in));
    tLocalAddr.sin_family = AF_INET;
#if defined(__WIN32__) || defined(_WIN32)
    tLocalAddr.sin_addr.s_addr = INADDR_ANY;
#else
    tLocalAddr.sin_addr.s_addr = inet_addr(MULTI_GROUP_ADDR);
#endif
    tLocalAddr.sin_port = htons(MULTI_GROUP_PORT);
    nRet = bind(tSockFd, (struct sockaddr*)&tLocalAddr, sizeof(tLocalAddr));
    if (0 != nRet)
    {
        printf("bind error \n");
        return -1;
    }

    nRet = setsockopt(tSockFd, IPPROTO_IP, IP_MULTICAST_TTL, (char*)&nTtl, sizeof(nTtl));
    if (-1 == nRet)
    {
        printf("setsockopt IP_MULTICAST_TTL  error \n");
        return -1;
    }

    tMreq.imr_multiaddr.s_addr = inet_addr(MULTI_GROUP_ADDR);
    tMreq.imr_interface.s_addr = INADDR_ANY;
    nRet = setsockopt(tSockFd, IPPROTO_IP, IP_ADD_MEMBERSHIP, (char*)&tMreq, sizeof(tMreq));
    if (-1 == nRet)
    {
        printf("setsockopt IP_ADD_MEMBERSHIP  error \n");
        return -1;
    }

    memset(&tSevAddr, 0, sizeof(tSevAddr));
    socklen_t len = sizeof(tSevAddr);

    char buf[1024];
    for (int i = 1; i < 2048; ++i)
    {
        nRet = recvfrom(tSockFd, buf, 1024, 0, (sockaddr*)&tSevAddr, &len);
        if (nRet > 0)
        {
            printf("recvfrom buf ip:%s port:%d :%x, %x, %x\n", inet_ntoa(tSevAddr.sin_addr), ntohs(tSevAddr.sin_port), buf[0], buf[nRet / 2], buf[nRet - 1]);
        }
        else
        {
            printf("recv error\n");
        }

        Sleep(500);
    }
    setsockopt(tSockFd, IPPROTO_IP, IP_DROP_MEMBERSHIP, (char*)&tMreq, sizeof(tMreq));
    return 0;
}