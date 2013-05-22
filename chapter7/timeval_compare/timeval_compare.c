/********************************************************************************
* File Name:	timeval_compare.c
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
	struct timeval lhs=
	{
		.tv_sec=1,
		.tv_usec=9999
	};//定义变量，当作函数的第一个参数
	struct timeval rhs=
	{
		.tv_sec=1,
		.tv_usec=1000
	};//定义变量，当作函数的第二个参数
	printk("<0>timeval_compare begin.\n");
	int result=timeval_compare(&lhs,&rhs);//调用函数，比较两个时间的大小
	printk("the timeval compare result is: %d\n",result);//显示比较结果
	printk("<0>timeval_compare over.\n");
	return 0;
}

void __exit timer_exit(void)
{
        printk("<1>Goodbye  timeval_compare\n");
}

module_init(timer_init);
module_exit(timer_exit);

