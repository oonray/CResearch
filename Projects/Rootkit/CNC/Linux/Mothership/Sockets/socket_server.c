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
    .con.addr.sin_family = AF_INET,
    .con.addr.sin_port = 31337,
    .con.address = "0.0.0.0"
};

int create_socket(struct connection *con){
    con.socket = socket(con->sin_family,SOCK_STREAM,0);
    inet_aton(con.address,&con.addr);
    return 0;
}

int bind_to_addr(struct connection *con){
    bind(con.socket,(struct sockaddr *)&con.addr, sizeof(con.addr));
    return 0;
}

int accept_drone(struct connection *con){
    struct drone dr = malloc(sizeof(struct drone));
    dr.name = "Drone_"+conf.content.count+1;
    dr.con.socket = accept(con.socket,(struct sockaddr *)&dr.con.addr, sizeof(struct sockadsddr));

    create_device(&dr.dev);
    append_drone(&dr);
    return 0;
}
