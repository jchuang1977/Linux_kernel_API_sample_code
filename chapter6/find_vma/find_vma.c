/********************************************************************************
* File Name:	find_vma.c
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
static int __init find_vma_init(void); 
static void __exit find_vma_exit(void);

int __init find_vma_init(void) 
{ 
	struct mm_struct *mm ; 
	unsigned long addr ; 
	struct vm_area_struct * vma ;

	mm = current->mm;       //mm指向当前进程	
	addr = mm->mmap->vm_next->vm_start + 1; 
	printk("<0>addr = 0x%lx\n", addr); 
	
	vma = find_vma(mm, addr); 	 
	if(vma != NULL ) 
	{		 
		/*输出所查找的虚拟区间的起始地址*/
		printk("<0>vma->vm_start = 0x%lx\n",vma->vm_start); 

		/*输出所查找虚拟区间的结束地址*/
		printk("<0>vma->vm_end = 0x%lx\n", vma->vm_end); 
	} 
	else 
		printk("<0>UNLUCK! You have failed!\n"); 

	return 0; 
}

void __exit find_vma_exit(void) 
{ 
	printk("<0>exit!\n"); 
}

module_init(find_vma_init); 
module_exit(find_vma_exit);
