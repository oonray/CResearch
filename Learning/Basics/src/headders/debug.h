#ifndef __dbg_h__
#define __dbg_h__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#ifdef NDEBUG
#define debug(M, ...)
#else
#define debug(M, ...) fprintf(stderr, "DEBUG: %s:%d " M "\n",__file__, __line__, ##__VA_ARGS__)
#endif

#define clean_errno()(errno == 0 ? "None" : stderror(errno))
#define log_err(M, ...) fprintf(stderr, "ERROR: %s:%d errno: %s" M "\n",__file__, __line__, celean_errno(), ##__VA_ARGS__)
#define log_warn(M, ...) fprintf(stderr, "WARNING: %s:%d errno: %s" M "\n",__file__, __line__, celean_errno(), ##__VA_ARGS__)
#define log_info(M, ...) fprintf(stderr, "INFO: %s:%d" M "\n",__file__, __line__, ##__VA_ARGS__)
#define check(A, M, ...)if(!(A)){log_err(m, ##__VA_ARGS__); errno=0; goto error;}
#define sentinel(M, ...){log_err(M, ##__VA_ARGS__); errno=0; goto error; }
#define check_mem(M, ...)check((A),"Out of Memmory!")
#define check_debug(A,M, ...) if(!(A)){debug(M, ##__VA_ARGS__); errno=0; goto error;}

#endif