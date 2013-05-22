/********************************************************************************
* File Name:	get_user_pages_fast.c
* Description:	第6章实例训练          
* Reference book:《Linux内核API完全参考手册》邱铁，周玉，邓莹莹 ，机械工业出版社.2010.9  
* E_mail:openlinux2100@gmail.com			                
*
********************************************************************************/

#include <linux/init.h> 
#include <linux/module.h> 
#include <linux/security.h> 
#include <linux/mm.h> 
#include <linux/pagemap.h> 
MODULE_LICENSE("GPL"); 
static int __init get_user_pages_fast_init(void); 
static void __exit get_user_pages_fast_exit(void);

int __init get_user_pages_fast_init(void) 
{ 
	struct page * pages; 
	struct mm_struct *mm ;
	mm = current->mm; 
	unsigned long addr = mm->mmap->vm_start;   //addr代表当前进程地址空间的起始地址。 

	/*获取当前进程地址空间第一个虚拟区间vm_area_struct所包含的页数 */
	int nr_pages = vma_pages(mm->mmap);        
	printk("<0>vma_pages(mm->mmap) = %d\n",nr_pages); 

    	/*调用待测试函数，成功完成后pages指向用户空间缓冲，它被锁入内存。*/
    	int ret = get_user_pages_fast(addr,nr_pages, 0,&pages); 
	printk("<0>ret = %d\n",ret);	 
	printk("<0>page_count(pages) = %d\n", page_count(pages));   //输出页的引用计数 
	printk("<0>addr of pages is: 0x%lx\n", (unsigned long)pages); 	 
	return 0; 
}

void __exit get_user_pages_fast_exit(void) 
{ 
	printk("<0>exit ok!\n"); 
}

module_init(get_user_pages_fast_init); 
module_exit(get_user_pages_fast_exit);
