/********************************************************************************
* File Name:	get_unmapped_area.c
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
MODULE_LICENSE("GPL"); 
static int __init get_unmapped_area_init(void); 
static void __exit get_unmapped_area_exit(void);

int __init get_unmapped_area_init(void) 
{	 
	unsigned long len ;
	unsigned long address ;  //定义一个长整型变量以接收所返回的地址值 

    	len = 1025;	        //假设所要查找的空闲空间的长度为1025个字节
	address = get_unmapped_area(NULL, 100,len, 0, MAP_ANONYMOUS);   //为各参数赋值，调用该函数 
	printk("<0>find address = 0x%lx\n",address); 
	return 0; 
} 

void __exit get_unmapped_area_exit(void) 
{ 
	printk("<0>exit ok!\n");     //退出 
}

module_init(get_unmapped_area_init); 
module_exit(get_unmapped_area_exit); 
