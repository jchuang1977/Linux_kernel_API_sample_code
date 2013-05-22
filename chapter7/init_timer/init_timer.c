/********************************************************************************
* File Name:	init_timer.c
* Description:	第7章实例训练          
* Reference book:《Linux内核API完全参考手册》邱铁，周玉，邓莹莹 ，机械工业出版社.2010.9  
* E_mail:openlinux2100@gmail.com			                
*
********************************************************************************/

#include <linux/module.h>
#include<linux/timer.h>

MODULE_LICENSE("GPL");

struct timer_list my_timer;     //定义一个静态全局变量

int __init init_timer_init(void)
{
	printk("<0>into init_timer_init.\n");		
	printk("<0>the value of the start_pid is :%d\n",my_timer.start_pid);
	if(my_timer.base==NULL)
		printk("<0>the base of my_timer has not been initialized\n");
	init_timer(&my_timer); //调用init_timer初始化变量
	printk("<0>the value of the start_pid is :%d\n",my_timer.start_pid);
	if(my_timer.base==NULL)
		printk("<0>the base of my_timer has not been initialized\n");
	else
		printk("<0>the base of my_timer has been initialized\n");
	printk("<0>out init_timer_init.\n");
	return 0;
}

void __exit init_timer_exit(void)
{	
    printk("<0>Goodbye  init_timer\n");
}

module_init(init_timer_init);
module_exit(init_timer_exit);

