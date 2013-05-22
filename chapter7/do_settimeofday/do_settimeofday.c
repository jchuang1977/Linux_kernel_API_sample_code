/********************************************************************************
* File Name:	do_settimeofday.c
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
	printk("<0>do_settimeofday test begin.\n");
	struct timespec now={
		.tv_sec=0,    //0
		.tv_nsec=0  //1000000000,0	
		};//声明变量，用于表示想设定的时间	
	int result=do_settimeofday(&now);//调用函数更改系统内核时间
	if(result==0) //更该时间成功
	{	
		struct timespec new_now=
		{	
			.tv_sec=0,
			.tv_nsec=0
		};
		getnstimeofday(&new_now); //获取更改之后的系统内核时间
		printk("set time of the day success,the result is:\n");
		printk("the new seconds of the day is:%ld\n",new_now.tv_sec);//显示更改之后的系统内核时间，秒数
		printk("the new nanoseconds of the day is:%ld\n",new_now.tv_nsec);//微秒数
	}
	else   //更改时间失败
		printk("set time of the day failed!\n");
	printk("<0>do_settimeofday test over.\n");
	return 0;
}

void __exit timer_exit(void)
{
        printk("<1>Goodbye  do_settimeofday test\n");
}

module_init(timer_init);
module_exit(timer_exit);

