/********************************************************************************
* File Name:	__module_text_address.c
* Description:	第2章实例训练          
* Reference book:《Linux内核API完全参考手册》邱铁，周玉，邓莹莹 ，机械工业出版社.2010.9  
* E_mail:openlinux2100@gmail.com			                
*
********************************************************************************/

#include <linux/module.h>
#include <linux/init.h>
MODULE_LICENSE("GPL"); 
static int __init __module_text_address_init(void); 
static void __exit __module_text_address_exit(void);

int fun_a()
{
	return 0;
}

static int var_b = 4;

int __init __module_text_address_init(void) 
{ 
	unsigned long addr = (unsigned long)fun_a;  //addr 为函数fun_a的入口地址
	
	struct module * ret ;

	preempt_disable();   //禁止抢占
	ret = __module_text_address(addr) ;
	preempt_enable();  //允许抢占

	/* 如果查找成功，则输出该模块的信息 */
	printk("<0>it's about fun_a:\n");
	if( ret != NULL )
	{
		printk("<0>ret->name: %s\n",ret->name);   //输出模块名
		printk("<0>ret->state: %d\n",ret->state);    //输出模块状态
        	/* 输出模块core段所占空间大小 */
		printk("<0>ret->core_size: %d\n",ret->core_size);  
	}	
	else
	{
		printk("<0>fun_a is not in text area!\n");
	}	

	addr = (unsigned long)&var_b;  //addr 为静态全局变量var_b的地址
	
	preempt_disable();
	ret = __module_text_address(addr) ;
	preempt_enable();

	/* 如果查找成功，则输出该模块的信息 */
	printk("<0>\nit's about var_b:\n");
	if( ret != NULL )
	{
		printk("<0>ret->name: %s\n",ret->name);   //输出模块名
		printk("<0>ret->state: %d\n",ret->state);    //输出模块状态
        	/* 输出模块core段所占空间大小 */
		printk("<0>ret->core_size: %d\n",ret->core_size);  
	}	
	else
	{
		printk("<0>var_b is not in text area!\n");
	}

	return 0; 
}


void __exit __module_text_address_exit(void) 
{ 
	printk("<0>module exit ok!\n"); 
}

module_init(__module_text_address_init); 
module_exit(__module_text_address_exit); 
