/********************************************************************************
* File Name:	use_module.c
* Description:	第2章实例训练          
* Reference book:《Linux内核API完全参考手册》邱铁，周玉，邓莹莹 ，机械工业出版社.2010.9  
* E_mail:openlinux2100@gmail.com			                
*
********************************************************************************/

#include <linux/module.h>
#include <linux/init.h>

MODULE_LICENSE("GPL"); 

static int __init use_module_init(void); 
static void __exit use_module_exit(void);

static struct module * b;

int __init use_module_init(void) 
{ 
	const char *name = "test_module";  //定义待查找的模块名为“test_module”
	b = find_module( name );  //调用查找模块函数
	
	if( b != NULL )
	{
        	/*调用use_module ( )函数之前，输出模块test_moudule的引用计数*/
        	printk("<0>before calling use_module,\n");
		printk("<0>refs of %s is: %d\n",name,module_refcount( b ));	

		int ret = use_module( THIS_MODULE, b ); 

		printk("<0>ret = %d\n",ret);  //输出函数的返回值
		/*调用use_module ( )函数之前，输出模块test_moudule的引用计数*/
		printk("<0>after calling use_module,\n");		
		printk("<0>refs of %s is: %d\n",name,module_refcount( b ));
	}	
	else
	{
		printk("<0>find %s failed!",name);
	}
	return 0; 
}


void __exit use_module_exit(void) 
{ 
	printk("<0>module exit ok!\n"); 
}

module_init(use_module_init); 
module_exit(use_module_exit); 
