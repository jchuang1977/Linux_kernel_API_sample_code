/********************************************************************************
* File Name:	vmalloc_user.c
* Description:	第6章实例训练          
* Reference book:《Linux内核API完全参考手册》邱铁，周玉，邓莹莹 ，机械工业出版社.2010.9  
* E_mail:openlinux2100@gmail.com			                
*
********************************************************************************/

#include <linux/init.h> 
#include <linux/module.h> 
#include <linux/security.h> 
#include <linux/vmalloc.h> 
#include <linux/mm.h> 
MODULE_LICENSE("GPL"); 
static int __init vmalloc_user_init(void); 
static void __exit vmalloc_user_exit(void); 

#define VMALLOC_user_SIZE 8092 
char * addr;

int __init vmalloc_user_init(void) 
{ 
	addr = (char *)vmalloc_user(VMALLOC_user_SIZE);	 
	if( addr == NULL ) 
		printk("<0>vmalloc failed!\n"); 
	else 
	{ 
		printk("<0>vmalloc successfully! addr = %lx\n",(unsigned long)addr); 		 
		printk("<0> *addr = %d\n",*addr); 
		printk("<0> *(addr+50) = %d\n",*(addr+50)); 
	}	 
	return 0; 
}

void __exit vmalloc_user_exit(void) 
{ 
	if(addr != NULL) 
		vfree( addr ); 
	printk("<0>exit!\n"); 
}

module_init(vmalloc_user_init); 
module_exit(vmalloc_user_exit); 

