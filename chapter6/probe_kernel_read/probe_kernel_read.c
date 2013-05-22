/********************************************************************************
* File Name:	probe_kernel_read.c
* Description:	第6章实例训练          
* Reference book:《Linux内核API完全参考手册》邱铁，周玉，邓莹莹 ，机械工业出版社.2010.9  
* E_mail:openlinux2100@gmail.com			                
*
********************************************************************************/

#include <linux/init.h> 
#include <linux/module.h> 
#include <linux/security.h> 
#include <linux/uaccess.h> 
#include <linux/mm_types.h> 
#include <linux/mm.h> 
MODULE_LICENSE("GPL"); 
static int __init probe_kernel_read_init(void); 
static void __exit probe_kernel_read_exit(void);

int __init probe_kernel_read_init(void) 
{ 
	struct mm_struct *mm = current->mm;             //mm指向当前进程的地址空间
	unsigned long mm_start = mm->mmap->vm_start;    //mm_start指当前进程地址空间的起始地址
	unsigned long * src = NULL; 
	src = (unsigned long *)mm_start;                //将源地址设置为用户空间的起始地址
	printk("<0>mm_start = 0x%lx\n", mm_start); 
	printk("<0>*src = %lx\n", *src);  
	 
	unsigned long * dst = NULL; 
	dst = (unsigned long *)0xd0001234;              //目标地址为内核空间的地址
	*dst = 5; 
	printk("<0>*dst = %ld\n",*dst); 

	long ret = probe_kernel_read(dst, src, 4);        //调用函数实现源地址到目标地址内容的拷贝
	printk("<0>ret = %ld\n",ret); 
	printk("<0>after probe_kernel_read,*dst = %lx\n", *dst); 
	return 0;
}

void __exit probe_kernel_read_exit(void) 
{	 
	printk("<0>exit!\n"); 
}

module_init(probe_kernel_read_init); 
module_exit(probe_kernel_read_exit);
