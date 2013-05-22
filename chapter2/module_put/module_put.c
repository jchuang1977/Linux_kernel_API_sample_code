/********************************************************************************
* File Name:	module_put.c
* Description:	第2章实例训练          
* Reference book:《Linux内核API完全参考手册》邱铁，周玉，邓莹莹 ，机械工业出版社.2010.9  
* E_mail:openlinux2100@gmail.com			                
*
********************************************************************************/

#include <linux/module.h>
#include <linux/init.h>

MODULE_LICENSE("GPL"); 

static int __init module_put_init(void); 
static void __exit module_put_exit(void);

int __init module_put_init(void) 
{ 
	const char *name = "test_module";  //定义待查找的模块名为“test_module”
	struct module * fmodule = find_module( name );  //调用查找模块函数
	
	if( fmodule != NULL )
	{
        	/*调用module_put( )函数之前，输出模块test_moudule的引用计数*/
		printk("<0>before calling module_put,\n");
		printk("<0>refs of %s is: %d\n",name,module_refcount(fmodule));

		module_put(fmodule);   //调用module_put( )函数
   
        	/*调用module_put( )函数之前，输出模块test_moudule的引用计数*/
		printk("<0>after calling module_put,\n");
		printk("<0>refs of %s is: %d\n",name,module_refcount(fmodule));
	}
	else
	{
		printk("<0>find %s failed!",name);
	}

	return 0;
}


void __exit module_put_exit(void) 
{ 
	printk("<0>module exit ok!\n"); 
}

module_init(module_put_init); 
module_exit(module_put_exit); 
