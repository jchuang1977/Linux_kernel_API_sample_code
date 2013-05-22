/********************************************************************************
* File Name:	del_timer.c
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
	printk("<0>the jiffies is :%ld\n",jiffies);    
	struct timer_list *mytimer = (struct timer_list *)data;	
	printk("<0>the expries of my_timer1 is :%ld\n",mytimer->expires);
	int result=del_timer(&my_timer);         //删除定时器变量
	printk("<0>the result of the del_timer is:%d\n",result);//显示删除结果	
}

int __init del_timer_init(void)
{
	printk("<0> into del_timer_init.\n");	
	printk("<0>the jiffies is :%ld\n",jiffies);
	init_timer(&my_timer);            //调用init_timer初始化变量
	my_timer.expires = jiffies + 1*HZ;  // HZ=250;初始化字段expires，使其值在当前节拍的基础上增加250个节拍
	my_timer.data = &my_timer;          //初始化字段data,其值指向变量的地址
	my_timer.function = my_timer_function; //初始化字段function，其值是自定义的定时器函数
	add_timer(&my_timer);                //激活动态定时器
	int result=del_timer(&my_timer);         //删除定时器变量
	printk("<0>the result of the del_timer is:%d\n",result);//显示删除结果
	add_timer(&my_timer);                //再次激活动态定时器
	printk("<0>out del_timer_init.\n");
	return 0;
}

void __exit del_timer_exit(void)
{
	int result=del_timer(&my_timer);         //删除定时器变量，此时的定时器已经不存在，在此只是验证函数的功能
	printk("<0>the result of the del_timer is:%d\n",result);   //显示删除结果
	printk("<0>my_timer is deleted!\n");
        printk("<0>Goodbye del_timer\n");
}

module_init(del_timer_init);
module_exit(del_timer_exit);

