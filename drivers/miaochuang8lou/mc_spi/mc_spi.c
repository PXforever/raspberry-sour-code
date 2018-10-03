#include "mc_spi.h"

#define DRIVER_NAME "mcspi_ctl"
#define DEVICE_NAME "mcspi_ctl"

#define SLAVER_ADDR 0x11  //这里是7-bit地址
#define BUS_NUMBER 1

struct spi_device *mc_spi;


MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("TOPEET");

static int mcspi_hw_init(struct gpio gpio)
{
	//初始化SDA SCL
}

int mc_spi_write(unsigned int reg_addr,int data)
{
	//等待填写
}
EXPORT_SYMBOL(mc_spi_write);

int mc_spi_read(unsigned int reg_addr,int data)
{
	//等待填写
}
EXPORT_SYMBOL(mc_spi_read);


static long mcspi_ioctl( struct file *files, unsigned int cmd, unsigned long arg){
	//设置CPOL  CPOH等
}

static ssize_t mcspi_write (struct file *files, const char __user *buff, size_t len, loff_t * offset)
{
	char *buff_data;
	int ret = -1; 
	//int i = 0;
	
	buff_data  = kmalloc(len,GFP_ATOMIC );
	printk(KERN_EMERG "Enter mcspi_write function\n");
/*
	if(down_interruptible(&sem))
	{
		return -ERESTARTSYS;
	}
*/
	
	if(buff_data == NULL) 
	{
		printk(KERN_EMERG"kmalloc faimcspi!\n");
		return -1;
	}
	ret = copy_from_user(buff_data, buff, len);
	if(ret<0)
	{
		printk(KERN_EMERG"copy_frome_user faimcspi!\n");
		return -1;
	} 
	
	//up(&sem);

	printk(KERN_EMERG"user want print :%d,%d",buff_data[0],buff_data[1]);

	kfree(buff_data);
	return 0;
	
}

static int mcspi_release(struct inode *inode, struct file *file){
	printk(KERN_EMERG "mcspi release\n");
	
	return 0;
}

static int mcspi_open(struct inode *inode, struct file *file){
	printk(KERN_EMERG "mcspi open\n");
	return 0;
}

static struct file_operations mcspi_ops = {
	.owner = THIS_MODULE,
	.write = mcspi_write,
	.open = mcspi_open,
	.release = mcspi_release,
	.unlocked_ioctl = mcspi_ioctl,
	
};


static  struct miscdevice mcspi_dev = {
	.minor = MISC_DYNAMIC_MINOR,
	.name = DEVICE_NAME,
	.fops = &mcspi_ops,
};


static int mcspi_probe(struct spi_device *spi){
	
	printk(KERN_EMERG"\t PX:mcspi_probe initialized\n");
	misc_register(&mcspi_dev);
	mc_spi = spi;
	//初始化SPI设备传输模式。
	//等待填写
	return 0;
}

static int mcspi_remove(struct platform_device *pdv){
	
	printk(KERN_EMERG "\t PX:remove\n");
	misc_deregister(&mcspi_dev);
	return 0;
}

static void mcspi_shutdown(struct platform_device *pdv){
	
	;
}

static struct spi_board_info mcspi_board_info = {
	
	.max_speed_hz = 200,
	.bus_num = 0,
};

static struct spi_driver mcspi_driver = {
	
	.probe = mcspi_probe,
	.remove = mcspi_remove,
	.shutdown = mcspi_shutdown,
	
	.driver = {
		.name = DRIVER_NAME,
		.owner = THIS_MODULE,
	},
};


static int mcspi_init(void)
{
	int DriverState,DeviceState;
	DeviceState = spi_register_board_info(&mcspi_board_info,0);
	if(DeviceState <0)
	{
		mc_spi_print_err("spi board register failed...\n");
		goto exit_device;
	}
	mc_spi_print_debug("spi board register success!!\n");
	
	DriverState = spi_register_driver(&mcspi_driver);
	if(DriverState <0)
	{
		mc_spi_print_err("spi board register failed...\n");
		goto exit_device;
	}
	mc_spi_print_debug("spi board register success!!\n");
	return 0;
	
exit_device:
	return -1;
exit_driver:
	printk(KERN_EMERG "exit_driver");
	return -1;
}

static void mcspi_exit(void)
{
	
	printk(KERN_EMERG "mcspi WORLD exit!\n");
	
	
}

module_init(mcspi_init);
module_exit(mcspi_exit);
