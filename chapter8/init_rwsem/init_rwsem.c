/********************************************************************************
* File Name:	init_rwsem.c
* Description:	第8章实例训练          
* Reference book:《Linux内核API完全参考手册》邱铁，周玉，邓莹莹 ，机械工业出版社.2010.9  
* E_mail:openlinux2100@gmail.com			                
*
********************************************************************************/

#include <linux/rwsem.h> 
#include <linux/init.h> 
#include <linux/module.h> 

MODULE_LICENSE("GPL"); 
static int __init init_rwsem_init(void); 
static void __exit init_rwsem_exit(void);

struct rw_semaphore rwsem ;

int __init init_rwsem_init(void) 
{	 
	init_rwsem( &rwsem );   //读写信号量初始化
	/* 输出读写信号量中的字段信息*/
	printk("<0>after init_rwsem, count: %d\n",rwsem.count);
	printk("<0>after init_rwsem, wait_lock.lock: 0x%0x\n",rwsem.wait_lock.raw_lock.slock);

	return 0;
}

void __exit init_rwsem_exit(void) 
{ 
	printk("<0>exit!\n");
}

module_init(init_rwsem_init); 
module_exit(init_rwsem_exit);
