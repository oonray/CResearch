
/*
 @author Alexander Bjornsrud <alexanderbjornsrud@gmail.com>
 @file mothership.c
 @brief A Kernel Module c&c mothership.

This is a kernel module used for command and controll in a botnet like maner.
It will only work in a testing enviroment and is not ment to be used outside the lab.
This module creates filhandles for communication with the bots.

This module is ment as an experiment and MAY NEVER BE USED OUTSIDE A LAB.....! 
This module may contain code that alters the behaviour of an operatingsystem in a potentinally malichous maner.
This software serves no convetnionally usefull purpouse and is continouasly devloped and thefore never finished.

#############################################################
#  NEVER USER IN A PRODUCTON ENVIROMENT!!!!!!!!!!!!!!!!!!!  #
#  !!!!***THIS SOFTWARE WILL HARM YOUR SYSTEM***!!!!	    #
############################################################# 

*/

#include <linux/module.h>	
#include <linux/socket.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/device.h>
#include <linux/cdev.h>

/*
Definitions 	definitions.h
Colors			colors.h
Debug			kerndebug.h
*/
#include "definitions.h"
#include "../headders/kerndebug.h"
#include "../headders/colors.h"
#include "file_defs.c"


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
	cdev_init(dev->cdev,&dev->fops);

	log_info("Setting Owner");
	dev->cdev->owner = THIS_MODULE;

	log_info("Making Device");
	dev->device = MKDEV(dev->major,dev->minor);

	log_info("Adding Device");
	add = cdev_add(dev->cdev, dev->device, 0);
	
	if(add==0){
			log_info("Creating Device");
			dev->dev = device_create(dev->_class,0,dev->device,0,dev->name);
			log_success("Device Created with major:%d", MAJOR(dev->device));
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
	cdev_del(dev->cdev);
	class_destroy(dev->_class);
	log_success("Device Destryed");
}

static int __init mothership_init(void)
{
	/**
	 @brief Initializes the mothership. 
	 @return 0 for success -1 for error.
	 */
	log_success("-----------------------------");
	log_success("Module Loaded");
	create_device(&all);
	return 0;
}

static void __exit mothership_exit(void)
{  
	/**
	 @brief UnInitializes the mothership. 
	 @return 0 for success -1 for error.
	 */

	destroy_device(&all);
	log_success("Module Unloaded");
}


module_init(mothership_init);
module_exit(mothership_exit);
