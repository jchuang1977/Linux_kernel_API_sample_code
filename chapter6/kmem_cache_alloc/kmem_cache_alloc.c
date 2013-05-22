/********************************************************************************
* File Name:	kmem_cache_alloc.c
* Description:	第6章实例训练          
* Reference book:《Linux内核API完全参考手册》邱铁，周玉，邓莹莹 ，机械工业出版社.2010.9  
* E_mail:openlinux2100@gmail.com			                
*
********************************************************************************/

#include <linux/slab.h> 
#include <linux/init.h> 
#include <linux/module.h> 
MODULE_LICENSE("GPL"); 
static int __init kmem_cache_alloc_init(void); 
static void __exit kmem_cache_alloc_exit(void); 

struct kmem_cache *my_cachep; 
void * object = NULL;

int __init kmem_cache_alloc_init(void) 
{ 	 
    	//创建一个名为”my_cache”的slab缓存
	my_cachep = kmem_cache_create("my_cache",35,0,SLAB_HWCACHE_ALIGN,NULL); 

	if(my_cachep == NULL ) 
		printk("<0>kmem_cache_create failed!\n"); 
	else 
	{ 
		object = kmem_cache_alloc( my_cachep, GFP_KERNEL ); //从slab缓存中分配一个内存对象 
		if(object == NULL ) 
			printk("<0>kmem_cache_alloc failed!\n"); 
		else 
			printk("<0>allocate object is 0x%lx\n", (unsigned long)object); 
	} 
	return 0; 
}

void __exit kmem_cache_alloc_exit(void) 
{ 
	if (object) 
	{ 
    		kmem_cache_free( my_cachep, object );             //释放分配的内存对象
		printk("<0>free object successfully!\n"); 
	} 
	if(my_cachep) 
	{ 
		kmem_cache_destroy(my_cachep);              //销毁高速缓存
		printk("<0>destroy my_cachep successfully!\n"); 
	}	 
	printk("<0>exit!\n"); 
}

module_init(kmem_cache_alloc_init); 
module_exit(kmem_cache_alloc_exit);