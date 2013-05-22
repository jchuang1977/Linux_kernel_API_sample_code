/********************************************************************************
* File Name:	ksize.c
* Description:	第6章实例训练          
* Reference book:《Linux内核API完全参考手册》邱铁，周玉，邓莹莹 ，机械工业出版社.2010.9  
* E_mail:openlinux2100@gmail.com			                
*
********************************************************************************/

#include <linux/slab.h> 
#include <linux/init.h> 
#include <linux/module.h> 
MODULE_LICENSE("GPL"); 
static int __init ksize_init(void); 
static void __exit ksize_exit(void); 

struct kmem_cache *my_cachep; 
void * object1; 
void * object2;

int __init ksize_init(void) 
{ 
	 //创建一个slab缓存，参见本章关于kmem_cache_create( )函数的分析
	my_cachep = kmem_cache_create("my_cache", 29, 0, SLAB_HWCACHE_ALIGN, NULL ); 
 
	if(my_cachep == NULL ) 
		printk("<0>kmem_cache_create failed!\n"); 
	else 
	{ 
		object1 = kmem_cache_alloc( my_cachep,  GFP_KERNEL );   //从slab缓存中分配一个内存对象
		if(object1 == NULL ) 
			printk("<0>kmem_cache_alloc failed!\n"); 
		else 
            		//输出所分配的内存对象的实际大小
			printk("<0>the actual amount of memory allocated for a object1 is:%d\n",ksize(object1));  
	} 
	object2 = kmalloc(8080,GFP_KERNEL);  //用kmalloc( )函数分配一个内存区间

	if(object2 == NULL ) 
		printk("<0>kmalloc failed!\n"); 
	else 
	{ 
        	//输出kmalloc( )分配的内存区间的实际大小
		printk("<0>the actual amount of memory allocated for a object2 is:%d\n",ksize(object2));    
	} 
	return 0; 
}

void __exit ksize_exit(void) 
{ 
	if (object1) 
	{ 
    		kmem_cache_free( my_cachep, object1 ); //释放由kmem_cache_alloc分配的内存对象
		printk("<0>free object1 successfully!\n"); 
	} 
	if (object2) 
	{ 
    		kfree( object2 );  //释放由kmalloc( )分配的内存区间
		printk("<0>free object2 successfully!\n"); 
	} 
	if(my_cachep) 
	{ 
		kmem_cache_destroy(my_cachep);  //销毁由kmem_cache_create创建的slab缓存
		printk("<0>destroy my_cachep successfully!\n"); 
	}	 
	printk("<0>exit!\n"); 
}

module_init(ksize_init); 
module_exit(ksize_exit); 