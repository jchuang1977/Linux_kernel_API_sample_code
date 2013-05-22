/********************************************************************************
* File Name:	module_refcount.c
* Description:	第2章实例训练          
* Reference book:《Linux内核API完全参考手册》邱铁，周玉，邓莹莹 ，机械工业出版社.2010.9  
* E_mail:openlinux2100@gmail.com			                
*
********************************************************************************/

#include <linux/module.h>
#include <linux/init.h>
MODULE_LICENSE("GPL"); 
static int __init module_refcount_init(void); 
static void __exit module_refcount_exit(void);

int __init module_refcount_init(void) 
{ 
	const char *name = "snd_seq_device"; //字符串常量，表示一个模块名字
	/* 查找名为name 的模块 */
	struct module * fmodule = find_module( name );

	/* 输出名为name 的模块的信息 */
	if( fmodule != NULL )
	{
		printk("<0>fmodule->name: %s\n",fmodule->name);
		printk("<0>module_refcount(fmodule): %d\n",module_refcount(fmodule));
	}
	
	/* 输出当前模块的信息 */
	printk("<0>THIS_MODULE->name: %s\n",THIS_MODULE->name);
	printk("<0>module_refcount(THIS_MODULE): %d\n",module_refcount(THIS_MODULE));

	return 0; 
}

void __exit module_refcount_exit(void) 
{ 
	printk("<0>module exit ok!\n"); 
}

module_init(module_refcount_init); 
module_exit(module_refcount_exit); 
