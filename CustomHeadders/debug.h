#ifndef __dbg_h__
#define __dbg_h__
#endif

#ifndef KNMR
    #include "colors.h"
#endif

#include <stdio.h>
#include <errno.h> 
#include <string.h>

#ifdef NDEBUG
#define debug(M, ...)
#else 
#define debug(M, ...) fprintf(stderr, "%s[DEBUG]%s %s:%d:%s: " M "\n",KCYN,KNRM, __FILE__, __LINE__, __func__, ##__VA_ARGS__) 
#endif

#define error(msg, ...) fprintf(stderr,"%s[-]%s" msg "\n",KRED,KNRM,##__VA_ARGS__)
#define success(msg, ...) fprintf(stdout,"%s[+]%s" msg "\n",KGRN,KNRM,##__VA_ARGS__)
#define info(msg, ... ) fprintf(stdout,"%s[.]%s" msg "\n",KMAG,KNRM,##__VA_ARGS__)