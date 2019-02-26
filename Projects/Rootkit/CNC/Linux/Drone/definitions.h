#ifndef __define_h__
    #define __define_h__
#endif

#define VERBOSE 1
#define MODULE_NAME "drone"
#define D_PORT 31337


MODULE_LICENSE("GPL");        
MODULE_AUTHOR("Alexander Bjørnsrud");   
MODULE_DESCRIPTION("This is an experimental program intentionally designed to do evil things.\n"
				   "It is not designed to be outside a lab\n"
				   "If the folder name Rootkit did not tip you of please google the term.\n"
				   "This module should not be used by anyone for any purpouse exept controlled labratory experiments."); 

MODULE_VERSION("0.1");


struct drone {
    char *name;
    int soc;
};>