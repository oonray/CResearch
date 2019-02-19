#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>
#include <signal.h>
#include <sys/time.h> /* gettimeofday() */
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <time.h> /* for time() and ctime() */

#define UTC_NTP 2208988800U /* 1970 - 1900 */

int main(int argc, char *argv[]){
    int *rt;
    __asm__(
        "mov %0, [gdtr];"
        ".att_syntax;"
        :"=r"(rt));
    printf("%d\n",rt);
}