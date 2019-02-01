
/*  
 *  hello-1.c - The simplest kernel module.
 */
#include <linux/module.h>	/* Needed by all modules */
#include <linux/kernel.h>	/* Needed for KERN_INFO */

static int __init mothership_init(void)
{
	printk(KERN_INFO "Hello world 1.\n");
	return 0;
}

static void __exit mothership_exit(void)
{
	printk(KERN_INFO "Goodbye world 1.\n");
}


module_init(mothership_init);
module_exit(mothership_exit);