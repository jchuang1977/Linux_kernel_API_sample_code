/********************************************************************************
* File Name:	__get_vm_area.c
* Description:	第6章实例训练          
* Reference book:《Linux内核API完全参考手册》邱铁，周玉，邓莹莹 ，机械工业出版社.2010.9  
* E_mail:openlinux2100@gmail.com			                
*
********************************************************************************/

#include <linux/vmalloc.h> 
#include <linux/module.h> 
#include <linux/init.h> 
MODULE_LICENSE("GPL"); 
static int __init  __get_vm_area_init(void); 
static void __exit  __get_vm_area_exit(void); 

struct vm_struct *vm = NULL;

int __init __get_vm_area_init(void) 
{ 
	vm = __get_vm_area(8192*4, VM_ALLOC, 0xC0000100, 0xdd000000); 
	if( !vm ) 
	{ 
		return -ENOMEM; 
	} 
	else 
	{ 
		printk("<0>vm->size ：%ld\n",vm->size);                //输出内核线性区间大小
		printk("<0>vm->addr ：0x%lx\n",(unsigned long)vm->addr);  //输出起始地址
	} 
	return 0; 
}

void __exit __get_vm_area_exit(void) 
{ 
	if(vm) 
    	{
		free_vm_area(vm); 
	   	printk("<0>free_vm_area ok!\n"); 
	}
	printk("<0>exit !\n");
}

module_init(__get_vm_area_init); 
module_exit(__get_vm_area_exit); 
