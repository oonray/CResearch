/*

.. author:: Alexander Bjornsrud <alexanderbjornsrud@gmail.com>
.. name:: kerneldbug.h

Debug Functions for the kernel.
  *  Uses Colors.

*/

#include <linux/kernel.h>

#ifndef __dbg_h__
#define __dbg_h__
#endif

#ifndef KNRM
    #include "colors.h"
#endif

#ifndef VERBOSE
    #define VERBOSE 0
#endif

#ifdef NDEBUG
#define debug(M, ...)
#else 
#define debug(M, ...) if(VERBOSE){ printk(KERN_INFO "(%s:%d:%s) %s[.]%s DEBUG, " M "\n", __FILE__, __LINE__, __func__,KCYN,KNRM, ##__VA_ARGS__) } 
#endif
 
#define log_err(M, ...) if(VERBOSE){ printk(KERN_ALERT "(%s:%d:%s) %s[-]%s ERROR, " M "\n",__FILE__, __LINE__, __func__,KRED,KNRM, ##__VA_ARGS__) } 

#define log_warn(M, ...) if(VERBOSE){ printk(KERN_ALERT "(%s:%d:%s) %s[!]%s WARNING, " M "\n",__FILE__, __LINE__, __func__,KMAG,KNRM, ##__VA_ARGS__) }

#define log_info(M, ...) if(VERBOSE){ printk(KERN_INFO "(%s:%d:%s) %s[.]%s INFO, " M "\n", __FILE__, __LINE__, __func__,KCYN,KNRM, ##__VA_ARGS__) }

#define log_success(M, ...) if(VERBOSE){ printk(KERN_INFO "(%s:%d:%s) %s[+]%s SUCCESS, " M "\n", __FILE__, __LINE__, __func__,KGRN,KNRM, ##__VA_ARGS__) }

/*
#define check(A, M, ...) if(!(A)) { log_err(M, ##__VA_ARGS__); errno=0; goto error; } 

#define sentinel(M, ...)  { log_err(M, ##__VA_ARGS__); errno=0; goto error; } 

#define check_mem(A) check((A), "Out of memory.")
 
#define check_debug(A, M, ...) if(!(A)) { debug(M, ##__VA_ARGS__); errno=0; goto error; } 

*/

 