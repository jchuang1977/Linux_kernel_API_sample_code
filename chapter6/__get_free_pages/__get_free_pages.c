/********************************************************************************
* File Name:	__get_free_pages.c
* Description:	第6章实例训练          
* Reference book:《Linux内核API完全参考手册》邱铁，周玉，邓莹莹 ，机械工业出版社.2010.9  
* E_mail:openlinux2100@gmail.com			                
*
********************************************************************************/

#include <linux/init.h> 
#include <linux/module.h> 
#include <linux/gfp.h>
MODULE_LICENSE("GPL"); 
static int __init __get_free_pages_init(void); 
static void __exit __get_free_pages_exit(void); 

unsigned long addr = 0;
int __init __get_free_pages_init(void) 
{ 
	addr = __get_free_pages( GFP_KERNEL, 3 );      //分配8个物理页
	 
	if(!addr) 
	{ 
		return -ENOMEM; 
	} 
	else 
		printk("<0>__get_free_pages Successfully!,\naddr = 0x%lx\n",addr); 

	return 0; 
}

void __exit __get_free_pages_exit(void) 
{ 
	if(addr)
	{ 
		free_pages(addr,3);                //释放所分配的物理页
		printk("<0>free_pages ok!\n"); 
	}
	printk("<0>exit!\n"); 	
}

module_init(__get_free_pages_init); 
module_exit(__get_free_pages_exit);
