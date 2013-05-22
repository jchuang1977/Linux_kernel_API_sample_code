/********************************************************************************
* File Name:	mempool_kzalloc.c
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
static int __init mempool_kzalloc_init(void);  
static void __exit mempool_kzalloc_exit(void);   
#define size 8192 
static mempool_t * pool;  
void * element = NULL;  
int * pool_data;  
int __init mempool_kzalloc_init(void)  
{	  	
	/*mempool_kzalloc( )*/	  	
	pool_data = (int *)8192;      //设置分配的内存空间大小  	
	element = mempool_kzalloc( GFP_KERNEL ,pool_data );       //分配一个内存元素  	
	printk("<0>element = 0x%lx\n",(unsigned long)element);       //输出起始地址  	
	printk("<0>*element = %d\n",*(int *)element);               //输出element地址处的内容是否为0       	
	
	/*输出相对element偏移量为100地址处的内容是否为0 */ 	
	printk("<0>*(element+100) = %d\n",*( (int *)element + 100 ));  	  	
	
	/*mempool_create_kzalloc_pool( )*/  	
	pool = mempool_create_kzalloc_pool( 5, size);          //创建一个包含5个初始元素的内存池  	
	if(pool == NULL )  	
	{  		
		printk("<0>mempool_create_kzalloc_pool failed!\n");  		
		return 0;  	
	}  	
	else  	
	{  		
		printk("<0>min_nr = %d\n",pool->min_nr);  	
	}			  	
		return 0;  
}  

void __exit mempool_kzalloc_exit(void)  
{  	
	if( element )  	
	{  		
		mempool_kfree(element, pool_data);   //释放内存元素空间  		
		printk("<0>mempool_kfree scessfully!\n");  	
	}  	
	if( pool )  	
	{  		
		mempool_destroy(pool);            //销毁创建的内存池  		
		printk("<0>mempool_destroy scessfully!\n");  	
	} 	  	
	printk("<0>exit!\n");  	
}  

module_init(mempool_kzalloc_init);  
module_exit(mempool_kzalloc_exit);
