
/*  
 *  hello-1.c - The simplest kernel module.
 */
#include <linux/module.h>	/* Needed by all modules */
#include <linux/kernel.h>	/* Needed for KERN_INFO */
#include <linux/socket.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/uaccess.h>

/*
DEBUG
*/
#include "../headders/kerndebug.h"

/*
COLORS
*/
#include "../headders/colors.h"

/*
Struct Definitions
*/
#include "definitions.h"


static struct file_operations fops = {
	.open = dev_open,
	.release = dev_close,
	.read = dev_read,
	.write = dev_write
};

struct device_out dev = {
	.name = "mothership_01",
	.type = "c",
	.envp = { "HOME=/", "TERM=linux", "PATH=/sbin:/bin:/usr/sbin:/usr/bin", NULL };
};

//call_usermodehelper(argv[0], argv, envp, UMH_NO_WAIT)  //Shell Stuff

static int __init mothership_init(void)
{
	log_success("Module Loaded");
	
	dev.major = register_chrdev(0, dev.name, &fops);
	dev.args = { dev.name, dev.type, dev.major};

	//call_usermodehelper("/bin/mknod", args , dev.envp, UMH_NO_WAIT);

	if(dev.major < 0){
		log_err("The module failed to load!");
		return dev.major;
	}


	return 0;
}

static void __exit mothership_exit(void)
{  
	log_success("Module Unloaded");
	unregister_chrdev(dev.major, dev.name);
}

static int dev_open(struct inode* inodep,struct file *file){
	printk("%s[+]%s Filehandle opened: %s",KGRN,KNRM,"");
	return 0;
}
static int dev_close(struct inode *inodep,struct file *file){
	printk("%s[+]%s Filehandle closed: %s",KRED,KNRM,"");
	return 0;
}

static ssize_t dev_read(struct file* fils,char* buff,size_t size,loff_t *offset){return 0;}
static ssize_t dev_write(struct file* file,const char* buff,size_t size ,loff_t *offset){return 0;}

module_init(mothership_init);
module_exit(mothership_exit);