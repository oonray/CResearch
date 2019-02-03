/*

.. author:: Alexander Bjornsrud <alexanderbjornsrud@gmail.com>
.. name:: definitions.h

All the different struct and function definitions.
For cleanlyness.

*/
#define VERBOSE 1
#define MODULE_NAME "mothership"

static int dev_open(struct inode*,struct file*);
static int dev_close(struct inode*,struct file*);
static ssize_t dev_read(struct file*,char*,size_t,loff_t*);
static ssize_t dev_write(struct file*,const char*,size_t,loff_t*);
//static int create_device(struct device);


struct connection{
	int port;
	char *addr;
	int type;
	char *filename;		
};

struct device_out {
    char *name;
    char *type;
    int major;
    char *envp[4];
    char *args[3];
};
