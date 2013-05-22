/********************************************************************************
* File Name:	page_address.c
* Description:	第6章实例训练          
* Reference book:《Linux内核API完全参考手册》邱铁，周玉，邓莹莹 ，机械工业出版社.2010.9  
* E_mail:openlinux2100@gmail.com			                
*
********************************************************************************/

#include <linux/init.h>
#include <linux/module.h>
#include <linux/mm.h>
MODULE_LICENSE("GPL");

static int __init _page_address_init(void);
static void __exit page_address_exit(void);

struct page * page = NULL;


int __init _page_address_init(void)
{
	page = alloc_pages(GFP_KERNEL, 0);      //分配一个物理页   		
	if(!page)
	{ 		
		printk("<0>alloc_pages failed!\n");
		return -ENOMEM; 	
	} 	
	else 	
	{ 
		printk("<0>addr = 0x%lx\n",(unsigned long)page);
		printk("<0>virtual addr = 0x%lx\n",(unsigned long)page_address(page));   //输出该page的逻辑地址 	
	}		 	
	return 0; 
}

void __exit page_address_exit(void) 
{ 	
	if(page) 		
		__free_pages(page,0);            //释放分配的物理页
	printk("<0>exit!\n");
}

module_init(_page_address_init);
module_exit(page_address_exit);
