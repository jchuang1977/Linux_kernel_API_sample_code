/********************************************************************************
* File Name:	del_timer_sync.c
* Description:	第7章实例训练          
* Reference book:《Linux内核API完全参考手册》邱铁，周玉，邓莹莹 ，机械工业出版社.2010.9  
* E_mail:openlinux2100@gmail.com			                
*
********************************************************************************/

#include <linux/module.h>
#include<linux/timer.h>

MODULE_LICENSE("GPL");

struct timer_list my_timer; //声明动态定时器变量

void my_timer_function(unsigned long data)
{
	printk("<0> In the my_timer_function\n");
	
	printk("<0>the jiffies is :%ld\n",jiffies);//显示当前节拍数    
	struct timer_list *mytimer = (struct timer_list *)data;	
	
	printk("<0>the expries of my_timer1 is :%ld\n",mytimer->expires);//显示定时器到期节拍数
}

int __init timer_init(void)
{
	printk("<0> my_timer will be created.\n");	

	printk("<0>the jiffies is :%ld\n",jiffies);//显示当前节拍数
	init_timer(&my_timer);//初始化动态定时器
	my_timer.expires = jiffies + 1*HZ;  // HZ=250;初始化字段expires	
	my_timer.data = &my_timer;//初始化字段data
	my_timer.function = my_timer_function;//初始化字段function
	add_timer(&my_timer);//激活动态定时器
	
	int result=del_timer_sync(&my_timer);//从链表中删除动态定时器
	
	printk("<0>the del_timer_sync result is :%d\n",result);//显示删除结果
	
	add_timer(&my_timer);//重新激活动态定时器
	printk("<0> my_timer init.\n");
	return 0;
}

void __exit timer_exit(void)
{
	
	int result=del_timer_sync(&my_timer);//从链表中删除动态定时器
	
	printk("<0>the del_timer_sync result is :%d\n",result);//显示删除结果
    	printk("<0>Goodbye  del_timer_sync\n");
}

module_init(timer_init);

module_exit(timer_exit);


