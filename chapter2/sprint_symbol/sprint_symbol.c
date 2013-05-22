/********************************************************************************
* File Name:	sprint_symbol.c
* Description:	第2章实例训练          
* Reference book:《Linux内核API完全参考手册》邱铁，周玉，邓莹莹 ，机械工业出版社.2010.9  
* E_mail:openlinux2100@gmail.com			                
*
********************************************************************************/

#include <linux/module.h>
#include <linux/init.h>
#include <linux/kallsyms.h>
MODULE_LICENSE("GPL"); 
static int __init sprint_symbol_init(void); 
static void __exit sprint_symbol_exit(void);

//符号a_symbol
int a_symbol()
{
	return 1;
}
EXPORT_SYMBOL(a_symbol);

int __init sprint_symbol_init(void) 
{ 
	char buffer[KSYM_SYMBOL_LEN];     //声明一个文本缓冲区
	int ret;                          //接收sprint_symbol( )函数返回值
	unsigned long address;            //表示符号地址
	char * name;                      //模块名字
	struct module * fmodule = NULL;  //指向一个模块的指针

	address = (unsigned long) __builtin_return_address(0);  //当前函数的返回地址
	
	ret = sprint_symbol( buffer , address );
	printk("<0>ret: %d\n", ret );          //输出返回值
	printk("<0>buffer: %s\n", buffer );    //输出文本缓冲区 buffer 的内容
	printk("<0>\n");

	name = "vboxvideo";           
	fmodule = find_module( name );   //查找模块名为　"vboxvideo"　的模块
	
	if( fmodule != NULL )
	{
		printk("<0>fmodule->name: %s\n",fmodule->name);
		address = (unsigned long)fmodule->module_core;     //将模块的内存起始地址赋值给 address
		ret = sprint_symbol( buffer , address );			
		printk("<0>ret: %d\n", ret );
		printk("<0>buffer: %s\n", buffer );
	}

	printk("<0>\n");


	address = (unsigned long)a_symbol + 5;  //将当前模块中符号 a_symbol 的地址加上偏移量 5 赋值给 address
	ret = sprint_symbol( buffer , address );
	printk("<0>ret: %d\n", ret );
	printk("<0>buffer: %s\n", buffer );

	return 0; 
}

void __exit sprint_symbol_exit(void) 
{ 
	printk("<0>module exit ok!\n"); 
}

module_init(sprint_symbol_init); 
module_exit(sprint_symbol_exit); 
