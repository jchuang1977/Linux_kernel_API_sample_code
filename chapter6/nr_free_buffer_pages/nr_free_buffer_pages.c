/********************************************************************************
* File Name:	nr_free_buffer_pages.c
* Description:	第6章实例训练          
* Reference book:《Linux内核API完全参考手册》邱铁，周玉，邓莹莹 ，机械工业出版社.2010.9  
* E_mail:openlinux2100@gmail.com			                
*
********************************************************************************/

#include <linux/init.h> 

#include <linux/module.h> 
#include <linux/swap.h> 
MODULE_LICENSE("GPL"); 
static int __init nr_free_buffer_pages_init(void); 
static void __exit nr_free_buffer_pages_exit(void);

int __init nr_free_buffer_pages_init(void) 
{	 
	int free_page_num = nr_free_buffer_pages( ); 
	printk("<0>free_page_num = %d\n",free_page_num); 
	return 0; 
}

void __exit nr_free_buffer_pages_exit(void) 
{ 
	printk("<0>exit!\n"); 
}

module_init(nr_free_buffer_pages_init); 
module_exit(nr_free_buffer_pages_exit);
