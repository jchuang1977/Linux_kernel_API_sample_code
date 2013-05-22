/********************************************************************************
* File Name:	down_timeout.c
* Description:	第8章实例训练          
* Reference book:《Linux内核API完全参考手册》邱铁，周玉，邓莹莹 ，机械工业出版社.2010.9  
* E_mail:openlinux2100@gmail.com			                
*
********************************************************************************/

#include <linux/semaphore.h> 
#include <linux/init.h> 
#include <linux/module.h> 

MODULE_LICENSE("GPL"); 
static int __init down_timeout_init(void); 
static void __exit down_timeout_exit(void);

struct semaphore sema;

int __init down_timeout_init(void) 
{
	int ret;
	long iffies = 1000;      //1000个时钟节拍，即是4s
	sema_init( &sema, 5 );   //信号量初始化, count = 5
	/* 输出初始化后信号量的信息 */
	printk("<0>after sema_init, sema.lock: 0x%x\n",sema.lock.raw_lock.slock);
	printk("<0>after sema_init, sema.count: %d\n",sema.count);
	
	printk("<0>\n");
	ret = down_timeout( &sema, iffies);            //获取信号量
	/* 输出down_timeout操作后信号量的信息 */
	printk("<0>first down_timeout, ret = %d\n", ret);
	printk("<0>first down_timeout, sema.lock: 0x%x\n",sema.lock.raw_lock.slock);
	printk("<0>first down_timeout, sema.count: %d\n",sema.count);

	sema_init( &sema, 0 );   //信号量初始化, count = 0
	printk("<0>\n");
	ret = down_timeout( &sema, iffies);            
	
	printk("<0>second down_timeout, ret = %d\n", ret);
	printk("<0>second down_timeout, sema.lock: 0x%x\n",sema.lock.raw_lock.slock);
	printk("<0>second down_timeout, sema.count: %d\n",sema.count);

	return 0;
}

void __exit down_timeout_exit(void) 
{ 
	printk("<0>exit!\n");
}

module_init(down_timeout_init); 
module_exit(down_timeout_exit);
