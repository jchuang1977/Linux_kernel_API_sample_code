/********************************************************************************
* File Name:	krealloc.c
* Description:	第6章实例训练          
* Reference book:《Linux内核API完全参考手册》邱铁，周玉，邓莹莹 ，机械工业出版社.2010.9  
* E_mail:openlinux2100@gmail.com			                
*
********************************************************************************/

#include <linux/string.h> 
#include <linux/slab.h> 
#include <linux/init.h> 
#include <linux/module.h> 
MODULE_LICENSE("GPL"); 
static int __init krealloc_init(void); 
static void __exit krealloc_exit(void); 

struct page * pages = NULL; 
#define new_size  26
 
int __init krealloc_init(void) 
{	 
	char * temp, * addr;
	char x;
	int i;

	pages = alloc_pages(GFP_KERNEL,0);       //分配一个物理页，pages为指向该页的指针 
	if(!pages) 
	{ 
		printk("<0>alloc failed!\n"); 
		return -ENOMEM; 
	} 
	else 
	{ 
		temp = (char *)pages;     //临时指针指向刚分配页的起始地址 		
		*temp = 'a'; 
		i = 0; 
		for(;i < new_size; i ++)        //为分配的页前new_size个字节进行赋值 
		{ 
			x = *temp; 
			temp ++; 
			*temp = x+1; 
		}	
       		//调用函数，重新分配内存，pages为起始地址的前new_size个字节的内容不改变
	    	addr = krealloc( pages,new_size,GFP_KERNEL);  
		printk("<0>addr = 0x%lx\n",(unsigned long)addr);      //输出所拷贝的目标起始地址 
		printk("<0>*addr = %c\n",*addr);                      //输出第一个字符 
		printk("<0>*addr+4 = %c\n",*(addr+4));                //输出第五个字符 
		 
		i = 0 ; temp = addr; 
		for(; i<new_size; i ++,temp ++)                    //输出新内存中的内容 
			printk("<0>%c",*temp); 	
		
	}	 	 
	return 0; 
}

void __exit krealloc_exit(void) 
{ 
	if(pages) 
	{ 
		__free_pages(pages,0);                      //释放由alloc_pages( )所分配的页。 
		printk("<0>__free_pages succeed!\n"); 
	} 
	printk("<0>exit ok!\n"); 
}

module_init(krealloc_init); 
module_exit(krealloc_exit);