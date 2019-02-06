
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

	log_info("Creating Device");
	dev->major = register_chrdev(0, dev->name, &dev->fops);
	log_info("Major Number: %s", dev->major);

	if(dev->major < 0){
		log_err("The module failed to load!");
		return dev->major;
	}

	dev->_class = class_create(*(*dev).name, "chardrv");
    device_create(dev->_class, NULL, dev->device, NULL, dev->name);
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
	device_destroy(dev->_class,dev->device);
	class_destroy(dev->_class);
	unregister_chrdev(dev->major,dev->name);
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
