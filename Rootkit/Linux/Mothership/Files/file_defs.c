/**  
@author Alexander Bjornsrud <alexanderbjornsrud@gmail.com>
@file file_defs.h
@brief All the file handler definitions with their functions.
 */


#ifndef __define_h__
    #include "definitions.h"
    #include <linux/module.h>	
    #include <linux/socket.h>
    #include <linux/init.h>
    #include <linux/fs.h>
    #include <linux/uaccess.h>
    #include <linux/device.h>
#endif



struct device_out all = {
	.name = "mothership_all",
	.fops = {
			.open = dev_open_all,
			.release = dev_close_all,
			.read = dev_read_all,
			.write = dev_write_all
		}
};


static int dev_open_all(struct inode* inodep,struct file *file){
	/**
	 @brief Called when a device is opened.
	 @param inodep Structure that contains the inode.
	 @param file The file structure tgat is opened.
	 @return 0 for succes -1 for failure
	 */

	log_info("Filehandle opened: %s","mothership_all");
	return 0;
}

static int dev_close_all(struct inode *inodep,struct file *file){
	/**
	 @brief Called when a device is closed.
	 @param inodep Structure that contains the inode.
	 @param file The file structure tgat is closed.
	 @return 0 for succes -1 for failure
	 */

	log_info("Filehandle closed: %s","mothership_all");
	return 0;
}

static ssize_t dev_read_all(struct file* fils,char* buff,size_t size,loff_t *offset){
	int err = 0;
	char *msg = "Hello !";
	int len = strlen(msg);
	err = copy_to_user(buffer,msg,len);
    return err == 0 ? len : -EFAULT;
    }

static ssize_t dev_write_all(struct file* file,const char* buff,size_t size ,loff_t *offset){
    return 0;
    }
