/********************************************************************************
* File Name:	mempool_alloc_pages.c
* Description:	第6章实例训练          
* Reference book:《Linux内核API完全参考手册》邱铁，周玉，邓莹莹 ，机械工业出版社.2010.9  
* E_mail:openlinux2100@gmail.com			                
*
********************************************************************************/

#include <linux/mm.h>
#include <linux/slab.h>
#include <linux/module.h>  
#include <linux/mempool.h>  
#include <linux/blkdev.h>  
#include <linux/writeback.h>  
MODULE_LICENSE("GPL");  
static int __init mempool_alloc_pages_init(void);
static void __exit mempool_alloc_pages_exit(void);   
int * pool_data;  void * element = NULL; 
int __init mempool_alloc_pages_init(void)  
{  	
	pool_data = (int *)2;    //设置分配的内存空间大小，为4个页  	
	element = mempool_alloc_pages( GFP_KERNEL ,pool_data );   //分配一个内存元素      	
	if( element != NULL )
 	     printk("<0>element = 0x%lx\n",(unsigned long)element);  //输出起始地址
  	else
 		 printk("<0>mempool_alloc_pages failed!\n");
   	return 0;  
}

void __exit mempool_alloc_pages_exit(void)  
{
  	if(element)
  	{
  		mempool_free_pages(element,pool_data);   //释放内存元素空间
  		printk("<0>mempool_free_pages successfully!\n");
  	}
  	printk("<0>exit!\n");
}  

module_init(mempool_alloc_pages_init);
module_exit(mempool_alloc_pages_exit);