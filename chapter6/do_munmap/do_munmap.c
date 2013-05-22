/********************************************************************************
* File Name:	do_munmap.c
* Description:	第6章实例训练          
* Reference book:《Linux内核API完全参考手册》邱铁，周玉，邓莹莹 ，机械工业出版社.2010.9  
* E_mail:openlinux2100@gmail.com			                
*
********************************************************************************/

#include <linux/mm.h>
#include <linux/security.h> 
#include <linux/mman.h> 
#include <linux/init.h> 
#include <linux/module.h> 
MODULE_LICENSE("GPL"); 
static int __init do_munmap_init(void); 
static void __exit do_munmap_exit(void);
 
#define define_nobrk  0      //控制if~else 分支语句选择

int __init do_munmap_init(void) 
{	 
	struct mm_struct *mm ;
	unsigned long start ;     //声明start 为要删除线性区间的起始地址 
	size_t len ;
	int ret;                //ret 用来接收do_munmap( )函数的返回值

	len = 4096;            //定义删除的长度为4096字节 	 
	mm = current->mm;	 //mm指向当前进程的地址空间

	/*********************************************** 
	**执行if 中的语句时，要删除的线性区间为当前进程已存在的区间，这部分线性区间可能正在使用 
	**执行else 中的语句时，先为当前进程分配一个线性区间，删除的即为这个刚分配的区间，这个空 
	**间是空闲的。 
	************************************************/ 
	if( define_nobrk ) 
	{ 
        	/*调用do_munmap( )之前，当前用户空间所包含的线性空间数目 */
		printk("<0>before do_munmap,map_count = %d\n", mm->map_count);

		/*令start为当前进程地址空间第一个线性区的起始地址 */
		start = mm->mmap->vm_next->vm_start;      

		down_write(&current->mm->mmap_sem);          //写当前进程空间的mmap_sem信号量 
		ret = do_munmap(mm ,start,len) ;             //调用do_munmap( )函数，ret接收返回值 
		up_write(&current->mm->mmap_sem); 
	 
		printk("<0>ret = %d\n",ret); 

        	/*调do_munmap( )之后，当前用户空间所包含的线性空间数目*/
		printk("<0>after do_munmap,map_count = %d\n", mm->map_count); 
	} 
	else 
	{		 
		down_write(&current->mm->mmap_sem); 
		start = do_brk( 4096, len );                //调用do_brk( )为分配一个新线性区间 
		up_write(&current->mm->mmap_sem); 

       	 	/*调用do_munmap( )之前，当前用户空间所包含的线性空间数目 */
		printk("<0>before do_munmap,map_count = %d\n", mm->map_count);

		down_write(&current->mm->mmap_sem); //写当前进程空间的mmap_sem信号量 
		ret = do_munmap(mm ,start,len) ;        //调用do_munmap( )函数，ret接收返回值 
		up_write(&current->mm->mmap_sem);		 

		printk("<0>ret = %d\n",ret); 

        	/*调用do_munmap( )之后，当前用户空间所包含的线性空间数目*/
		printk("<0>after do_munmap,map_count = %d\n", mm->map_count); 
	}	 
	return 0; 
}

void __exit do_munmap_exit(void) 
{ 
	printk("<0>exit ok!\n"); 
}

module_init(do_munmap_init); 
module_exit(do_munmap_exit);
