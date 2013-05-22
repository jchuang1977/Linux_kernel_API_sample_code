/********************************************************************************
* File Name:	probe_kernel_write.c
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
static int __init probe_kernel_write_init(void); 
static void __exit probe_kernel_write_exit(void); 

unsigned long *addr; 
#define len 1000

int __init probe_kernel_write_init(void) 
{ 
	unsigned long * src = NULL; 
	src = (unsigned long *)0xdc001234;      //设置源地址src为内核地址空间的某一地址
	*src = 65;                              //该地址处的内容为65
	printk("<0>*src = %ld\n",*src); 	 
	unsigned long * dst = NULL;		
 
    	/*为当前进程地址空间分配一个线性区，addr为线性区首地址*/
	down_write(&current->mm->mmap_sem); 
	addr = do_mmap_pgoff(NULL, 100, len, PROT_WRITE|PROT_READ,
						MAP_ANONYMOUS|MAP_SHARED, 0); 
	up_write(&current->mm->mmap_sem); 
	 
	if( addr ) 
	{ 
		dst = (unsigned long *)addr;                           //目标地址为线性区的首地址
		printk("<0>originally *dst = %ld\n", *dst);               //输出拷贝之前目标地址的内容
	 
		long ret = probe_kernel_write( dst , src , 4 );        //从内核空间拷贝4个字节到用户空间
		printk("<0>ret = %ld\n",ret); 
		printk("<0>after probe_kernel_write,*dst = %ld\n", *dst); //输出拷贝之后目标地址的内容
	} 
	else 
	{ 
		printk("<0>do_mmap_pgoff failed!"); 
	} 
	 
	return 0; 
}

void __exit probe_kernel_write_exit(void) 
{	 
	if( addr ) 
		do_munmap(current->mm,addr,len); 
	printk("<0>exit!\n"); 
}

module_init(probe_kernel_write_init); 
module_exit(probe_kernel_write_exit);
