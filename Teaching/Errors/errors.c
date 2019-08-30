#include <stdio.h>
#include <strings.h>
#include <errno.h>


int main(int arc, char *argv[]){
				FILE *f = fopen("./lol","r");
				printf("The error number is: %d\n", errno);
				printf("The error text is: %s\n", strerror(errno));


				}
