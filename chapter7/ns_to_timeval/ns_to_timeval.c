/********************************************************************************
* File Name:	ns_to_timeval.c
* Description:	第7章实例训练          
* Reference book:《Linux内核API完全参考手册》邱铁，周玉，邓莹莹 ，机械工业出版社.2010.9  
* E_mail:openlinux2100@gmail.com			                
*
********************************************************************************/

#include <linux/module.h>
#include<linux/time.h>

MODULE_LICENSE("GPL");


int __init ns_to_timeval_init(void)
{
	
	struct timeval tv;  //声明变量，用于保存函数执行结果 
	
	const s64 nsec=1001000000;     //-1001000000，定义64位有符号整数，作为函数的参数
	printk("<0>ns_to_timeval begin.\n");
	
	tv=ns_to_timeval(nsec);//调用函数，将参数表示的时间转换成用timeval表示的时间
	
	printk("the value of the struct timeval is:\n");
	
	printk("the tv_sec value is:%ld\n",tv.tv_sec);//秒数
	
	printk("the tv_usec value is:%ld\n",tv.tv_usec);//微秒数
	
	printk("<0>ns_to_timeval over.\n");
	return 0;
}

void __exit ns_to_timeval_exit(void)
{
        printk("<1>Goodbye ns_to_timeval\n");
}


module_init(ns_to_timeval_init);

module_exit(ns_to_timeval_exit);
