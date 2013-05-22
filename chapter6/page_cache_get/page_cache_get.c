/********************************************************************************
* File Name:	page_cache_get.c
* Description:	第6章实例训练          
* Reference book:《Linux内核API完全参考手册》邱铁，周玉，邓莹莹 ，机械工业出版社.2010.9  
* E_mail:openlinux2100@gmail.com			                
*
********************************************************************************/

#include <linux/init.h> 
#include <linux/module.h> 
#include <linux/gfp.h> 
#include <linux/mm_types.h> 
#include <linux/mm.h> 
#include <linux/pagemap.h> 
MODULE_LICENSE("GPL"); 
static int __init page_cache_get_init(void); 
static void __exit page_cache_get_exit(void);

struct page * pages = NULL;

int __init page_cache_get_init(void) 
{	 
	pages = alloc_pages(GFP_KERNEL,0);	//分配一个页 
	if(!pages) 
	{ 
		printk("<0>alloc failed!\n"); 
		return -ENOMEM; 
	} 
	else 
	{ 
		printk("<0>after allcating,_count=%d\n",pages->_count);	 //输出页初始分配后的引用计数 
		page_cache_get(pages); 

        	//输出对页进行page_cache_get操作后，页的引用计数
		printk("<0>after page_cache_get,_count=%d\n",pages->_count);  
		page_cache_release(pages); 

        	//输出对页进行page_cache_release操作后，页的引用计数
		printk("<0>after page_cache_release,_count=%d\n",pages->_count);  
	}	 
	return 0; 
}

void __exit page_cache_get_exit(void) 
{ 
	if(pages) 
		__free_pages(pages,0);      //释放所分配的页 
	printk("<0>exit ok!\n"); 
}

module_init(page_cache_get_init); 
module_exit(page_cache_get_exit);
