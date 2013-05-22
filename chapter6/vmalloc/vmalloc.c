/********************************************************************************
* File Name:	vmalloc.c
* Description:	第6章实例训练          
* Reference book:《Linux内核API完全参考手册》邱铁，周玉，邓莹莹 ，机械工业出版社.2010.9  
* E_mail:openlinux2100@gmail.com			                
*
********************************************************************************/

#include <linux/vmalloc.h> 
#include <linux/init.h> 
#include <linux/module.h> 
MODULE_LICENSE("GPL"); 
static int __init vmalloc1_init(void); 
static void __exit vmalloc1_exit(void); 

#define MEM_VMALLOC_SIZE 8092 
char * mem_spvm;

int __init vmalloc1_init(void) 
{ 
	mem_spvm = (char *)vmalloc(MEM_VMALLOC_SIZE); 	 
	if(mem_spvm == NULL ) 
		printk("<0>vmalloc failed!\n"); 
	else 
		printk("<0>vmalloc successfully! addr = 0x%lx\n",(unsigned long)mem_spvm); 	 
	return 0; 
}

void __exit vmalloc1_exit(void) 
{ 
	if(mem_spvm != NULL)
	{ 
		vfree(mem_spvm); 
		printk("<0>vfree succeed!\n");
	}

	printk("<0>exit !\n"); 
}

module_init(vmalloc1_init); 
module_exit(vmalloc1_exit);
