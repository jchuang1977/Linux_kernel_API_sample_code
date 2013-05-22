/********************************************************************************
* File Name:	mktime.c
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
	printk("mktime test begin\n");
	//调用函数mktime将时间换算成秒
	unsigned long result1=mktime(2010,2,11,9,52,10);
	unsigned long result2=mktime(2010,2,11,9,52,12);
        //显示函数调用结果
	printk("the result1 is :%ld\n",result1);
	printk("the result2 is :%ld\n",result2);
	return 0;
}

void __exit timer_exit(void)
{
        printk("<0>Goodbye mktime\n");
}

module_init(timer_init);
module_exit(timer_exit);


