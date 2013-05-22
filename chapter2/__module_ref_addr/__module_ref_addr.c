/********************************************************************************
* File Name:	__module_ref_addr.c
* Description:	第2章实例训练          
* Reference book:《Linux内核API完全参考手册》邱铁，周玉，邓莹莹 ，机械工业出版社.2010.9  
* E_mail:openlinux2100@gmail.com			                
*
********************************************************************************/

#include <linux/module.h>
#include <linux/init.h>

MODULE_LICENSE("GPL"); 

static int __init __module_ref_addr_init(void); 
static void __exit __module_ref_addr_exit(void);

int __init __module_ref_addr_init(void) 
{ 	
	local_t * addr;
	unsigned int cpu = get_cpu();  //获取当前cpu ID 

    	/*addr 为指向当前模块引用计数的指针*/
	addr = __module_ref_addr( THIS_MODULE, cpu ); 
	printk("<0>addr: %lx\n", (unsigned long)addr);	
	
	printk("<0>originally,\n");  //输出初始时当前模块的引用计数
	printk("<0>refs of this module is: %d\n",module_refcount(THIS_MODULE));
	
	local_inc(addr);  //实现将addr所指向的内容加1
	printk("<0>after calling local_inc,\n");  
	printk("<0>refs of this module is: %d\n",module_refcount(THIS_MODULE));	

	local_dec(addr);  //实现将addr所指向的内容减1
	printk("<0>after calling local_dec,\n");
	printk("<0>refs of this module is: %d\n",module_refcount(THIS_MODULE));

	put_cpu();  //允许抢占 preempt_enable( )

	return 0; 
}


void __exit __module_ref_addr_exit(void) 
{ 	
	printk("<0>module exit ok!\n"); 
}

module_init(__module_ref_addr_init); 
module_exit(__module_ref_addr_exit); 
