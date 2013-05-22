/********************************************************************************
* File Name:	timespec_add_ns.c
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
	printk("<0>timespec_add_ns begin.\n");
	struct timespec ts={
		.tv_sec=1,
		.tv_nsec=1
	}; //声明变量，函数的第一个参数
	u64 ns=1000000001;//64位无符号整数，函数的第二个参数
	printk("the value of the timespec before timespec_add_ns\n");
	printk("the tv_sec of the timespec is:%ld\n",ts.tv_sec); //显示参与加之前的数据
	printk("the tv_nsec of the timespec is:%ld\n",ts.tv_nsec);
	printk("the add ns is:%lld\n",ns);	
	timespec_add_ns(&ts,ns);//调用函数实现结构体变量与加整数的相加	
	printk("the value of timespec after the timespec_add_ns :\n");//显示参与加之后的数据
	printk("the new tv_sec of the timespec is:%ld\n",ts.tv_sec);
	printk("the new tv_nsec of the timespec is:%ld\n",ts.tv_nsec);
	printk("<0>timespec_add_ns over.\n");
	return 0;
}

void __exit timer_exit(void)
{
        printk("<1>Goodbye timespec_add_ns\n");
}

module_init(timer_init);
module_exit(timer_exit);

