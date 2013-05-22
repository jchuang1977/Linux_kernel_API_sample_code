/********************************************************************************
* File Name:	init_timer_key.c
* Description:	第7章实例训练          
* Reference book:《Linux内核API完全参考手册》邱铁，周玉，邓莹莹 ，机械工业出版社.2010.9  
* E_mail:openlinux2100@gmail.com			                
*
********************************************************************************/

#include <linux/module.h>
#include<linux/timer.h>
MODULE_LICENSE("GPL");

struct timer_list my_timer; //声明全局变量

//自定义定时器到期时执行的函数，在此只有显示的功能
void my_timer_function(unsigned long data)
{
	printk("<0> In the my_timer_function\n");
	printk("<0>the jiffies is :%ld\n",jiffies);    
	struct timer_list *mytimer = (struct timer_list *)data;	
	printk("<0>the expries of my_timer is :%ld\n",mytimer->expires);
}


int __init timer_init(void)
{
	printk("<0> my_timer will be created.\n");	
	printk("<0>the jiffies is :%ld\n",jiffies); //显示当前的时钟节拍数
	init_timer_key(&my_timer,"my_timer",NULL); //调用函数init_timer_key()，对定时器变量进行初始化
	my_timer.expires = jiffies + 1*HZ;  // HZ=250，定时器的到期时间在当前节拍的基础上增加250节拍
	my_timer.data = &my_timer;      //初始化data字段
	my_timer.function = my_timer_function;  //初始化function字段
	add_timer(&my_timer);    //将定时器变量出入到合适的链表中
	printk("<0> my_timer init.\n");
	return 0;
}

void __exit timer_exit(void)
{		
        printk("<0>Goodbye  init_timer_key\n");
	del_timer(&my_timer);
}

module_init(timer_init);
module_exit(timer_exit);


