/********************************************************************************
* File Name:	kmap_high.c
* Description:	第6章实例训练          
* Reference book:《Linux内核API完全参考手册》邱铁，周玉，邓莹莹 ，机械工业出版社.2010.9  
* E_mail:openlinux2100@gmail.com			                
*
********************************************************************************/

#include <asm/highmem.h>
#include <linux/init.h> 
#include <linux/module.h> 
#include <linux/page-flags.h> 
MODULE_LICENSE("GPL"); 
static int __init kmap_high_init(void); 
static void __exit kmap_high_exit(void); 

struct page * pages = NULL;

int __init kmap_high_init(void) 
{ 
	pages = alloc_pages(__GFP_HIGHMEM, 0); //从高端内存分配一个页 
	if(!pages) 
	{ 
		return -ENOMEM; 
	} 
	else 
	{		 
		printk("<0>alloc_pages Successfully!\npage = 0x%lx\n",(unsigned long)pages); 

        	/*调用函数kmap_high( )，将高端内存页映射到内核地址空间，返回映射的虚拟地址*/
		void * addr = kmap_high(pages);   
		printk("<0>addr = 0x%lx\n",(unsigned long)addr); 
	}	 
	return 0; 
}

void __exit kmap_high_exit(void) 
{	 
	if(pages) 
	{ 
		kunmap_high(pages);    //解除高端内存页到内核的映射 
		printk("<0>kunmap_high succeed!\n"); 
		__free_pages(pages,0);   //释放由alloc_pages( )函数所分配的高端页 
		printk("<0>__free_pages ok!\n"); 
	} 
	printk("<0>exit ok!\n"); 
}

module_init(kmap_high_init); 
module_exit(kmap_high_exit);