/********************************************************************************
* File Name:	current_kernel_time.c
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
	printk("<0>current_kernel_time test begin.\n");
	
		
	struct timespec now=current_kernel_time();//调用函数获得当前系统内核时间
	
	printk("<0>the seconds of the current kernel time is: %ld\n",now.tv_sec);//显示当前系统内核的秒数
	
	printk("<0>the nanoseconds of the current kernel time is:%ld\n",now.tv_nsec);//显示当前系统内核的纳秒数
	printk("<0>current_kernel_time test over.\n");
	return 0;
}

void __exit timer_exit(void)
{
        printk("<1>Goodbye  current_kernel_time test\n");
}

module_init(timer_init);

module_exit(timer_exit);

