/********************************************************************************
* File Name:	try_module_get.c
* Description:	第2章实例训练          
* Reference book:《Linux内核API完全参考手册》邱铁，周玉，邓莹莹 ，机械工业出版社.2010.9  
* E_mail:openlinux2100@gmail.com			                
*
********************************************************************************/

#include <linux/module.h>
#include <linux/init.h>

MODULE_LICENSE("GPL"); 

static int __init try_module_get_init(void); 
static void __exit try_module_get_exit(void);

int __init try_module_get_init(void) 
{
	int ret ;
	const char * name;
	struct module * fmodule;

	name = "test_module";  //定义待查找的模块名为“test_module”
	fmodule = find_module( name );  //调用查找模块函数

	if( fmodule != NULL )
	{
		printk("<0>before calling try_module_get,\n");
		printk("<0>refs of %s is: %d\n",name, module_refcount(fmodule));

		ret = try_module_get(fmodule);

		printk("<0>after calling try_module_get,\n");
		printk("<0>ret = %d\n",ret);
		printk("<0>refs of %s is: %d\n",name, module_refcount(fmodule));
	}

	return 0; 
}

void __exit try_module_get_exit(void) 
{ 
	printk("<0>module exit ok!\n"); 
}

module_init(try_module_get_init); 
module_exit(try_module_get_exit); 
