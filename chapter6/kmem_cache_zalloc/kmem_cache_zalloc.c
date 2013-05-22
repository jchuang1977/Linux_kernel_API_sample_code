/********************************************************************************
* File Name:	kmem_cache_zalloc.c
* Description:	第6章实例训练          
* Reference book:《Linux内核API完全参考手册》邱铁，周玉，邓莹莹 ，机械工业出版社.2010.9  
* E_mail:openlinux2100@gmail.com			                
*
********************************************************************************/

#include <linux/slab.h> 
#include <linux/init.h> 
#include <linux/module.h> 
MODULE_LICENSE("GPL"); 
static int __init kmem_cache_zalloc_init(void); 
static void __exit kmem_cache_zalloc_exit(void); 

struct kmem_cache *my_cachep; 
char * object;

int __init kmem_cache_zalloc_init(void) 
{  
	my_cachep = kmem_cache_create("my_cache",32,0,SLAB_HWCACHE_ALIGN,NULL); 
	if(my_cachep == NULL ) 
		printk("<0>kmem_cache_create failed!\n"); 
	else 
	{ 
		object = (char * )kmem_cache_zalloc( my_cachep, GFP_KERNEL ); 	 
		if(object == NULL ) 
			printk("<0>kmem_cache_zalloc failed!\n"); 
		else 
		{ 
			printk("<0>allocated object is 0x%lx\n", (unsigned long)object); 
			printk("<0>the content of object+2 is: %d\n",*(object+2)); 
			printk("<0>the content of object+30 is: %d\n",*(object+30)); 
		} 
	} 	 
	return 0; 
}

void __exit kmem_cache_zalloc_exit(void) 
{ 
	if (object) 
	{ 
    		kmem_cache_free( my_cachep, object ); 
		printk("<0>free object successfully!\n"); 
	} 
	if(my_cachep) 
	{ 
		kmem_cache_destroy(my_cachep); 
		printk("<0>destroy my_cachep successfully!\n"); 
	}	 
	printk("<0>exit!\n"); 
}

module_init(kmem_cache_zalloc_init); 
module_exit(kmem_cache_zalloc_exit);

