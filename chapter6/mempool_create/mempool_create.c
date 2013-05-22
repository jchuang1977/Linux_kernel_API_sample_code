/********************************************************************************
* File Name:	mempool_create.c
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
static int __init mempool_create_init(void);  
static void __exit mempool_create_exit(void);   
static struct kmem_cache * kmem;  
static mempool_t * pool = NULL;
int __init mempool_create_init(void)  
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
		printk("<0>kmem_cache_create scessfully!\n");       	
		//基于创建的slab缓存创建一个包含5个初始元素的内存池 		
		pool = mempool_create(5, mempool_alloc_slab, 
		mempool_free_slab, kmem);   		
		if(pool == NULL )  		
		{  			
			printk("<0>mempool_create failed!\n");  			
			return 0;  		
		}  		
		else  		
		{  			
			printk("<0>mempool_create scessfully! min_nr = %d\n",pool->min_nr);  		
		}  		  	
	}  	  	
	return 0;  
}
 
void __exit mempool_create_exit(void)  
{  	
	if(pool != NULL) 	
	{ 		
		mempool_destroy(pool);       //销毁创建的内存池 		
		printk("<0>mempool_destroy succeed!\n");	
	} 	
	if(kmem != NULL) 	
	{ 		
		kmem_cache_destroy(kmem);    //销毁创建的slab缓存 		
		printk("<0>kmem_cache_destroy succeed!\n");
	}  	
	printk("<0>exit!\n");  
}
module_init(mempool_create_init);  
module_exit(mempool_create_exit); 