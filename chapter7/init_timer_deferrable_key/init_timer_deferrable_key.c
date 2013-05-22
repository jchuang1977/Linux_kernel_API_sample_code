/********************************************************************************
* File Name:	init_timer_deferrable_key.c
* Description:	第7章实例训练          
* Reference book:《Linux内核API完全参考手册》邱铁，周玉，邓莹莹 ，机械工业出版社.2010.9  
* E_mail:openlinux2100@gmail.com			                
*
********************************************************************************/

#include <linux/module.h>
#include<linux/timer.h>
MODULE_LICENSE("GPL");

struct timer_list my_timer;  //声明定时器全局变量

//自定义定时器执行函数，在此只有显示的功能，不做任何处理
void my_timer_function(unsigned long data){
	printk("<0> In the my_timer_function\n");
	printk("<0>the jiffies is :%ld\n",jiffies); //显示当前的节拍数   
	struct timer_list *mytimer = (struct timer_list *)data;	

	//显示定时器变量的expires字段的值	
	printk("<0>the expries of my_timer is :%ld\n",mytimer->expires);
                               
	//显示函数调用之后的定时器变量的base的值	
	printk("the value of the base after the init_timer_deferable_key:%u\n",(unsigned int)mytimer->base);
                     
}


int __init timer_init(void)
{
	printk("<0> my_timer will be created.\n");	
	printk("<0>the jiffies is :%ld\n",jiffies); //显示当前的节拍数

	//显示函数调用之前的定时器变量的base字段的值
	printk("the value of the base before the init_timer_deferable_key:%u\n",(unsigned int)my_timer.base);
                     
	init_timer_deferrable_key(&my_timer,"my_timer","NULL"); //调用函数初始化定时器变量
	//init_timer(&my_timer);
	my_timer.expires = jiffies + 1*HZ;  // HZ=250，设定expires字段的值	
	my_timer.data = &my_timer;     //设定data字段的值
	my_timer.function = my_timer_function;	 //设定function字段的值
	add_timer(&my_timer);              //将定时器变量加入合适的链表
	printk("<0> my_timer init.\n");
	return 0;
}

void __exit timer_exit(void)
{
        printk("<0>Goodbye  init_timer_deferrable_key\n");
}

module_init(timer_init);
module_exit(timer_exit);


