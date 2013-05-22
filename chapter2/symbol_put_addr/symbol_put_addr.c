/********************************************************************************
* File Name:	symbol_put_addr.c
* Description:	第2章实例训练          
* Reference book:《Linux内核API完全参考手册》邱铁，周玉，邓莹莹 ，机械工业出版社.2010.9  
* E_mail:openlinux2100@gmail.com			                
*
********************************************************************************/

#include <linux/module.h>
#include <linux/init.h>
MODULE_LICENSE("GPL"); 
static int __init symbol_put_addr_init(void); 
static void __exit symbol_put_addr_exit(void);

int __init symbol_put_addr_init(void) 
{ 
	const char * symbol_name ;
	const char * mod_name ;
	struct module * fmodule ;
	void * addr;

	symbol_name = "symbol_A";
	addr = __symbol_get( symbol_name );
	
	if( addr != NULL )
	{
		printk("<0>addr : %lx \n", (unsigned long)addr );

		mod_name = "test_module";  //定义待查找的模块名为“test_module”
		fmodule = find_module( mod_name );  //调用查找模块函数

		if(fmodule != NULL )
		{
			printk("<0>before calling symbol_put_addr,\n");
			printk("<0>refs of %s is: %d\n",mod_name, module_refcount(fmodule));

			symbol_put_addr( addr ); //will dec the count

			printk("<0>after calling symbol_put_addr,\n");
			printk("<0>refs of %s is: %d\n",mod_name, module_refcount(fmodule));
		}
		else
		{
			printk("<0>find %s failed!\n", mod_name );
		}
	}
	else
	{
		printk("<0>%s isn't found\n",symbol_name);
	}
	return 0; 
}


void __exit symbol_put_addr_exit(void) 
{ 
	printk("<0>module exit ok!\n"); 
}

module_init(symbol_put_addr_init); 
module_exit(symbol_put_addr_exit); 
