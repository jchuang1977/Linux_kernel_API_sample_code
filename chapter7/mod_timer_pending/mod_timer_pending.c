/********************************************************************************
* File Name:	mod_timer_pending.c
* Description:	第7章实例训练          
* Reference book:《Linux内核API完全参考手册》邱铁，周玉，邓莹莹 ，机械工业出版社.2010.9  
* E_mail:openlinux2100@gmail.com			                
*
********************************************************************************/

#include <linux/module.h>
#include<linux/timer.h>
MODULE_LICENSE("GPL");

struct timer_list my_timer1; //自定义动态定时器，全局变量

//自定义动态定时器到期处理函数，此函数在此只有显示功能，不做任何处理
void my_timer1_function(unsigned long data)
{
	printk("<0> In the my_timer1_function\n");
	struct timer_list *mytimer = (struct timer_list *)data;
	printk("<0>the current jiffies is:%ld\n",jiffies);//显示当前节拍
	printk("<0>the expires of my_timer1 is:%ld\n",mytimer->expires); //显示动态定时器的到期节拍数	
	int result1=mod_timer_pending(&my_timer1,mytimer->expires+10);//调用函数改变动态定时器到期时间	
	printk("<0>the mod result of my_timer1 is: %d\n",result1);//显示函数调用结果	
	printk("<0>the expires of my_timer1 is:%ld\n",mytimer->expires); //显示动态定时器的到期节拍数
}

int __init timer_init(void)
{
	printk("<0> my_timer1 will be created.\n");
	printk("<0>the current jiffies is :%ld\n",jiffies);//显示当前节拍数
	init_timer(&my_timer1);//初始化动态定时器
	my_timer1.expires = jiffies + 1*HZ;//初始化字段expires,HZ=250
	my_timer1.data = &my_timer1;//初始化字段data
	my_timer1.function = my_timer1_function;//初始化字段function
	add_timer(&my_timer1);	//激活动态定时器
	printk("<0>the expires of my_timer1 is before mod_timer_pending:%ld\n",my_timer1.expires); //显示动态定时器的到期节拍数
	int result1=mod_timer_pending(&my_timer1,my_timer1.expires+10);//调用函数改变动态定时器到期时间	
	printk("the result of mod_timer_pending is: %d\n",result1);//显示函数调用结果
	printk("<0>the expires of my_timer1 is:%ld\n",my_timer1.expires); //显示动态定时器的到期节拍数
	printk("<0> my_timer1 init.\n");
	return 0;
}

void __exit timer_exit(void)
{
        printk("<1>Goodbye  mod_timer_pending\n");
	del_timer(&my_timer1);
}

module_init(timer_init);
module_exit(timer_exit);

