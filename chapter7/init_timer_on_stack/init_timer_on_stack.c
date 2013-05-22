/********************************************************************************
* File Name:	init_timer_on_stack.c
* Description:	第7章实例训练          
* Reference book:《Linux内核API完全参考手册》邱铁，周玉，邓莹莹 ，机械工业出版社.2010.9  
* E_mail:openlinux2100@gmail.com			                
*
********************************************************************************/

#include <linux/module.h>
#include<linux/timer.h>
MODULE_LICENSE("GPL");

struct timer_list my_timer;     //定义一个静态全局变量
//自定义一个定时器函数，此函数在此只有输出的功能
void my_timer_function(unsigned long data)
{
	printk("<0> In the my_timer_function\n");
	printk("<0>the jiffies is :%ld\n",jiffies); //显示当前节拍数   
	struct timer_list *mytimer = (struct timer_list *)data;	
	printk("<0>the expries of my_timer is :%ld\n",mytimer->expires);//显示expires字段的值
	printk("<0>the base of my_timer is:%u\n",(unsigned int)mytimer->base);//显示base字段的值	
}

int __init timer_init(void)
{
	printk("<0> my_timer will be created.\n");	
	printk("<0>the jiffies is :%ld\n",jiffies); //显示当前节拍数
	init_timer_on_stack(&my_timer); //调用init_timer初始化变量
	my_timer.expires = jiffies + 1*HZ;  // HZ=250;初始化字段expires，使其值在当前节拍的基础上增加250个节拍
	my_timer.data = &my_timer;          //初始化字段data,其值指向变量的地址
	my_timer.function = my_timer_function; //初始化字段function，其值是自定义的定时器函数
	add_timer(&my_timer);                //调用函数add_timer()将变量插入合适的动态定时器队列
	printk("<0> my_timer init.\n");
	return 0;
}

void __exit timer_exit(void)
{	
        printk("<0>Goodbye  init_timer_on_stack\n");
}

module_init(timer_init);
module_exit(timer_exit);

