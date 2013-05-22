/********************************************************************************
* File Name:	setup_timer_key.c
* Description:	第7章实例训练          
* Reference book:《Linux内核API完全参考手册》邱铁，周玉，邓莹莹 ，机械工业出版社.2010.9  
* E_mail:openlinux2100@gmail.com			                
*
********************************************************************************/

#include <linux/module.h>
#include<linux/timer.h>
MODULE_LICENSE("GPL");

struct timer_list my_timer; //声明定时器全局变量

//自定义定时器到期执行函数，在此只有显示功能，不做任何处理
void my_timer_function(unsigned long data)
{
	printk("<0> In the my_timer_function\n");
	printk("<0>the jiffies is :%ld\n",jiffies);//显示当前节拍数    
	struct timer_list *mytimer = (struct timer_list *)data;	
	printk("<0>the expries of my_timer1 is :%ld\n",mytimer->expires);//显示expires字段的值    
}


int __init timer_init(void)
{
	printk("<0> my_timer will be created.\n");	
	printk("<0>the jiffies is :%ld\n",jiffies);//显示当前节拍数
	my_timer.expires = jiffies + 1*HZ;  // HZ=250，初始化expires的字段		
	setup_timer_key(&my_timer,"my_timer",NULL,my_timer_function,&my_timer);//调用函数对定时器变量进行初始化
	add_timer(&my_timer);   //将定时器变量加入到合适的链表
	printk("<0> my_timer init.\n");
	return 0;
}

void __exit timer_exit(void)
{
        printk("<0>Goodbye  setup_timer_key\n");
        del_timer(&my_timer);  //删除定时器变量
}

module_init(timer_init);
module_exit(timer_exit);


