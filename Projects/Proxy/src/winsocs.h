#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include "dbg.h"

#pragma comment(lib, "Ws2_32.lib")

WSADATA *init(){    
    WSADATA *wsaData = calloc(1,sizeof(WSADATA));
    check_memory(wsaData);

    int result = WSAStartup(MAKEWORD(2,2),wsaData);
    check(result != 0,"Could not init WSA");

    return wsaData;
error:
    return NULL;

}

void end(WSADATA *wsaData){
    check(wsaData != NULL,"Allreaddy destroyed")
    free(wsaData);
error:
    return;
}

