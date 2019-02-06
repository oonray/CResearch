
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
	int dev_crt;
	


    alloc_chrdev_region(&dev->device, 0, 1, dev->name);
	if(dev->device != NULL){
		dev->major = MAJOR(dev->device);
		dev->minor = MINOR(dev->device);
	}else{
		log_err("Could not get Chardev Region!");
		return -1;
	}
	the_class = class_create(THIS_MODULE, "chardriver");
	cdev_init(dev->cdev,&dev->fops);

	if(dev->cdev != NULL){
		dev->cdev->owner = THIS_MODULE;
		dev->device = MKDEV(dev->major,dev->minor);

		add = cdev_add(dev->cdev, dev->device, 0);
		if(add==0){
			dev_crt = device_create(the_class,NULL,dev->device,NULL,dev->name);
			if(dev_crt == 0){
				log_success("Device Created with major:%d",MAJOR(dev->device));
				return dev_crt;
			}else{
				log_err("Device Creation failed with error %d",dev_crt);
				return dev_crt;
			}
		}else{
			log_err("Device Creation failed with error %d",add);
			return add;
		}
	}
	return -1;
};

static int destroy_device(struct device_out *dev){
	/**
	@brief Destroys an IO Device.
	@param dev A device structure.
	@return returns 0 for success and -1 for failure.

	Destroys an IO device that then is removed from  /dev/
	*/
	log_info("Destroying Device");
	device_destroy(the_class,dev->device);
	cdev_del(dev->cdev);
	log_success("Device Destryed");
	return 0;
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
