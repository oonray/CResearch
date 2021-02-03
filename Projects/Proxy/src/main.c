#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#include "winsocs.h"
#else
#include "linsocks.h"
#endif

#include "linked.h"


int main(){
#ifdef _WIN32
    WSADATA *wsadata = init();
#endif

      

#ifdef _WIN32
    end(wsadata);
#endif
}


