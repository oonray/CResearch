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

conf.server = {
    .dev = all,
    .num_client = 0,
    .con.addr.sin_family = AF_INET,
    .con.addr.sin_port = 31337,
    .con.address = "0.0.0.0"
};

int create_socket(struct connection *con){
    con.socket = socket(con->sin_family,SOCK_STREAM,0);
    inet_aton(con.address,&con.addr)
    bind(con.socket,(struct sockaddr *)&con.addr, sizeof(con.addr));
}
