#ifndef _mc_pwm_h_
#define _mc_pwm_h_

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
//pwm头文件
#include <linux/pwm.h>

#define DEBUGLEVEL 4		//调试打印等级，默认为2，1-err（错误），2-log（关键信息），3-debug（调试）。
#define mc_pwm_print(n,fmt,arg...) do{\
	if(n){\
			printk("[MC_pwm "fmt,##arg);\
		}\
	else\
			;\
	}while(0)

#define mc_pwm_print_err(fmt,arg...) 	mc_pwm_print(DEBUGLEVEL>=1?1:0,"ERROR:]"fmt,##arg)
#define mc_pwm_print_log(fmt,arg...) 	mc_pwm_print(DEBUGLEVEL>=2?1:0,"LOG:]"fmt,##arg)
#define mc_pwm_print_debug(fmt,arg...) 	mc_pwm_print(DEBUGLEVEL>=3?1:0,"DEBUG:]"fmt,##arg)

extern int mc_pwm_config(unsigned int pwm_channle,char *config);
extern int mc_pwm_start(unsigned int pwm_channle);
extern int mc_pwm_stop(unsigned int pwm_channle);


#endif