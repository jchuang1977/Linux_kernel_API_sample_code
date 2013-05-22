/********************************************************************************
* File Name:	write_lock.c
* Description:	第8章实例训练          
* Reference book:《Linux内核API完全参考手册》邱铁，周玉，邓莹莹 ，机械工业出版社.2010.9  
* E_mail:openlinux2100@gmail.com			                
*
********************************************************************************/

#include <linux/spinlock.h> 
#include <linux/init.h> 
#include <linux/module.h> 

MODULE_LICENSE("<0>GPL"); 
static int __init write_lock_init(void); 
static void __exit write_lock_exit(void);

rwlock_t rwlock = RW_LOCK_UNLOCKED;

int __init write_lock_init(void) 
{	 
	printk("<0>RW_LOCK_UNLOCKED: 0x%x\n",RW_LOCK_UNLOCKED.raw_lock.lock);
	
	rwlock_init( &rwlock );      //读写自旋锁初始化
	/* 输出读写自旋锁lock字段信息*/
	printk("<0>after rwlock_init, lock: 0x%x\n\n",rwlock.raw_lock.lock);

	write_lock( &rwlock );      //写者申请得到读写锁rwlock
	printk("<0>after write_lock, lock: 0x%x\n",rwlock.raw_lock.lock);	

	write_unlock( &rwlock );    //写者释放读写锁rwlock
	printk("<0>after write_unlock, lock: 0x%x\n",rwlock.raw_lock.lock);

	return 0;
}

void __exit write_lock_exit(void) 
{ 
	printk("<0>exit!\n");
}

module_init(write_lock_init); 
module_exit(write_lock_exit);
