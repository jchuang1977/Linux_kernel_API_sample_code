/********************************************************************************
* File Name:	do_brk.c
* Description:	第6章实例训练          
* Reference book:《Linux内核API完全参考手册》邱铁，周玉，邓莹莹 ，机械工业出版社.2010.9  
* E_mail:openlinux2100@gmail.com			                
*
********************************************************************************/

#include <linux/security.h> 
#include <linux/mm.h> 
#include <linux/init.h> 
#include <linux/module.h> 
MODULE_LICENSE("GPL"); 
static int __init do_brk_init(void); 
static void __exit do_brk_exit(void); 

unsigned long addr; 
#define len 8192

int __init do_brk_init(void) 
{ 
	struct mm_struct *mm ;
	mm = current->mm;  //mm指向当前进程的地址空间 
	addr = 200; 

    	/*调用do_brk( )之前，当前用户空间所包含的线性空间数目*/
	printk("<0>before do_brk( ),map_count = %d\n", mm->map_count); 
	 
	down_write(&current->mm->mmap_sem);       //写者获取当前进程空间的mmap_sem信号量 
	addr = do_brk( addr, len );               //调用do_brk( )函数，addr = 200,len = 8192字节 
	up_write(&current->mm->mmap_sem); 
	 
	printk("<0>addr=0x%lx\n",addr); //输出新分配的线性区间的起始地址 

    	/*调用do_brk( )之后，当前用户空间所包含的线性空间数目*/
	printk("<0>after do_brk( ),map_count = %d\n", mm->map_count);  	 
	return 0; 
}

void __exit do_brk_exit(void) 
{ 
	down_write(&current->mm->mmap_sem);     //写者获取当前进程空间的mmap_sem信号量 
	do_munmap(current->mm,addr,len); 
	up_write(&current->mm->mmap_sem); 
	printk("<0>exit ok!\n"); 
}

module_init(do_brk_init); 
module_exit(do_brk_exit);
