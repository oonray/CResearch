
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
static size_t dev_read(struct file*,char*,size_t,loff_t*);
static size_t dev_write(struct file*,const char*,size_t,loff_t*);


static struct connection {
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


static int major;

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

}

static int dev_open(struct inode* inodep,struct file* file){
	printk("%s[+]%s Filehandle opened: %s",KGRN,KNRM,file->filename);
	return 0;
}
static int dev_close(struct inode* inodep,struct file* file){
	printk("%s[+]%s Filehandle closed: %s",KRED,KNRM,file->filename);
	return 0;
}
static size_t dev_read(struct file* fils,char* buff,size_t size,loff_t *offsett){return 0;}
static size_t dev_write(struct file* file,const char* buff,size_t size ,loff_t *offsett){return 0;}

module_init(mothership_init);
module_exit(mothership_exit);