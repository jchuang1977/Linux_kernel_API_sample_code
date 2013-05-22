/********************************************************************************
* File Name:	memdup_user.c
* Description:	第6章实例训练          
* Reference book:《Linux内核API完全参考手册》邱铁，周玉，邓莹莹 ，机械工业出版社.2010.9  
* E_mail:openlinux2100@gmail.com			                
*
********************************************************************************/

#include <linux/string.h>
#include <linux/init.h>
#include <linux/module.h> 
#include <linux/sched.h>
MODULE_LICENSE("GPL"); 
static int __init memdup_user_init(void); 
static void __exit memdup_user_exit(void);

#define len 20

int __init memdup_user_init(void) 
{	 
	struct mm_struct * mm ;
	unsigned long mm_start ;

	mm = current->mm;  	        //获取当前进程的地址空间	
	mm_start = mm->mmap->vm_start;    //mm_start为当前进程地址空间的起始地址 

	printk("<0>mm_start = 0x%lx\n", mm_start);	

    	//调用函数，从mm_start开始的地址空间拷贝len个字节的内容
	unsigned long * addr = memdup_user( mm_start, len);   	 

	printk("<0>addr = 0x%lx\n",(unsigned long)addr);   //输出所拷贝的目标起始地址 
	printk("<0>*addr = %lx\n",*addr);                 //输出第一个字 
	printk("<0>*addr+1 = %lx\n",*(addr+1));           //输出第四个字 
	unsigned long * temp = addr; 
	int i = 0; 
	for(;i<len/4; i ++,temp ++)                   //循环输出地址中的字内容 
		printk("%lx\n",*temp); 
	return 0; 	 
}

void __exit memdup_user_exit(void) 
{ 
	printk("<0>exit ok!\n"); 
}

module_init(memdup_user_init); 
module_exit(memdup_user_exit);