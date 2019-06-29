#include <linux/init.h>
#include <linux/module.h>

MODULE_LICENSE("Dual BSD/GPL");

static int hello_init(void) {
		printk(KERN_AERT, "Hello, World!\n");
		return 0;
}
