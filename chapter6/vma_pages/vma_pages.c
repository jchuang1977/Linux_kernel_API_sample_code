/********************************************************************************
* File Name:	vma_pages.c
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
static int __init vma_pages_init(void); 
static void __exit vma_pages_exit(void);

int __init vma_pages_init(void) 
{ 
	struct mm_struct *mm = current->mm;                //mm指向当前进程的地址空间
	unsigned long addr = mm->mmap->vm_start + 1;       //进程虚拟区间中某一地址
	printk("<0>addr=0x%lx\n", addr); 
	struct vm_area_struct * vma = find_vma(mm, addr);  //找到地址addr所属的线性区间
	 
	if(vma != NULL ) 
	{		 
	    printk("<0>vma->vm_start=0x%lx\n",vma->vm_start); 
		printk("<0>vma->vm_end=0x%lx\n", vma->vm_end); 
		 
		int page_number = vma_pages(vma);            //获得线性区间vma所包含的页数
		printk("<0>the page_number of vma is:%d\n",page_number); 
	} 
	else 
		printk("<0> You have failed!\n"); 

	return 0; 
}

void __exit vma_pages_exit(void) 
{ 
	printk("<0>exit!\n"); 
}

module_init(vma_pages_init); 
module_exit(vma_pages_exit);
