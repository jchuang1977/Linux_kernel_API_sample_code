/********************************************************************************
* File Name:	get_zeroed_page.c
* Description:	第6章实例训练          
* Reference book:《Linux内核API完全参考手册》邱铁，周玉，邓莹莹 ，机械工业出版社.2010.9  
* E_mail:openlinux2100@gmail.com			                
*
********************************************************************************/

#include <linux/gfp.h> 
#include <linux/init.h> 
#include <linux/module.h> 
MODULE_LICENSE("GPL"); 
static int __init get_zeroed_page_init(void); 
static void __exit get_zeroed_page_exit(void); 

char * addr;

int __init get_zeroed_page_init(void) 
{	 
	addr = (char *)get_zeroed_page(GFP_KERNEL); 
	 
	if(addr == NULL ) 
		printk("<0>get_zeroed_page failed!\n"); 
	else 
	{ 
		printk("<0>get_zeroed_page successfully! addr = 0x%lx\n",(unsigned long)addr ); 
		printk("<0>the content of mem_spvm+2 is: %d\n",*(addr+2)); 
		printk("<0>the content of mem_spvm+500 is: %d\n",*(addr+500)); 
	} 	 
	return 0; 
}

void __exit get_zeroed_page_exit(void) 
{ 
	if(addr != NULL) 
	{ 
		free_pages((unsigned long)addr , 1);    //由于分配一页，这里也释放一页
		printk("<0>free_pages ok!\n"); 
	} 
	printk("<0>exit!\n"); 
}

module_init(get_zeroed_page_init); 
module_exit(get_zeroed_page_exit);
