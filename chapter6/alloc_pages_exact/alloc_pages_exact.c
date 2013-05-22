/********************************************************************************
* File Name:	alloc_pages_exact.c
* Description:	第6章实例训练          
* Reference book:《Linux内核API完全参考手册》邱铁，周玉，邓莹莹 ，机械工业出版社.2010.9  
* E_mail:openlinux2100@gmail.com			                
*
********************************************************************************/

#include <linux/init.h> 
#include <linux/module.h> 
#include <linux/gfp.h> 
MODULE_LICENSE("GPL"); 
static int __init alloc_pages_exact_init(void); 
static void __exit alloc_pages_exact_exit(void); 

void * addr = NULL;
#define size 8092

int __init alloc_pages_exact_init(void) 
{ 
    	/*调用函数，以GFP_KERNEL模式分配 满足size字节大小的内存空间 */
	addr = alloc_pages_exact( size, GFP_KERNEL);

	if(!addr) 
	{ 
		printk("<0>alloc_pages_exact failed!\n"); 
		return -ENOMEM; 
	} 
	else 
	{ 
		printk("<0>addr = 0x%lx\n",(unsigned long)addr);   //输出所分配的内存空间的起始地址 
	} 
	return 0; 
}

void __exit alloc_pages_exact_exit(void) 
{ 
	if(addr) 
	{ 
		free_pages_exact(addr,size);      //释放所分配的内存空间 
		printk("<0>free_pages_exact succeed!\n"); 
	} 
	printk("<0>exit!\n"); 
}

module_init(alloc_pages_exact_init); 
module_exit(alloc_pages_exact_exit);
