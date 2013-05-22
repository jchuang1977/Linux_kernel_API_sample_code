/********************************************************************************
* File Name:	probe_kernel_address.c
* Description:	第6章实例训练          
* Reference book:《Linux内核API完全参考手册》邱铁，周玉，邓莹莹 ，机械工业出版社.2010.9  
* E_mail:openlinux2100@gmail.com			                
*
********************************************************************************/

#include <linux/init.h> 
#include <linux/module.h> 
#include <linux/uaccess.h> 
#include <linux/security.h> 
#include <linux/mm.h> 
#include <linux/mman.h>
MODULE_LICENSE("GPL"); 
static int __init probe_kernel_address_init(void); 
static void __exit probe_kernel_address_exit(void);

int __init probe_kernel_address_init(void) 
{ 	 
	struct mm_struct *mm = current->mm;          //mm指向当前进程的地址空间
	unsigned long mm_start = mm->mmap->vm_start; //mm_start为当前进程空间首地址
	unsigned long * addr = NULL; 
	addr = (unsigned long *)mm_start;             //强制类型转化mm_start赋值给addr
	printk("<0>mm_start=0x%lx\n", mm_start); 
	printk("<0>*addr = %lx\n", *addr); 	 
	long retval = 0; 
	long ret = probe_kernel_address(addr,retval);     //将addr所指的内容读到retval中 
	printk("<0>retval = %ld\n", ret); 
	printk("<0>after probe_kernel_read,retval = %lx\n", retval); 
	return 0; 
}

void __exit probe_kernel_address_exit(void) 
{	 
	printk("<0>exit!\n"); 
}

module_init(probe_kernel_address_init); 
module_exit(probe_kernel_address_exit);
