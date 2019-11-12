#ifndef _mc_gpio_list_h_
#define _mc_gpio_list_h_

//#define GPIO_1 1
#define GPIO_2 2
#define GPIO_3 3
#define GPIO_4 4
#define GPIO_5 5
#define GPIO_6 6
#define GPIO_7 7
#define GPIO_8 8
#define GPIO_9 9
#define GPIO_10 10
#define GPIO_11 11
#define GPIO_12 12
#define GPIO_13 13
#define GPIO_14 14
#define GPIO_15 15
#define GPIO_16 16
#define GPIO_17 17
#define GPIO_18 18
#define GPIO_19 19
#define GPIO_20 20
#define GPIO_21 21
#define GPIO_22 22
#define GPIO_23 23
#define GPIO_24 24
#define GPIO_25 25
#define GPIO_26 26
#define GPIO_27 27

#define MAX_GPIO_NUMBER 27

#define DEBUGLEVEL 4		//调试打印等级，默认为2，1-err（错误），2-log（关键信息），3-debug（调试）。
#define mc_gpio_print(n,fmt,arg...) do{\
	if(n){\
			printk("[MC_GPIO "fmt,##arg);\
		}\
	else\
			;\
	}while(0)

#define mc_gpio_print_err(fmt,arg...) 	mc_gpio_print(DEBUGLEVEL>=1?1:0,"ERROR:]"fmt,##arg)
#define mc_gpio_print_log(fmt,arg...) 	mc_gpio_print(DEBUGLEVEL>=2?1:0,"LOG:]"fmt,##arg)
#define mc_gpio_print_debug(fmt,arg...) mc_gpio_print(DEBUGLEVEL>=3?1:0,"DEBUG:]"fmt,##arg)

enum MODE{
	MOD_0 = 0,
	MOD_1,
	MOD_2,
	MOD_3,
	MOD_4
};


extern int mc_gpio_setdir(unsigned int pins,int dir);
extern int mc_gpio_getdir(unsigned int pins);
extern int mc_gpio_setmod(unsigned int pins,int mod);
extern int mc_gpio_getmod(unsigned int pins);
extern int mc_gpio_setout(unsigned int pins,int out);
extern int mc_gpio_getout(unsigned int pins);





#endif