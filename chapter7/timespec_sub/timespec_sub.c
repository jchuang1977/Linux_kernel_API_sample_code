/********************************************************************************
* File Name:	timespec_sub.c
* Description:	第7章实例训练          
* Reference book:《Linux内核API完全参考手册》邱铁，周玉，邓莹莹 ，机械工业出版社.2010.9  
* E_mail:openlinux2100@gmail.com			                
*
********************************************************************************/

#include <linux/module.h> 
#include<linux/time.h>
MODULE_LICENSE("GPL");
 
int __init timespec_sub_init(void) 
{
	struct timespec ts_sub;//用于保存函数timespec_sub()的返回结果

	//定义两个timespec类型的变量，作为函数的参数	
	struct timespec lhs=
	{	
		.tv_sec=10,
		.tv_nsec=110
	};
	struct timespec rhs=
	{
		.tv_sec=9,
		.tv_nsec=100		
	}; 	printk("<0>timespec_sub begin.\n");
	ts_sub=timespec_sub(lhs,rhs);	//两个时间相减，结果仍是timespec类型的变量
	printk("<0>the value of struct timespec after the timespec_sub:\n");//显示时间相减的结果
	printk("the tv_sec value is:%ld\n",ts_sub.tv_sec);
	printk("the tv_nsec value is:%ld\n",ts_sub.tv_nsec); 	
	printk("<0>timespec_sub over.\n"); 	
	return 0; 
}  

void __exit timespec_sub_exit(void) 
{         
	printk("<0>Goodbye timespec_sub\n"); 
}
 
module_init(timespec_sub_init);
module_exit(timespec_sub_exit);  
