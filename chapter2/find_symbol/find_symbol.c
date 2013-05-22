/********************************************************************************
* File Name:	find_symbol.c
* Description:	第2章实例训练          
* Reference book:《Linux内核API完全参考手册》邱铁，周玉，邓莹莹 ，机械工业出版社.2010.9  
* E_mail:openlinux2100@gmail.com			                
*
********************************************************************************/

#include <linux/module.h>
#include <linux/init.h>

MODULE_LICENSE("GPL"); 
static int __init find_symbol_init(void); 
static void __exit find_symbol_exit(void);

int __init find_symbol_init(void) 
{ 
	const char * name = "symbol_A";  //待查找的内核符号的名字
	struct kernel_symbol * ksymbol ;  //用于接收测试函数返回值
	struct module * owner;  //内核符号所属的模块
	const unsigned long *crc; 
	bool gplok = true; 
	bool warn = true;
	
	ksymbol = find_symbol(name,&owner,&crc,gplok,warn);

    if( ksymbol != NULL )
	{
        	/*输出查找到的内核符号在内存中的地址*/
		printk("<0>ksymbol->value : %lx\n",ksymbol->value);  
		printk("<0>ksymbol->name : %s\n",ksymbol->name);   //输出内核符号名字
	}
	else
		printk("<0>Failed to find symbol %s\n", name);

	if( owner != NULL )
	{
        	/*输出内核符号所属的模块的名字*/
		printk("<0>owner->name : %s\n",owner->name);  
	}
	if( crc != NULL )
	{
		printk("<0>*crc : %lx\n",*crc);
	}
	return 0;

	
}

void __exit find_symbol_exit(void) 
{ 
	printk("<0>module exit ok!\n"); 
}

module_init(find_symbol_init); 
module_exit(find_symbol_exit); 
