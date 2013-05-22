/********************************************************************************
* File Name:	find_module.c
* Description:	第2章实例训练          
* Reference book:《Linux内核API完全参考手册》邱铁，周玉，邓莹莹 ，机械工业出版社.2010.9  
* E_mail:openlinux2100@gmail.com			                
*
********************************************************************************/

#include <linux/module.h>
#include <linux/init.h>
MODULE_LICENSE("GPL"); 
static int __init find_module_init(void); 
static void __exit find_module_exit(void);

int __init find_module_init(void) 
{ 
	const char *name = "udf";  //定义待查找的模块名为“udf”
	struct module * fmodule = find_module( name );  //调用查找模块函数

   	 /* 如果查找成功，则输出该模块的信息 */
	if( fmodule != NULL )
	{
		printk("<0>fmodule->name: %s\n",fmodule->name);   //输出模块名
		printk("<0>fmodule->state: %d\n",fmodule->state);    //输出模块状态
        	/* 输出模块core段所占空间大小 */
		printk("<0>fmodule->core_size: %d\n",fmodule->core_size);  
        	/*输出模块引用计数 */
		printk("<0>module_refcount(fmodule): %d\n",module_refcount(fmodule)); 
	}

	name = "crc_itu_t";  //模块名
	fmodule = find_module( name );   //调用查找模块函数
	
	/* 如果查找成功，则输出该模块的信息 */
	if( fmodule != NULL )
	{
		printk("<0>fmodule->name: %s\n",fmodule->name);   //输出模块名
		printk("<0>fmodule->state: %d\n",fmodule->state);    //输出模块状态
        	/* 输出模块core段所占空间大小 */
		printk("<0>fmodule->core_size: %d\n",fmodule->core_size);   
        	/*输出模块引用计数 */
		printk("<0>module_refcount(fmodule): %d\n",module_refcount(fmodule));
	}

	return 0; 
}


void __exit find_module_exit(void) 
{ 
	printk("<0>module exit ok!\n"); 
}

module_init(find_module_init); 
module_exit(find_module_exit); 
