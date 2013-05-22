/********************************************************************************
* File Name:	kmalloc.c
* Description:	第6章实例训练          
* Reference book:《Linux内核API完全参考手册》邱铁，周玉，邓莹莹 ，机械工业出版社.2010.9  
* E_mail:openlinux2100@gmail.com			                
*
********************************************************************************/

#include <linux/slab.h> 
#include <linux/init.h> 
#include <linux/module.h> 
MODULE_LICENSE("GPL"); 
static int __init kmalloc_init(void); 
static void __exit kmalloc_exit(void);

#define MEM_KMALLOC_SIZE 8092 
char * mem_spvm;

int __init kmalloc_init(void) 
{ 
	mem_spvm = (char *)kmalloc( MEM_KMALLOC_SIZE, GFP_KERNEL); 	 
	if(mem_spvm == NULL ) 
		printk("<0>kmalloc failed!\n"); 
	else 
        	/*输出分配的内存空间的起始地址*/
		printk("<0>kmalloc successfully! \naddr = 0x%lx\n",(unsigned long)mem_spvm); 

	return 0; 
}

void __exit kmalloc_exit(void) 
{ 
	if(mem_spvm != NULL) 
    	{
		kfree(mem_spvm); 
	   	printk("<0>kfree ok!\n"); 
	}
	printk("<0>exit !\n"); 
}

module_init(kmalloc_init); 
module_exit(kmalloc_exit); 