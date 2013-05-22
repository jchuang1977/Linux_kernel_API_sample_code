/********************************************************************************
* File Name:	timeval_to_ns.c
* Description:	第7章实例训练          
* Reference book:《Linux内核API完全参考手册》邱铁，周玉，邓莹莹 ，机械工业出版社.2010.9  
* E_mail:openlinux2100@gmail.com			                
*
********************************************************************************/

#include <linux/module.h> 
#include<linux/time.h>
MODULE_LICENSE("GPL");
 
int __init timeval_to_ns_init(void) 
{
	printk("<0>timeval_to_ns begin.\n");
	struct timeval tv={
		.tv_sec=1,
		.tv_usec=1
	};//定义变量，用作函数参数
	s64 ns=timeval_to_ns(&tv); //调用函数将timeval类型的变量表示的时间转换成纳秒
	printk("the tv_sec of the timeval is:%ld\n",tv.tv_sec); //显示变量的秒数
	printk("the tv_usec of the timeval is:%ld\n",tv.tv_usec);//显示变量的微秒数
	printk("the result of the timeval_to_ns is:%lld\n",ns);//显示转换结果，纳秒
	printk("<0>timeval_to_ns over.\n"); 	
	return 0; 
}  

void __exit timeval_to_ns_exit(void) 
{         
	printk("<0>Goodbye timeval_to_ns\n"); 
}

module_init(timeval_to_ns_init);
module_exit(timeval_to_ns_exit);  
