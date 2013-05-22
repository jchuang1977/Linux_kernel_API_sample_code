/********************************************************************************
* File Name:	kmem_cache_create.c
* Description:	第6章实例训练          
* Reference book:《Linux内核API完全参考手册》邱铁，周玉，邓莹莹 ，机械工业出版社.2010.9  
* E_mail:openlinux2100@gmail.com			                
*
********************************************************************************/

#include <linux/slab.h> 
#include <linux/init.h> 
#include <linux/module.h> 
MODULE_LICENSE("GPL"); 
static int __init kmem_cache_create_init(void); 
static void __exit kmem_cache_create_exit(void);

char * mem_spvm = NULL; 
struct kmem_cache *my_cachep = NULL;

int __init kmem_cache_create_init(void) 
{ 	 
	my_cachep = kmem_cache_create("my_cache",32,0,SLAB_HWCACHE_ALIGN,NULL); 	 
	if(my_cachep == NULL ) 
		printk("<0>kmem_cache_create failed!\n"); 
	else 
	{ 
		printk("<0>Cache size is: %d\n",kmem_cache_size(my_cachep)); 
		printk("<0>Cache name is: %s\n", kmem_cache_name( my_cachep )); 
	} 	 
	return 0; 
}

void __exit kmem_cache_create_exit(void) 
{ 	 
	if(my_cachep) 
	{ 
		kmem_cache_destroy(my_cachep); 
		printk("<0>kmem_cache_destroy succeed!\n"); 
	}	 
	printk("<0>exit!\n"); 
}

module_init(kmem_cache_create_init); 
module_exit(kmem_cache_create_exit);

