#ifndef __dbg_h__
#define __dbg_h__
#endif

#ifndef KNRM
    #include "colors.h"
#endif

#ifdef NDEBUG
#define debug(M, ...)
#else 
#define debug(M, ...) printk(KERN_INFO "\n%s[.]%s DEBUG %s:%d:%s" M "\n",KCYN,KNRM, __FILE__, __LINE__, __func__, ##__VA_ARGS__) 
#endif

#define log_err(M, ...) printk(KERN_ALERT "\n%s[-]%s ERROR (%s:%d:%s)" M "\n",KRED,KNRM,__FILE__, __LINE__, __func__, ##__VA_ARGS__) 

#define log_warn(M, ...) printk(KERN_ALERT "\n%s[!]%s WARNING (%s:%d:%s)" M "\n",KMAG,KNRM, __FILE__, __LINE__, __func__, ##__VA_ARGS__) 

#define log_info(M, ...) printk(KERN_INFO "\n%s[.]%s INFO (%s:%d:%s)" M "\n",KCYN,KNRM, __FILE__, __LINE__, __func__, ##__VA_ARGS__) 

#define log_success(M, ...) printk(KERN_INFO "\n%s[+]%s Sucess (%s:%d:%s)" M "\n",KGRN,KNRM, __FILE__, __LINE__, __func__, ##__VA_ARGS__)

/*
#define check(A, M, ...) if(!(A)) { log_err(M, ##__VA_ARGS__); errno=0; goto error; } 

#define sentinel(M, ...)  { log_err(M, ##__VA_ARGS__); errno=0; goto error; } 

#define check_mem(A) check((A), "Out of memory.")
 
#define check_debug(A, M, ...) if(!(A)) { debug(M, ##__VA_ARGS__); errno=0; goto error; } 

*/

 