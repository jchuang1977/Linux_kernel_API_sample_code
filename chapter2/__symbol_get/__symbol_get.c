/********************************************************************************
* File Name:	__symbol_get.c
* Description:	第2章实例训练          
* Reference book:《Linux内核API完全参考手册》邱铁，周玉，邓莹莹 ，机械工业出版社.2010.9  
* E_mail:openlinux2100@gmail.com			                
*
********************************************************************************/

#include <linux/module.h>
#include <linux/init.h>
MODULE_LICENSE("GPL"); 
static int __init __symbol_get_init(void); 
static void __exit __symbol_get_exit(void);

int __init __symbol_get_init(void) 
{ 
	const char * symbol_name ;
	void * addr;

	symbol_name = "symbol_A";  //内核符号名为“symbol_A”
	addr = __symbol_get( symbol_name );
	
	if( addr != NULL )
		printk("<0>the address of %s is: %lx\n",symbol_name, (unsigned long)addr);
	else
		printk("<0>%s isn't found\n",symbol_name);

	symbol_name = "symbol_0";  //内核符号名为“symbol_0”
	addr = __symbol_get( symbol_name );
	
	if( addr != NULL )
		printk("<0>the address of %s is: %lx\n",symbol_name, (unsigned long)addr);
	else
		printk("<0>%s isn't found\n",symbol_name);

	return 0; 
}

void __exit __symbol_get_exit(void) 
{ 
	printk("<0>module exit ok!\n"); 
}

module_init(__symbol_get_init); 
module_exit(__symbol_get_exit); 
