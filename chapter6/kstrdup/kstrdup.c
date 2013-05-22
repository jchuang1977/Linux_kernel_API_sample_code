/********************************************************************************
* File Name:	kstrdup.c
* Description:	第6章实例训练          
* Reference book:《Linux内核API完全参考手册》邱铁，周玉，邓莹莹 ，机械工业出版社.2010.9  
* E_mail:openlinux2100@gmail.com			                
*
********************************************************************************/

#include <linux/string.h> 
#include <linux/init.h> 
#include <linux/module.h> 

MODULE_LICENSE("GPL"); 
static int __init kstrdup_init(void); 
static void __exit kstrdup_exit(void);

int __init kstrdup_init(void) 
{ 
	const char *s = "hello world!";                 //定义一个常量字符串 
	char * addr = kstrdup( s, GFP_KERNEL);          //调用函数，分配模式为GFP_KERNEL 
	printk("<0>addr = 0x%lx\n",(unsigned long)addr);   //将字符串s拷贝到内存中的起始地址 
	printk("<0>*addr = %c\n",*addr);                   //输出第一个字符 
	printk("<0>*addr+4 = %c\n",*(addr+4));             //输出第五个字符 
	char * temp; 
	for(temp = addr; *temp !='\0'; temp ++)         //循环地址中的字符值 
		printk("%c",*temp); 
	return 0; 
}

void __exit kstrdup_exit(void) 
{ 
	printk("<0>exit ok!\n"); 
}

module_init(kstrdup_init); 
module_exit(kstrdup_exit);