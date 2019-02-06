
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
#include <linux/types.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/device.h>
#include <linux/kdev_t.h>

/*
Definitions 	definitions.h
Colors			colors.h
Debug			kerndebug.h
*/
#include "definitions.h"
#include "../headders/kerndebug.h"
#include "../headders/colors.h"
#include "file_defs.c"

static struct class *_class; 

static int create_device(struct device_out *dev){
	/**
	@brief Creates an IO Device.
	@param dev A device structure.
	@param fops The file operations stucture pointing to functions.
	@return returns 0 for success and -1 for failure.

	Creates an IO device that the user can interface with via /dev/
	*/

	//_class = class_create(THIS_MODULE,"chardrv");

	//alloc_chrdev_region(dev_t first, unsigned int count,char *name);

	//log_info("Creating Device");
	//int success = alloc_chrdev_region(dev->device,0,1,dev->name);
	//if(success==0){
	//	log_success("Chardev registered with major Number: %d", MAJOR(dev->device)));
	//}else{return success;}
	
	cdev_init(&dev->cdev,&dev->fops);
	dev->cdev.owner = THIS_MODULE;
	dev->cdev.ops = dev->fops;
	if(cdev_add(dev->cdev, dev->device, 1)==0){
		log_success("Device Created");
	}

	log_success("Device Created");
	return 0;
};

static int destroy_device(struct device_out *dev){
	/**
	@brief Destroys an IO Device.
	@param dev A device structure.
	@return returns 0 for success and -1 for failure.

	Destroys an IO device that then is removed from  /dev/
	*/
	log_info("Destroying Device");
	cdev_del(dev->device);
	class_destroy(_class);
	unregister_chrdev_region(dev->device,1);
	log_success("Device Destryed");
	return 0;
}

static int __init mothership_init(void)
{
	/**
	 @brief Initializes the mothership. 
	 @return 0 for success -1 for error.
	 */
	
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
