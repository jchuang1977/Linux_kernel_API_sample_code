/********************************************************************************
* File Name:	kzalloc.c
* Description:	第6章实例训练          
* Reference book:《Linux内核API完全参考手册》邱铁，周玉，邓莹莹 ，机械工业出版社.2010.9  
* E_mail:openlinux2100@gmail.com			                
*
********************************************************************************/

#include <linux/slab.h>
#include <linux/init.h> 
#include <linux/module.h> 
MODULE_LICENSE("GPL"); 
static int __init kzalloc_init(void); 
static void __exit kzalloc_exit(void); 

#define MEM_KZALLOC_SIZE 8092 
char * mem_spvm;

int __init kzalloc_init(void) 
{  
    	//调用kzalloc分配一个内存空间
	mem_spvm = (char *)kzalloc(MEM_KZALLOC_SIZE, GFP_KERNEL);  

	if(mem_spvm == NULL ) 
		printk("<0>kzalloc failed!\n"); 
	else 
	{ 
		printk("<0>kzalloc successfully! addr = %lx\n",(unsigned long)mem_spvm ); 
		printk("<0>the content of mem_spvm+2 is: %d\n",*(mem_spvm+2)); 
		printk("<0>the content of mem_spvm+500 is: %d\n",*(mem_spvm+500)); 
	} 	 
	return 0; 
}

void __exit kzalloc_exit(void) 
{ 
	if(mem_spvm != NULL) 
	{ 
		kfree(mem_spvm); //释放由kzalloc( )所分配的内存空间
		printk("<0>kfree ok!\n"); 
	} 
	printk("<0>exit!\n"); 
}

module_init(kzalloc_init); 
module_exit(kzalloc_exit); 