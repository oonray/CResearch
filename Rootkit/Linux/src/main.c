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

struct socket_connextion {
      int previous;
      int next;
      
      struct socket;
      int *clientsock;

      char *readBuff;
      char *writeBuff;
} 

struct file *storage;

 static int __int mothership__init(void){
        /*
        The init Function.
        */
        
        //struct sockaddr_in *server_addr;
        //server_addr = malloc(sizeof(struct sockaddr_in));
        printk(KERN_LOG "Bomb has been Planted!\n");
        printk(KERN_LOG "Mothership is live!\n");


        return 0;

 }

  static int __exit mothership__exit(void){
      /*
        The Exit function.
      */
      printk("Mothership Destroyed!\n");
      return 0;
 }


/*
The init and exit functions.
Called when the module loads and unloads.
*/

module_init(mothership__init);
module_exit(mothership__exit);

