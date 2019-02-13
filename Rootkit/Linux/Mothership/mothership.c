
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

#include <linux/socket.h>
#include <linux/in.h>

#include <asm/segment.h>
#include <asm/uaccess.h>
#include <linux/buffer_head.h>
#include <linux/slab.h>


/*
Definitions 		definitions.h
Colors				colors.h
Debug				kerndebug.h
File Definitions	file_defs.c
File Createions		file_create.c
Config File			file_config.c
*/
#include "definitions.h"
#include "../headders/kerndebug.h"
#include "../headders/colors.h"
#include "Files/file_defs.c"
#include "Files/file_create.c"
#include "Files/file_config.c"


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
