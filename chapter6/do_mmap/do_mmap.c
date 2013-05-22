/********************************************************************************
* File Name:	do_mmap.c
* Description:	第6章实例训练          
* Reference book:《Linux内核API完全参考手册》邱铁，周玉，邓莹莹 ，机械工业出版社.2010.9  
* E_mail:openlinux2100@gmail.com			                
*
********************************************************************************/

#include <linux/security.h> 
#include <linux/mm.h> 
#include <linux/mman.h> 
#include <linux/init.h> 
#include <linux/module.h> 
#include <linux/rwsem.h> 
MODULE_LICENSE("GPL"); 
static int __init do_mmap_init(void); 
static void __exit do_mmap_exit(void);

unsigned long addr; 
#define len 1000

int __init do_mmap_init(void) 
{	 
	/*调用do_mmap( )之前，当前用户空间所包含的线性空间数目*/
	printk("<0>before do_mmap( ),map_count = %d\n", current->mm->map_count); 

	down_write(&current->mm->mmap_sem);    //写者获取当前进程空间的mmap_sem信号量 
	addr = do_mmap(NULL,100,len,PROT_WRITE|PROT_READ,MAP_ANONYMOUS|MAP_SHARED,0); 
	up_write(&current->mm->mmap_sem);    //释放当前进程空间的mmap_sem信号量

	if ( addr > 0xc0000000 )         //分配不成功或是运行结果错误
	{ 
            printk("<0>do_mmap( ) failed\n"); 
    	} 
    	else                          // else指do_mmap( ) 操作成功
	{	 
            	/*调用do_mmap( )之后，当前用户空间所包含的线性空间数目*/
		printk("<0>after do_mmap( ),map_count = %d\n", current->mm->map_count);  
		printk("<0>The addr = 0x%lx\n", addr); 
	} 
	return 0;
} 

void __exit do_mmap_exit(void) 
{ 
	if( addr < 0xc000000 ) 
	{ 
		down_write(&current->mm->mmap_sem); 
		do_munmap(current->mm,addr,len); 
		up_write(&current->mm->mmap_sem); 
	} 
	printk("<0>exit ok!\n"); 
}

module_init(do_mmap_init); 
module_exit(do_mmap_exit);
