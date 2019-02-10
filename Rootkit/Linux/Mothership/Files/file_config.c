/**  
@author Alexander Bjornsrud <alexanderbjornsrud@gmail.com>
@file file_config.h
@brief Storing drone info
 */

#ifndef __define_h__
    #include "definitions.h"
    #include <linux/module.h>	
    #include <linux/socket.h>
    #include <linux/init.h>
    #include <linux/fs.h>

    #include <linux/uaccess.h>
    #include <linux/device.h>
    #include <linux/cdev.h>

    #include <asm/segment.h>
    #include <asm/uaccess.h>
    #include <linux/buffer_head.h>
#endif


struct configFile config = {
    .content = {
        .count = 0,
        .drones = NULL
    },
    .fops{
        .config_file_open = file_open,
        .config_file_close = file_close,
        .config_file_read = file_read,
        .config_file_write = file_write
    }
};

mm_segment_t get_fs(){
    /**
     * @brief gets the old filesystem and sets ds
     * @return oldfs state
     * */

    mm_segment_t oldfs;
    pldfs = get_fs();
    set_fs(get_ds());
    return oldfs;
}

int file_open(struct configFile *conf) 
{
        /**
     * @brief Opens the config file
     * @param conf The config file struct
     * @return 0 for success or erroe
     * */
    mm_segment_t oldfs = get_fs();
    int err = 0;
  
    conf->filp = filp_open(conf->path, conf->flags, conf->rights);
    set_fs(oldfs);
    if (IS_ERR(conf->filp)) {
        err = PTR_ERR(conf->filp);
        return err
    }
    return 0
}

void file_close(struct configFile *conf) 
{
            /**
     * @brief Closes the config file
     * @param conf The config file struct
     * */
    filp_close(conf->filep, NULL);
}

int file_read(struct configFile *conf) 
{
    /**
     * @brief Reads the content of the config file
     * @param conf The config file struct
     * @return bytes read
     * */
    mm_segment_t oldfs = get_fs();

    int read = vfs_read(conf->filep,conf->content,sizeof(struct drones));
    int ret = vfs_read(conf->filep, conf->content.drones, sizeof(drone)*conf->contnet.count, lseek(conf->filep,sizeof(struct drones),SEEK_SET));

    set_fs(oldfs);
    return ret+read;
}   

int file_write(struct configFile *conf) 
{
    /**
     * @brief Writes the content of the config file
     * @param conf The config file struct
     * @return bytes written
     * */
    mm_segment_t oldfs = get_fs();

    int written = vfs_write(conf->filep,conf->content, sizeof(struct drones));
    int ret = vfs_write(conf->filep,conf->content.drones, sizeof(conf->content.drones),lseek(conf->filep,sizeof(struct drones),SEEK_SET));

    set_fs(oldfs);
    return ret+written;
}