/********************************************************************************
* File Name:	mempool_alloc.c
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
static int __init mempool_alloc_init(void);  
static void __exit mempool_alloc_exit(void);   
static struct kmem_cache * kmem = NULL;  
static mempool_t * pool = NULL;  
static void * element = NULL;  
int __init mempool_alloc_init(void)  
{	          
	//创建一个名为"my_buffer"的slab缓存 	
	kmem = kmem_cache_create("my_buffer",10000,0,SLAB_HWCACHE_ALIGN,NULL);	  	  	
	if(kmem == NULL )  	
	{  		
		printk("<0>kmem_cache_create failed!\n");    		
		return 0;  	
	}  	
	else  	
	{  		
		printk("<0>kmem_cache_create scessfully!\n");           	//基于创建的slab缓存创建一个包含5个初始元素的内存池 		
		pool = mempool_create(5,mempool_alloc_slab,mempool_free_slab,kmem);  		
		if(pool == NULL )  		
		{  			
			printk("<0>mempool_create failed!\n");
  			return 0;
  		}
  		else
  		{
              		//从创建好的内存池中分配内存
 			printk("<0>mempool_create scessfully! min_nr = %d\n",pool->min_nr); 
  			element = mempool_alloc(pool , GFP_KERNEL);
  			//输出所分配内存对象的地址 
            		printk("<0>after mempool_alloc,element = 0x%lx\n",(unsigned long)element);
   		}
	}
  	return 0;
  }

void __exit mempool_alloc_exit(void)  
{
  	if(element != NULL)
	{  		
		mempool_free(element,pool);  //释放分配的内存对象 
		printk("<0>mempool_free scessfully!\n"); 
	}
 	if(pool != NULL) 
	{
 		mempool_destroy(pool);      //销毁创建的内存池 
		printk("<0>mempool_destroy scessfully!\n"); 
	}
 	if(kmem != NULL) 
	{
 		kmem_cache_destroy(kmem);  //销毁创建的slab缓存 
		printk("<0>kmem_cache_destroy scessfully!\n"); 
	}
  	printk("<0>exit!\n");
  }

  module_init(mempool_alloc_init);
  module_exit(mempool_alloc_exit);



