
/*
 @author Alexander Bjornsrud <alexanderbjornsrud@gmail.com>
 @file deonw.c
 @brief A Kernel Module c&c worker.

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
Colors				colors.h
Debug				kerndebug.h
*/
#include "definitions.h"
#include "../headders/kerndebug.h"
#include "../headders/colors.h"



static int __init drone_init(void)
{
	/**
	 @brief Initializes the drone. 
	 @return 0 for success -1 for error.
	 */
	log_success("-----------------------------");
	log_success("Module Loaded");
	return 0;
}

static void __exit drone_exit(void)
{  
	/**
	 @brief UnInitializes the drone. 
	 @return 0 for success -1 for error.
	 */
	log_success("Module Unloaded");
}


module_init(drone_init);
module_exit(drone_exit);
