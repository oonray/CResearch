#include <stdio.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <arpa/inet.h>


void msg(){
    struct sockaddr_in *server = malloc(sizeof(struct sockaddr_in));
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);

    char *msg = "You have Changed the execution\n";

    server->sin_family = AF_INET; 
    inet_pton(AF_INET,"127.0.0.1", &server->sin_addr); 
    server->sin_port = htons(31337); 

    connect(sockfd,(struct sockaddr *)server,sizeof(server));
    write(sockfd,msg,sizeof(msg)/sizeof(char));
}