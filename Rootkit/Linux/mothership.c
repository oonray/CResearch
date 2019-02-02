
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
#include "headders/kerndebug.h"

/*
COLORS
*/
#include "headders/colors.h"

#define DEVICE_NAME "Mothership"

static int dev_open(struct inode*,struct file*);
static int dev_close(struct inode*,struct file*);
static ssize_t dev_read(struct file*,char*,size_t,loff_t*);
static ssize_t dev_write(struct file*,const char*,size_t,loff_t*);


struct connection{
	int port;
	char *addr;
	int type;
	char *filename;		
};

static struct file_operations fops = {
	.open = dev_open,
	.release = dev_close,
	.read = dev_read,
	.write = dev_write
};

//call_usermodehelper(argv[0], argv, envp, UMH_NO_WAIT)  //Shell Stuff

static int major;

static char* envp = { "HOME=/", "TERM=linux", "PATH=/sbin:/bin:/usr/sbin:/usr/bin", NULL };

static int __init mothership_init(void)
{
	printk(KERN_INFO "%s[+]%s Module Loaded\n",KGRN,KNRM);
	
	major = register_chrdev(0,DEVICE_NAME,&fops);
	if(major < 0){
		printk(KERN_ALERT "%s[!]%s The module failed to load!\n",KRED, KNRM);
		return major;
	}


	return 0;
}

static void __exit mothership_exit(void)
{
	printk(KERN_INFO "%s[-]%s Module Unloaded.\n",KRED,KNRM);
	register_chrdev(major,DEVICE_NAME);
	call_usermodehelper("/bin/mknod",{DEVICE_NAME,"c",major},envp,UMH_NO_WAIT);
}

static int dev_open(struct inode* inodep,struct file *file){
	printk("%s[+]%s Filehandle opened: %s",KGRN,KNRM,"");
	return 0;
}
static int dev_close(struct inode* inodep,struct file *file){
	printk("%s[+]%s Filehandle closed: %s",KRED,KNRM,"");
	return 0;
}
static ssize_t dev_read(struct file* fils,char* buff,size_t size,loff_t *offset){return 0;}
static ssize_t dev_write(struct file* file,const char* buff,size_t size ,loff_t *offset){return 0;}

module_init(mothership_init);
module_exit(mothership_exit);