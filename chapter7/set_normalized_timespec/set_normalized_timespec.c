/********************************************************************************
* File Name:	set_normalized_timespec.c
* Description:	第7章实例训练          
* Reference book:《Linux内核API完全参考手册》邱铁，周玉，邓莹莹 ，机械工业出版社.2010.9  
* E_mail:openlinux2100@gmail.com			                
*
********************************************************************************/

#include <linux/module.h>
#include<linux/time.h>
MODULE_LICENSE("GPL");

int __init timer_init(void)
{
	struct timespec ts=
	{
		.tv_sec=0,
		.tv_nsec=0
	};//定义变量，作为函数的第一个参数
	printk("<0>set_normalized_timespec begin.\n");
	printk("<0>the value of struct timespec before the set_normalized_timespec:\n");
	printk("the tv_sec value is:%ld\n",ts.tv_sec); //显示函数调用之前结构体变量表示的时间值
	printk("the tv_nsec value is:%ld\n",ts.tv_nsec);
	set_normalized_timespec(&ts,1,1000000010L);//调用函数，更改结构体变量表示的时间值
	printk("<0>the value of struct timespec after the set_normalized_timespec:\n");
	printk("the tv_sec value is:%ld\n",ts.tv_sec);//显示函数调用之后结构体变量表示的时间值
	printk("the tv_nsec value is:%ld\n",ts.tv_nsec);
	printk("<0>set_normalized_timespec over.\n");
	return 0;
}

void __exit timer_exit(void)
{
        printk("<1>Goodbye set_normalized_timespec\n");
}

module_init(timer_init);
module_exit(timer_exit);

