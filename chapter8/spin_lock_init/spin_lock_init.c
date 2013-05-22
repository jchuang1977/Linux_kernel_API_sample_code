/********************************************************************************
* File Name:	spin_lock_init.c
* Description:	第8章实例训练          
* Reference book:《Linux内核API完全参考手册》邱铁，周玉，邓莹莹 ，机械工业出版社.2010.9  
* E_mail:openlinux2100@gmail.com			                
*
********************************************************************************/

#include <linux/spinlock.h> 
#include <linux/init.h>
#include <linux/module.h> 

MODULE_LICENSE("GPL"); 
static int __init spin_lock_init_init(void); 
static void __exit spin_lock_init_exit(void);

spinlock_t lock = SPIN_LOCK_UNLOCKED;

int __init spin_lock_init_init(void) 
{	
	/*输出宏SPIN_LOCK_UNLOCKED的相关信息*/
	printk("<0>SPIN_LOCK_UNLOCKED: %d\n",SPIN_LOCK_UNLOCKED.raw_lock.slock);
	
	spin_lock_init( &lock );  //初始化自旋锁
	printk("<0>after init, slock: %d\n",lock.raw_lock.slock);
	
	printk("<0>\n");

	spin_lock( &lock );      //第一次获取自旋锁
	printk("<0>first spin_lock, slock: %d\n",lock.raw_lock.slock);
	spin_unlock( &lock );    //第一次释放自旋锁
	printk("<0>first spin_unlock, slock: %d\n",lock.raw_lock.slock);

	printk("<0>\n");

	spin_lock( &lock );      //第二次获取自旋锁
	printk("<0>second spin_lock, slock: %d\n",lock.raw_lock.slock);
	spin_unlock( &lock );    //第二次释放自旋锁
	printk("<0>second spin_unlock, slock: %d\n",lock.raw_lock.slock);

	return 0;
}

void __exit spin_lock_init_exit(void) 
{ 
	printk("<0>exit!\n");
}

module_init(spin_lock_init_init); 
module_exit(spin_lock_init_exit);
