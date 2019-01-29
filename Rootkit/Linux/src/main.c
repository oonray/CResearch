#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

//Socket includes
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

//std
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define FILEPATH "/etc/mot"
#define BUFF_SIZE 1024

struct socket {
      int previous;
      int next;
      int *clientsock;
      char *readBuff;
      char *writeBuff;
} 

FILE *storage;

 static int __int mothership__init(void){
          // struct sockaddr_in *server_addr;
           //server_addr = malloc(sizeof(struct sockaddr_in));


 }

  static int __exit mothership__exit(void){


 }


