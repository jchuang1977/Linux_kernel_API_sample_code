/********************************************************************************
* File Name:	__module_address.c
* Description:	第2章实例训练          
* Reference book:《Linux内核API完全参考手册》邱铁，周玉，邓莹莹 ，机械工业出版社.2010.9  
* E_mail:openlinux2100@gmail.com			                
*
********************************************************************************/

#include <linux/module.h>
#include <linux/init.h>
MODULE_LICENSE("GPL"); 
static int __init __module_address_init(void); 
static void __exit __module_address_exit(void);

int a_module()
{
	return 0;
}
int __init __module_address_init(void) 
{ 
	struct module * ret ; //用于接收测试函数返回值
	unsigned long addr = (unsigned long)a_module; //得到内核符号a_module的地址

	/**调用__module_address( )函数之前，必须禁止中断，以防止模块在执行
	操作期间被释放**/
	preempt_disable();   //禁止抢占
	ret = __module_address(addr) ;
	preempt_enable();   //允许抢占

	/* 如果返回不为空，则输出该模块的信息 */
	if( ret != NULL )
	{
		printk("<0>ret->name: %s\n",ret->name);   //输出模块名
		printk("<0>ret->state: %d\n",ret->state);    //输出模块状态
        	/* 输出模块core段所占空间大小 */
		printk("<0>ret->core_size: %d\n",ret->core_size);  
        	/*输出模块引用计数 */
		printk("<0>refs of %s is %d\n",ret->name, module_refcount(ret)); 
	}	
	else
	{
		printk("<0>__module_address return NULL !\n");
	}	

	return 0; 
}

void __exit __module_address_exit(void) 
{ 
	printk("<0>module exit ok!\n"); 
}

module_init(__module_address_init); 
module_exit(__module_address_exit); 
