/********************************************************************************
* File Name:	mempool_alloc_slab.c
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
static int __init mempool_alloc_slab_init(void);  
static void __exit mempool_alloc_slab_exit(void);   
static struct kmem_cache * kmem = NULL;  
void * element = NULL; 
int __init mempool_alloc_slab_init(void)  
{
	//创建一个slab高速缓存
	kmem = kmem_cache_create("my_buffer",10000,0,SLAB_HWCACHE_ALIGN,NULL);
   	if(kmem == NULL )
  	{
  		printk("<0>kmem_cache_create failed!\n");                    //输出失败信息
  		return 0;
  	}
  	else
  	{
  		printk("<0>kmem_cache_create successfully!\n");
  		element = mempool_alloc_slab( GFP_KERNEL , kmem );       //分配一个内存元素
 	       printk("<0>element = 0x%lx\n",(unsigned long)element);      //输出起始地址
       }
  	return 0;
}

void __exit mempool_alloc_slab_exit(void)
{
  	if(element)
  	{
  		mempool_free_slab(element,kmem);    //释放内存元素空间
  		printk("<0>mempool_free_slab successfully!\n");
  	}
  	if(kmem != NULL)
  	{
  		kmem_cache_destroy(kmem);           //销毁slab高速缓存
  		printk("<0>kmem_cache_destroy successfully!\n");
  	}
  	printk("<0>exit!\n");
}

module_init(mempool_alloc_slab_init);
module_exit(mempool_alloc_slab_exit);