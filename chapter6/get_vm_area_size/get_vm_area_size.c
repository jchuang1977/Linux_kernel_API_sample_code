/********************************************************************************
* File Name:	get_vm_area_size.c
* Description:	第6章实例训练          
* Reference book:《Linux内核API完全参考手册》邱铁，周玉，邓莹莹 ，机械工业出版社.2010.9  
* E_mail:openlinux2100@gmail.com			                
*
********************************************************************************/

#include <linux/init.h> 
#include <linux/module.h> 
#include <linux/vmalloc.h> 
MODULE_LICENSE("GPL"); 
static int __init get_vm_area_size_init(void); 
static void __exit get_vm_area_size_exit(void); 

struct vm_struct * vm; 
unsigned long size = 8192;

int __init get_vm_area_size_init(void) 
{ 
	vm = alloc_vm_area( size );                          //分配一个size大小的内核虚拟区间
	if( vm == NULL ) 
		printk("<0>alloc failed!\n"); 
	else 
	{		 
		printk("<0>vm->size = %ld\n",vm->size);        //输出在结构体size字段所存储的大小
		size_t actual_size = get_vm_area_size( vm ); 
		printk("<0>actual_size = %ld\n",actual_size);  //输出由get_vm_area_size所得到的实际大小
	} 
	return 0; 
}

void __exit get_vm_area_size_exit(void) 
{ 
	if( vm ) 
	     free_vm_area( vm ); 
	printk("<0>exit !\n"); 
}

module_init(get_vm_area_size_init); 
module_exit(get_vm_area_size_exit);
