/********************************************************************************
* File Name:	__symbol_put.c
* Description:	第2章实例训练          
* Reference book:《Linux内核API完全参考手册》邱铁，周玉，邓莹莹 ，机械工业出版社.2010.9  
* E_mail:openlinux2100@gmail.com			                
*
********************************************************************************/

#include <linux/module.h>
#include <linux/init.h>
MODULE_LICENSE("GPL"); 
static int __init __symbol_put_init(void); 
static void __exit __symbol_put_exit(void);

int __init __symbol_put_init(void) 
{ 
	const char * symbol_name ;	
	const char * mod_name ;
	struct module * fmodule ;

	symbol_name = "symbol_A";
	mod_name = "test_module";  //定义待查找的模块名为“test_module”
	fmodule = find_module( mod_name );  //调用查找模块函数

	if(fmodule != NULL )
	{
		printk("<0>before calling __symbol_put,\n");
		printk("<0>ref of %s is: %d\n",mod_name, module_refcount(fmodule));

		__symbol_put(symbol_name); //will dec the count

		printk("<0>after calling __symbol_put,\n");
		printk("<0>ref of %s is: %d\n",mod_name, module_refcount(fmodule));
	}
	else
	{
		printk("<0>find %s failed!\n", mod_name );
	}

	return 0; 
}

void __exit __symbol_put_exit(void) 
{ 
	printk("<0>module exit ok!\n"); 
}

module_init(__symbol_put_init); 
module_exit(__symbol_put_exit); 
