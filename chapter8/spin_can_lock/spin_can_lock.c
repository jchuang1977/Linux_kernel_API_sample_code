/********************************************************************************
* File Name:	spin_can_lock.c
* Description:	第8章实例训练          
* Reference book:《Linux内核API完全参考手册》邱铁，周玉，邓莹莹 ，机械工业出版社.2010.9  
* E_mail:openlinux2100@gmail.com			                
*
********************************************************************************/

#include <linux/spinlock.h> 
#include <linux/module.h> 

MODULE_LICENSE("GPL"); 
static int __init spin_can_lock_init(void); 
static void __exit spin_can_lock_exit(void);

/**
 * spin_can_lock - would spin_trylock() succeed?
 * @lock: the spinlock in question.
 */
//#define spin_can_lock(lock)	(!spin_is_locked(lock))

spinlock_t lock = SPIN_LOCK_UNLOCKED;

int __init spin_can_lock_init(void) 
{	 
	int ret;

	spin_lock_init( &lock );  //初始化自旋锁
	spin_lock( &lock );       //获取自旋锁
	printk("<0>after spin_lock, before spin_unlock:\n");
	printk("<0>slock: %d\n",lock.raw_lock.slock);

	ret = spin_can_lock( &lock );   //是否可以对自旋锁lock加锁
	if( ret )
	{
		printk("<0>can get lock\n");
	}
	else
	{
		printk("<0>can not get lock\n");
	}

	spin_unlock( &lock );    //释放自旋锁
	printk("<0>after spin_unlock:\n");
	printk("<0>slock: %d\n",lock.raw_lock.slock);

	ret = spin_can_lock( &lock );
	if( ret )
	{
		printk("<0>can get lock\n");
	}
	else
	{
		printk("<0>can not get lock\n");
	}

	return 0;
}

void __exit spin_can_lock_exit(void) 
{ 
	printk("<0>exit!\n");
}

module_init(spin_can_lock_init); 
module_exit(spin_can_lock_exit);
