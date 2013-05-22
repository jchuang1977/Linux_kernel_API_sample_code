/********************************************************************************
* File Name:	get_seconds.c
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
	printk("<0>get_seconds begin.\n");
	unsigned long result=get_seconds();//调用函数获得系统内核时间（秒数）
	printk("the get_seconds result is: %lu\n",result);//显示内核时间（秒数）
	printk("<0>get_seconds over.\n");
	return 0;
}

void __exit timer_exit(void)
{
        printk("<1>Goodbye  get_seconds\n");
}

module_init(timer_init);
module_exit(timer_exit);

