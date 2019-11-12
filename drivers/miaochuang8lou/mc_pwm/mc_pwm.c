#include "mc_pwm.h"

#define DRIVER_NAME "mcpwm_ctl"
#define DEVICE_NAME "mcpwm_ctl"

#define SLAVER_ADDR 0x11  //这里是7-bit地址
#define BUS_NUMBER 1

#define PWM0_ID 0
#define PWM1_ID 1
#define PWM2_ID 2
#define PWM3_ID 3

#define PWM(n) "pwm"#n

struct pwm_device *mc_pwm_device;

MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("TOPEET");

int mc_pwm_config(unsigned int pwm_channle,char *config)
{
	//配置PWM
	return 0;
}
EXPORT_SYMBOL(mc_pwm_config);

int mc_pwm_start(unsigned int pwm_channle)
{
	//PWM开始
	return 0;
}
EXPORT_SYMBOL(mc_pwm_start);

int mc_pwm_stop(unsigned int pwm_channle)
{
	//PWM结束
	return 0;
}
EXPORT_SYMBOL(mc_pwm_stop);


static long mcpwm_ioctl( struct file *files, unsigned int cmd, unsigned long arg){
	//控制PWM
	return 0;
}

static ssize_t mcpwm_write (struct file *files, const char __user *buff, size_t len, loff_t * offset)
{
	char *buff_data;
	int ret = -1; 
	//int i = 0;
	
	buff_data  = kmalloc(len,GFP_ATOMIC );
	printk(KERN_EMERG "Enter mcpwm_write function\n");
/*
	if(down_interruptible(&sem))
	{
		return -ERESTARTSYS;
	}
*/
	
	if(buff_data == NULL) 
	{
		printk(KERN_EMERG"kmalloc faimcpwm!\n");
		return -1;
	}
	ret = copy_from_user(buff_data, buff, len);
	if(ret<0)
	{
		printk(KERN_EMERG"copy_frome_user faimcpwm!\n");
		return -1;
	} 
	
	//up(&sem);

	printk(KERN_EMERG"user want print :%d,%d",buff_data[0],buff_data[1]);

	kfree(buff_data);
	return 0;
	
}

static int mcpwm_release(struct inode *inode, struct file *file){
	printk(KERN_EMERG "mcpwm release\n");

	return 0;
}

static int mcpwm_open(struct inode *inode, struct file *file){
	printk(KERN_EMERG "mcpwm open\n");
	return 0;
}

static struct file_operations mcpwm_ops = {
	.owner = THIS_MODULE,
	.write = mcpwm_write,
	.open = mcpwm_open,
	.release = mcpwm_release,
	.unlocked_ioctl = mcpwm_ioctl,
	
};


static  struct miscdevice mcpwm_dev = {
	.minor = MISC_DYNAMIC_MINOR,
	.name = DEVICE_NAME,
	.fops = &mcpwm_ops,
};


static int mcpwm_init(void)
{
	int ret = -1;
	struct pwm_device new_pwm_device;
	mc_pwm_device = kmalloc( sizeof(struct pwm_device), GFP_KERNEL);
	if(mc_pwm_device = NULL)
	{
		printk("malloc struct pwm_device failed...\n");
		goto exit_device;
	}
	mc_pwm_device = &new_pwm_device;
	
	mc_pwm_device = pwm_request(PWM0_ID,"pwm");
	mc_pwm_device->state.period = 100;
	//mc_pwm_device->state.duty_cycle = 100;
	//mc_pwm_device->state.polarity = PWM_POLARITY_NORMAL;
	//mc_pwm_device->state.enabled = 1;
	
	//pwm_init_state(mc_pwm_device,&mc_pwm_device->state);
	printk("MC_PWM init success!!\n");
	return 0;
exit_device:
	return -1;
exit_driver:
	printk(KERN_EMERG "exit_driver");
	return -1;
}

static void mcpwm_exit(void)
{
	
	printk(KERN_EMERG "mcpwm WORLD exit!\n");
	
	
}

module_init(mcpwm_init);
module_exit(mcpwm_exit);
