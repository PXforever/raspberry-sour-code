
#include "mc_i2c.h"


#define DRIVER_NAME "mci2c_ctl"
#define DEVICE_NAME "mci2c_ctl"

#define SLAVER_ADDR 0x11  //这里是7-bit地址
#define BUS_NUMBER 1

struct i2c_client mci2c_clint;

MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("TOPEET");

static int mci2c_hw_init(struct gpio gpio)
{
	//初始化SDA SCL
}

int mc_i2c_write(unsigned int chip_addr,unsigned int reg_addr,int data)
{
	//等待填写
}
EXPORT_SYMBOL(mc_i2c_write);

int mc_i2c_read(unsigned int chip_addr,unsigned int reg_addr,int data)
{
	//等待填写
}
EXPORT_SYMBOL(mc_i2c_read);


static long mci2c_ioctl( struct file *files, unsigned int cmd, unsigned long arg){
	//设置slave地址
}

static ssize_t mci2c_write (struct file *files, const char __user *buff, size_t len, loff_t * offset)
{
	char *buff_data;
	int ret = -1; 
	//int i = 0;
	
	buff_data  = kmalloc(len,GFP_ATOMIC );
	printk(KERN_EMERG "Enter mci2c_write function\n");
/*
	if(down_interruptible(&sem))
	{
		return -ERESTARTSYS;
	}
*/
	
	if(buff_data == NULL) 
	{
		printk(KERN_EMERG"kmalloc faimci2c!\n");
		return -1;
	}
	ret = copy_from_user(buff_data, buff, len);
	if(ret<0)
	{
		printk(KERN_EMERG"copy_frome_user faimci2c!\n");
		return -1;
	} 
	
	//up(&sem);

	printk(KERN_EMERG"user want print :%d,%d",buff_data[0],buff_data[1]);

	kfree(buff_data);
	return 0;
	
}

static int mci2c_release(struct inode *inode, struct file *file){
	printk(KERN_EMERG "mci2c release\n");
	return 0;
}

static int mci2c_open(struct inode *inode, struct file *file){
	printk(KERN_EMERG "mci2c open\n");
	return 0;
}

static struct file_operations mci2c_ops = {
	.owner = THIS_MODULE,
	.write = mci2c_write,
	.open = mci2c_open,
	.release = mci2c_release,
	.unlocked_ioctl = mci2c_ioctl,
	
};


static  struct miscdevice mci2c_dev = {
	.minor = MISC_DYNAMIC_MINOR,
	.name = DEVICE_NAME,
	.fops = &mci2c_ops,
};


static int mci2c_probe(struct i2c_client *client, const struct i2c_device_id *id){
	
	printk(KERN_EMERG"\t PX:mci2c_probe initialized\n");
	misc_register(&mci2c_dev);
	//等待填写
	return 0;
}

static int mci2c_remove(struct platform_device *pdv){
	
	printk(KERN_EMERG "\t PX:remove\n");
	misc_deregister(&mci2c_dev);
	return 0;
}

static void mci2c_shutdown(struct platform_device *pdv){
	
	;
}

static int mci2c_suspend(struct platform_device *pdv,pm_message_t pmt){
	
	return 0;
}

static int mci2c_resume(struct platform_device *pdv){
	
	return 0;
}
static struct i2c_board_info mci2c_board_info = {DEVICE_NAME,1,(SLAVER_ADDR)};

static struct i2c_driver mci2c_driver = {
	
	.probe = mci2c_probe,
	
	.driver = {
		.name = DRIVER_NAME,
		.owner = THIS_MODULE,
	},
};


static int mci2c_init(void)
{
	int DriverState,DeviceState;
	DeviceState = i2c_register_board_info(BUS_NUMBER,&mci2c_board_info,0);
	if(DeviceState <0)
	{
		mc_i2c_print_err("i2c board register failed...\n");
		goto exit_device;
	}
	mc_i2c_print_debug("i2c board register success!!\n");
	
	DriverState = i2c_add_driver(&mci2c_driver);
	if(DriverState <0)
	{
		mc_i2c_print_err("i2c driver register failed...\n");
		goto exit_device;
	}
	mc_i2c_print_debug("i2c driver register success!!\n");
	return 0;
	
exit_device:
	return -1;
exit_driver:
	printk(KERN_EMERG "exit_driver");
	return -1;
}

static void mci2c_exit(void)
{
	
	printk(KERN_EMERG "mci2c WORLD exit!\n");
	
	
}

module_init(mci2c_init);
module_exit(mci2c_exit);
