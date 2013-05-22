/********************************************************************************
* File Name:	do_gettimeofday.c
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
	printk("<0>do_gettimeofday test begin.\n");
	
		struct timeval now={
		
			.tv_sec=0,
		
			.tv_usec=0	
		
		};//声明一个变量
	
	do_gettimeofday(&now);//调用函数获取时间，此时间是距离1970-01-01 00:00:00的时间
	 
	//显示当前时间
	
	printk("<0>the seconds of the day is: %ld\n",now.tv_sec);//秒数
	
	printk("<0>the microseconds of the day is: %ld\n",now.tv_usec);//微秒数
	printk("<0>do_gettimeofday test over.\n");
	return 0;
}

void __exit timer_exit(void)
{
        printk("<1>Goodbye  do_gettimeofday test\n");
}

module_init(timer_init);

module_exit(timer_exit);

