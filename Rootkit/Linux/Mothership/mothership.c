
/*
 @author Alexander Bjornsrud <alexanderbjornsrud@gmail.com>
 @file mothership.c
 @brief A Kernel Module c&c mothership.

This is a kernel module used for command and controll in a botnet like maner.
It will only work in a testing enviroment and is not ment to be used outside the lab.
This module creates filhandles for communication with the bots.

 */

#include <linux/module.h>	
#include <linux/socket.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/device.h>

/*
Definitions 	definitions.h
Colors			colors.h
Debug			kerndebug.h
*/
#include "definitions.h"
#include "../headders/kerndebug.h"
#include "../headders/colors.h"


static struct file_operations fops = {
	.open = dev_open,
	.release = dev_close,
	.read = dev_read,
	.write = dev_write
};


struct device_out dev = {
	.name = "mothership_01",
};


static int create_device(struct device_out *dev, struct file_operations *fops){
	/**
	@brief Creates an IO Device.
	@param dev A device structure.
	@param fops The file operations stucture pointing to functions.
	@return returns 0 for success and -1 for failure.

	Creates an IO device that the user can interface with via /dev/
	*/

	dev->major = register_chrdev(0, dev->name, fops);
	
	if(dev.major < 0){
		log_err("The module failed to load!");
		return dev->major;
	}

	dev->_class = class_create(dev.name, "chardrv");
    device_create(dev->_class, NULL, dev->device, NULL, dev->name);
	return 0;
};

static int destroy_device(struct device_out *dev){
	/**
	@brief Destroys an IO Device.
	@param dev A device structure.
	@return returns 0 for success and -1 for failure.

	Destroys an IO device that then is removed from  /dev/
	*/
	device_destroy(dev->_class,dev->device);
	class_destroy(dev->class);
	unregister_chrdev(dev->major,dev->name);
	return 0;
}

static int __init mothership_init(void)
{
	/**
	 @brief Initializes the mothership. 
	 @return 0 for success -1 for error.
	 */
	
	log_success("Module Loaded");
	return 0;
}

static void __exit mothership_exit(void)
{  
	/**
	 @brief UnInitializes the mothership. 
	 @return 0 for success -1 for error.
	 */

	log_success("Module Unloaded");
	unregister_chrdev(dev.major, dev.name);
}

static int dev_open(struct inode* inodep,struct file *file){
	/**
	 @brief Called when a device is opened.
	 @param inodep Structure that contains the inode.
	 @param file The file structure tgat is opened.
	 @return 0 for succes -1 for failure
	 */

	printk("%s[+]%s Filehandle opened: %s",KGRN,KNRM,"");
	return 0;
}
static int dev_close(struct inode *inodep,struct file *file){
	/**
	 @brief Called when a device is closed.
	 @param inodep Structure that contains the inode.
	 @param file The file structure tgat is closed.
	 @return 0 for succes -1 for failure
	 */

	printk("%s[+]%s Filehandle closed: %s",KRED,KNRM,"");
	return 0;
}

static ssize_t dev_read(struct file* fils,char* buff,size_t size,loff_t *offset){return 0;}
static ssize_t dev_write(struct file* file,const char* buff,size_t size ,loff_t *offset){return 0;}

module_init(mothership_init);
module_exit(mothership_exit);