/********************************************************************************
* File Name:	kmemdup.c
* Description:	第6章实例训练          
* Reference book:《Linux内核API完全参考手册》邱铁，周玉，邓莹莹 ，机械工业出版社.2010.9  
* E_mail:openlinux2100@gmail.com			                
*
********************************************************************************/

#include <linux/string.h> 
#include <linux/init.h> 
#include <linux/module.h> 
MODULE_LICENSE("GPL"); 
static int __init kmemdup_init(void); 
static void __exit kmemdup_exit(void);
struct page * pages = NULL;

int __init kmemdup_init(void) 
{	 
	pages = alloc_pages(GFP_KERNEL,0);	 //分配一个物理页，pages为指向该页的指针 
	if(!pages) 
	{ 
		printk("<0>alloc failed!\n"); 
		return -ENOMEM; 
	} 
	else 
	{ 
		char * temp = (char *)pages; 
		char x; 
		*temp = 'a'; 
		int i = 0; 
		for(;i <26; i ++)                 //为分配的页进行循环赋值 
		{ 
			x = *temp; 
			temp ++; 
			*temp = x+1; 
		}		 
        
                /*调用函数，拷贝pages为起始地址的26个字符，分配模式为GFP_KERNEL */
		char * addr = kmemdup( pages, 26,GFP_KERNEL);   

		printk("<0>addr = 0x%lx\n",(unsigned long)addr);   //输出所拷贝的目标起始地址 
		printk("<0>*addr = %c\n",*addr);                   //输出第一个字符 
		printk("<0>*addr+4 = %c\n",*(addr+4));             //输出第五个字符 

		for(temp = addr; *temp !='\0'; temp ++)         //循环输出地址中的字符值 
			printk("%c",*temp); 
	}	 
	 
	return 0; 
}

void __exit kmemdup_exit(void) 
{ 
	if(pages) 
		__free_pages(pages,0);             //释放由alloc_pages( )所分配的页。 
	printk("<0>exit!\n"); 
}

module_init(kmemdup_init); 
module_exit(kmemdup_exit); 