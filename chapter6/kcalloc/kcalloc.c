/********************************************************************************
* File Name:	kcalloc.c
* Description:	第6章实例训练          
* Reference book:《Linux内核API完全参考手册》邱铁，周玉，邓莹莹 ，机械工业出版社.2010.9  
* E_mail:openlinux2100@gmail.com			                
*
********************************************************************************/

#include <linux/slab.h> 
#include <linux/init.h> 
#include <linux/module.h> 
MODULE_LICENSE("GPL"); 
static int __init kcalloc_init(void); 
static void __exit kcalloc_exit(void);

#define MEM_VMALLOC_SIZE 8192 
char * mem_spvm;

int __init kcalloc_init(void) 
{ 
	mem_spvm = (char *)kcalloc(2, MEM_VMALLOC_SIZE, GFP_KERNEL); 
	 
	if(mem_spvm == NULL ) 
		printk("<0>kcalloc failed!\n"); 
	else 
	{ 
        	//输出起始地址
		printk("<0>kcalloc successfully! addr = 0x%lx\n",(unsigned long)mem_spvm);
		//输出内存空间大小
		printk("<0>the actual allocated size is : %d\n",(unsigned int)ksize(mem_spvm)); 
		//输出地址偏移为10的内容
		printk("<0>the content of mem_spvm+10 is : %d\n",*(mem_spvm+10));  
		//输出地址偏移为1000的内容
		printk("<0>the content of mem_spvm+1000 is : %d\n",*(mem_spvm+1000)); 
	}		 
	return 0; 
}

void __exit kcalloc_exit(void) 
{ 
	if(mem_spvm != NULL) 
	{ 
		kfree(mem_spvm);  //释放所分配的空间
		printk("<0>kfree ok!\n"); 
	} 
	printk("<0>exit!\n"); 
}

module_init(kcalloc_init); 
module_exit(kcalloc_exit); 