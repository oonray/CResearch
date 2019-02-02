
/*  
 *  hello-1.c - The simplest kernel module.
 */
#include <linux/module.h>	/* Needed by all modules */
#include <linux/kernel.h>	/* Needed for KERN_INFO */
#include <linux/socket.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/uaccess.h>


#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"

#define DEVICE_NAME "Mothership"

//static int dev_open(struct *inode,struct *file);
//static int dev_close(struct *inode,struct *file);
//static int dev_read(struct *inode,struct *file);
//static int dev_write(struct *inode,struct *file);

/*
static struct connection {
	int port;
	char *addr;
	int type;
	char *filename;		
	
}

static struct file_operations fops = {
	.open = dev_open,
	.release = dev_close,
	.read = dev_read,
	.write = dev_write
};
*/
FILE *client_list;

static int major;

static int __init mothership_init(void)
{
	printk(KERN_INFO "%s[+]%s Module Loaded\n",KGRN,KNRM);
	/*major = register_chrdev(0,DEVICE_NAME,&fops);
	if(major < 0){
		printk(KERN_ALERT "%s[!]%s The module failed to load!\n",KRED, KNRM);
		return major;
	}*/


	return 0;
}

static void __exit mothership_exit(void)
{
	printk(KERN_INFO "Goodbye world 1.\n");
}


module_init(mothership_init);
module_exit(mothership_exit);