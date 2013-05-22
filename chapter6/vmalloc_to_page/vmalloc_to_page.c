/********************************************************************************
* File Name:	vmalloc_to_page.c
* Description:	第6章实例训练          
* Reference book:《Linux内核API完全参考手册》邱铁，周玉，邓莹莹 ，机械工业出版社.2010.9  
* E_mail:openlinux2100@gmail.com			                
*
********************************************************************************/

#include <linux/init.h>
#include <linux/module.h>
#include <linux/security.h>
#include <linux/vmalloc.h>
#include <linux/mm.h>
MODULE_LICENSE("GPL");
static int __init vmalloc_to_page_init(void);
static void __exit vmalloc_to_page_exit(void);

#define VMALLOC_SIZE 8092
char * addr;

int __init vmalloc_to_page_init(void)
{
	addr = (char *)vmalloc(VMALLOC_SIZE);	        //调用vmalloc( )分配一段内存区间
	if( addr == NULL )
		printk("<0>vmalloc failed!\n");
	else
	{
		printk("<0>vmalloc successfully! addr = 0x%lx\n",(unsigned long)addr);	//输出返回地址	
		struct page * to_page; 
		to_page = vmalloc_to_page( addr );      //to_page为虚拟地址addr所映射的物理页框
		printk("<0>the_page_address = 0x%lx\n",to_page);
		to_page = vmalloc_to_page( addr+4097 );	//to_page为虚拟地址addr+4097所映射的物理页框		
		printk("<0>the_page_address = 0x%lx\n",to_page);
	}	
	return 0;
}

void __exit vmalloc_to_page_exit(void)
{
	if(addr != NULL)
		vfree( addr );  //释放由vmalloc( )函数所分配的内存区间
	printk("<0>exit ok!\n");
}

module_init(vmalloc_to_page_init);
module_exit(vmalloc_to_page_exit);
