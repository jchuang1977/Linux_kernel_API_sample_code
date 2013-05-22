/********************************************************************************
* File Name:	find_vma_intersection.c
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
static int __init find_vma_intersection_init(void); 
static void __exit find_vma_intersection_exit(void);

int __init find_vma_intersection_init(void) 
{ 
	struct mm_struct *mm ;
	unsigned long mm_start ;
	unsigned long start_addr ;
	unsigned long end_addr ;
	struct vm_area_struct * vma ;

	mm = current->mm;                   //mm指向当前进程的地址空间	
	mm_start = mm->mmap->vm_start;       //mm_start为当前进程起始地址
	printk("<0>mm_start = 0x%lx\n", mm_start); 	 
	
	printk("<0>\nIn first situation:\n");
	start_addr = mm_start + 1;          //参数start_addr取起始地址+1	
	end_addr = mm_start +10;            //参数end_addr取起始地址+10
	
	vma = find_vma_intersection(mm , start_addr , end_addr ); 

	if(vma != NULL) 
		printk("<0>vma->vm_start = 0x%lx\n",vma->vm_start);    //输出所查找到的vma的起始地址
	else 
		printk("<0>There is no vma exists between start_addr and end_addr!\n"); 

	printk("<0>In second situation:\n");
	start_addr = mm_start - 10; 	 //参数start_addr取起始地址-10
	end_addr = mm_start - 1;        //参数end_addr取起始地址-1

	vma = find_vma_intersection(mm, start_addr, end_addr); 

	if(vma != NULL) 
		printk("<0>vma->vm_start = 0x%lx\n",vma->vm_start); 
	else 
		printk("<0>There is no vma exists between start_addr and end_addr!\n"); 
	 
	return 0; 
}

void __exit find_vma_intersection_exit(void) 
{ 
	printk("<0>exit!\n"); 
}

module_init(find_vma_intersection_init); 
module_exit(find_vma_intersection_exit);
