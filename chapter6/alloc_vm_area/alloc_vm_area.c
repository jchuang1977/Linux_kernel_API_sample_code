/********************************************************************************
* File Name:	alloc_vm_area.c
* Description:	第6章实例训练          
* Reference book:《Linux内核API完全参考手册》邱铁，周玉，邓莹莹 ，机械工业出版社.2010.9  
* E_mail:openlinux2100@gmail.com			                
*
********************************************************************************/

#include <linux/init.h> 
#include <linux/module.h> 
#include <linux/vmalloc.h> 
MODULE_LICENSE("GPL"); 
static int __init alloc_vm_area_init(void); 
static void __exit alloc_vm_area_exit(void); 

struct vm_struct * vm; 
unsigned long size = 8092;

int __init alloc_vm_area_init(void) 
{ 
        /*调用alloc_vm_area( )分配size 大小的内核地址空间*/
	vm = alloc_vm_area( size ); 

	if( vm == NULL ) 
		printk("<0>alloc failed!\n"); 
	else 
	{ 
		printk("<0>vm->addr= 0x%lx\n",(unsigned long)vm->addr);  //输出虚拟区间vm的起始地址
		printk("<0>vm->size= %ld\n",vm->size);	  //输出虚拟区间vm的大小
	} 
	return 0; 
}
	
void __exit alloc_vm_area_exit(void) 
{ 
	if( vm ) 
	{		
		free_vm_area( vm );   //释放由alloc_vm_area( )函数所分配的虚拟区间
		printk("<0>free_vm_area ok!\n"); 
	}

	printk("<0>exit !\n"); 
}

module_init(alloc_vm_area_init); 
module_exit(alloc_vm_area_exit);
