/**  
@author Alexander Bjornsrud <alexanderbjornsrud@gmail.com>
@file file_create.h
@brief Contains the file creation functions
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


static int create_device(struct device_out *dev){
	/**
	@brief Creates an IO Device.
	@param dev A device structure.
	@param fops The file operations stucture pointing to functions.
	@return returns 0 for success and -1 for failure.

	Creates an IO device that the user can interface with via /dev/
	*/

	int add;
	log_info("Starting Device Creation");

	if(alloc_chrdev_region(&dev->device, 0, 1, dev->name)==0){
		dev->major = MAJOR(dev->device);
		dev->minor = MINOR(dev->device);
		log_info("Device Allocated! with MAJOR:%d",dev->major);
	}else{
		log_err("Could not get Chardev Region!");
		return -1;
	}
	log_info("Creating Class");
	dev->_class = class_create(THIS_MODULE, "chardriver");
	log_info("Initializes cdev");

	cdev_init(&dev->cdev,&dev->fops);

	log_info("Setting Owner");
	dev->cdev.owner = THIS_MODULE;

	log_info("Making Device");
	dev->device = MKDEV(dev->major,dev->minor);

	log_info("Adding Device");
	add = cdev_add(&dev->cdev, dev->device, 1);
	
	if(add==0){
			log_info("Creating Device");
			dev->dev = device_create(dev->_class,NULL,dev->device,NULL,dev->name);
			log_success("Device Created with major:%d and name %s", dev->major,dev->name);
			return 0;
	}else{
			log_err("Device Creation failed with error %d", add);
			return add;
	}
	return -1;
};

void destroy_device(struct device_out *dev){
	/**
	@brief Destroys an IO Device.
	@param dev A device structure.
	@return returns 0 for success and -1 for failure.

	Destroys an IO device that then is removed from  /dev/
	*/

	log_info("Destroying Device");
	cdev_del(&dev->cdev);
	device_destroy(dev->_class,dev->device);
	class_destroy(dev->_class);
	unregister_chrdev_region(dev->device,1);
	log_success("Device Destryed");
    

}