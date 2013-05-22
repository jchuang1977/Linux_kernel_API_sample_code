/********************************************************************************
* File Name:	module_is_live.c
* Description:	第2章实例训练          
* Reference book:《Linux内核API完全参考手册》邱铁，周玉，邓莹莹 ，机械工业出版社.2010.9  
* E_mail:openlinux2100@gmail.com			                
*
********************************************************************************/

#include <linux/module.h>
#include <linux/init.h>

MODULE_LICENSE("GPL"); 
static int __init module_is_live_init(void); 
static void __exit module_is_live_exit(void);

static int ret;

int __init module_is_live_init(void) 
{ 
	ret = module_is_live(THIS_MODULE);  //参数为当前模块

	if( ret == 1 )
		printk("<0>in init,state is:not GOING!\n");	
	else
		printk("<0>in init,state is:GOING\n");	

	return 0; 
}

void __exit module_is_live_exit(void) 
{ 
	ret = module_is_live(THIS_MODULE);  //参数为当前模块

	if( ret == 1 )
		printk("<0>in exit,state is:not GOING!\n");	
	else
		printk("<0>in exit,state is:GOING\n");

	printk("<0>module exit ok!\n"); 
}


module_init(module_is_live_init); 
module_exit(module_is_live_exit); 
