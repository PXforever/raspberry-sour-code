#include <linux/init.h>
#include <linux/module.h>

/*驱动注册的头文件，包含驱动的结构体和注册和卸载的函数*/
#include <linux/platform_device.h>
/*注册杂项设备头文件*/
#include <linux/miscdevice.h>
/*注册设备节点的文件结构体*/
#include <linux/fs.h>

#include <linux/slab.h>

#include <asm/uaccess.h>

#include <linux/string.h>

#include<linux/semaphore.h>

#include <linux/gpio.h>

#include <linux/platform_device.h>

#include <linux/delay.h>

//mc_gpio头文件
#include "mc_gpio_list.h"

#define DRIVER_NAME "mcgpio_ctl"
#define DEVICE_NAME "mcgpio_ctl"

#define MC_GPIO(n) "mc_gpio"#n

#define GET_GPIO 0
#define SET_OUT_HIGH 1
#define SET_OUT_LOW 3
MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("TOPEET");

//static struct semaphore sem;
struct gpio mcgpio_list[MAX_GPIO_NUMBER];

static int mcgpio_hw_init(struct gpio gpio)
{
	int ret = -1;
	ret = gpio_request(gpio.gpio,"mcgpio");
	if(ret<0)
	{
		mc_gpio_print_err(KERN_EMERG"gpio request faimcgpio...\n");
		return -1;
	}	
	return 0;
}

int mc_gpio_setdir(unsigned int pins,int dir)
{
	int ret = -1;
	mc_gpio_print_log("enter %s\n",__func__);
	ret = gpio_request(pins,MC_GPIO(pins));
	if(ret < 0)
	{
		mc_gpio_print_err("request gpio failed...\n");
		goto exit;
	}
	mc_gpio_print_debug("request gpio success!!\n");
	if(dir == 0)
		gpio_direction_input(MC_GPIO(pins));
	else
		gpio_direction_output(MC_GPIO(pins),0);
	
	return pins;
exit:
	return -1;
}
EXPORT_SYMBOL(mc_gpio_setdir);

int mc_gpio_getdir(unsigned int pins)
{
	int ret = -1;
	//等待填写
	return pins;
exit:
	
	return -1;
free_gpio:
	gpio_free(pins);
	return -1;
}
EXPORT_SYMBOL(mc_gpio_getdir);

int mc_gpio_setmod(unsigned int pins,int mod)
{
	//等待填写
}
EXPORT_SYMBOL(mc_gpio_setmod);

int mc_gpio_getmod(unsigned int pins)
{
	//等待填写
}
EXPORT_SYMBOL(mc_gpio_getmod);

int mc_gpio_setout(unsigned int pins,int out)
{
	//等待填写
}
EXPORT_SYMBOL(mc_gpio_setout);

int mc_gpio_getout(unsigned int pins)
{
	//等待填写
}
EXPORT_SYMBOL(mc_gpio_getout);


static long mcgpio_ioctl( struct file *files, unsigned int cmd, unsigned long arg){
	struct gpio get_gpio;
	mc_gpio_print_debug(KERN_EMERG"cmd is %d,arg is %ld\n",cmd,arg);
	switch(cmd)
	{
		case GET_GPIO:	{get_gpio.gpio = arg; get_gpio.flags = 1; mcgpio_hw_init(get_gpio);break;}
		case SET_OUT_HIGH : {gpio_direction_output(arg,1);break;}
		case 2 : {gpio_direction_output(arg,0);break;}
		case SET_OUT_LOW : {gpio_direction_output(arg,0);break;}
		
		default : {mc_gpio_print_debug(KERN_EMERG"please input nomal number...\n");break;}
	}
	return 0;
}

static ssize_t mcgpio_write (struct file *files, const char __user *buff, size_t len, loff_t * offset)
{
	char *buff_data;
	int ret = -1; 
	//int i = 0;
	
	buff_data  = kmalloc(len,GFP_ATOMIC );
	mc_gpio_print_debug(KERN_EMERG "Enter mcgpio_write function\n");
/*
	if(down_interruptible(&sem))
	{
		return -ERESTARTSYS;
	}
*/
	
	if(buff_data == NULL) 
	{
		mc_gpio_print_debug(KERN_EMERG"kmalloc faimcgpio!\n");
		return -1;
	}
	ret = copy_from_user(buff_data, buff, len);
	if(ret<0)
	{
		mc_gpio_print_debug(KERN_EMERG"copy_frome_user faimcgpio!\n");
		return -1;
	} 
	
	//up(&sem);

	mc_gpio_print_debug(KERN_EMERG"user want print :%d,%d",buff_data[0],buff_data[1]);

	kfree(buff_data);
	return 0;
	
}

static int mcgpio_release(struct inode *inode, struct file *file){
	mc_gpio_print_debug(KERN_EMERG "mcgpio release\n");
	gpio_free(mcgpio_list[1].gpio);
	return 0;
}

static int mcgpio_open(struct inode *inode, struct file *file){
	mc_gpio_print_debug(KERN_EMERG "mcgpio open\n");
	return 0;
}

static struct file_operations mcgpio_ops = {
	.owner = THIS_MODULE,
	.write = mcgpio_write,
	.open = mcgpio_open,
	.release = mcgpio_release,
	.unlocked_ioctl = mcgpio_ioctl,
	
};


static  struct miscdevice mcgpio_dev = {
	.minor = MISC_DYNAMIC_MINOR,
	.name = DEVICE_NAME,
	.fops = &mcgpio_ops,
};


static int mcgpio_probe(struct platform_device *pdv){
	
	mc_gpio_print_debug(KERN_EMERG"\t PX:mcgpio_probe initialized\n");
	misc_register(&mcgpio_dev);
	gpio_request(2,"mcgpio");
	return 0;
}

static int mcgpio_remove(struct platform_device *pdv){
	
	mc_gpio_print_debug(KERN_EMERG "\t PX:remove\n");
	misc_deregister(&mcgpio_dev);
	return 0;
}

static void mcgpio_shutdown(struct platform_device *pdv){
	
	;
}

static int mcgpio_suspend(struct platform_device *pdv,pm_message_t pmt){
	
	return 0;
}

static int mcgpio_resume(struct platform_device *pdv){
	
	return 0;
}

struct platform_device mcgpio_device = {
	.name = DEVICE_NAME,
	.id = -1,
	.dev={
		
	},
	
	
};

struct platform_driver mcgpio_driver = {
	.probe = mcgpio_probe,
	.remove = mcgpio_remove,
	.shutdown = mcgpio_shutdown,
	.suspend = mcgpio_suspend,
	.resume = mcgpio_resume,
	.driver = {
		.name = DRIVER_NAME,
		.owner = THIS_MODULE,
	}
};

static int mcgpio_init(void)
{
	int DriverState,DeviceState;
	//int i=0;
	
	mc_gpio_print_debug(KERN_EMERG "PX:mcgpio WORLD enter!\n");

	DeviceState = platform_device_register(&mcgpio_device);
	if(DeviceState <0)
	{
		mc_gpio_print_debug(KERN_EMERG "platform device register faimcgpio...\n");
		return -1;
	}

	DriverState = platform_driver_register(&mcgpio_driver);
	if(DriverState)
	{
		mc_gpio_print_debug(KERN_EMERG "platform driver register faimcgpio...\n");
		goto exit_driver;
	}
	//sema_init(&sem,1);
	

	return 0;
	
exit_driver:
	platform_device_unregister(&mcgpio_device);
	platform_driver_unregister(&mcgpio_driver);
	mc_gpio_print_debug(KERN_EMERG "exit_driver");
	return -1;
}

static void mcgpio_exit(void)
{
	
	mc_gpio_print_debug(KERN_EMERG "mcgpio WORLD exit!\n");
	platform_device_unregister(&mcgpio_device);
	platform_driver_unregister(&mcgpio_driver);	
	
	
}

module_init(mcgpio_init);
module_exit(mcgpio_exit);
