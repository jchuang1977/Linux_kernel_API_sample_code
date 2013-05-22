/********************************************************************************
* File Name:	timespec_equal.c
* Description:	第7章实例训练          
* Reference book:《Linux内核API完全参考手册》邱铁，周玉，邓莹莹 ，机械工业出版社.2010.9  
* E_mail:openlinux2100@gmail.com			                
*
********************************************************************************/

#include <linux/module.h> 
#include<linux/time.h>
MODULE_LICENSE("GPL");
 
int __init timespec_equal_init(void) 
{
	int result_equ;//用于保存函数timespec_equ()的返回结果

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
	}; 	
	printk("<0>timespec_equal begin.\n");
	result_equ=timespec_equal(&lhs,&rhs); //判断时间是否相同
	printk("the timespec equal result is: %d\n",result_equ);//显示时间是否相等的结果 	
	printk("<0>timespec_equal over.\n"); 	
	return 0; 
}  

void __exit timespec_equal_exit(void) 
{         
	printk("<0>Goodbye timespec_equal\n"); 
}

module_init(timespec_equal_init);
module_exit(timespec_equal_exit);  
