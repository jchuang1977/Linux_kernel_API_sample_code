/********************************************************************************
* File Name:	spin_unlock_wait.c
* Description:	第8章实例训练          
* Reference book:《Linux内核API完全参考手册》邱铁，周玉，邓莹莹 ，机械工业出版社.2010.9  
* E_mail:openlinux2100@gmail.com			                
*
********************************************************************************/

#include <linux/spinlock.h> 
#include <linux/module.h> 

MODULE_LICENSE("GPL"); 
static int __init spin_unlock_wait_init(void); 
static void __exit spin_unlock_wait_exit(void);

spinlock_t lock;
int __init spin_unlock_wait_init(void) 
{	 
	spin_lock_init( &lock );   //初始化自旋锁
	printk("<0>init, slock: %d\n",lock.raw_lock.slock);
	spin_lock( &lock );        //spin_lock获取自旋锁
	printk("<0>spin_lock, slock: %d\n",lock.raw_lock.slock);
	spin_unlock( &lock );      //spin_unlock释放自旋锁
	printk("<0>spin_unlock, slock: %d\n",lock.raw_lock.slock);
	
	spin_unlock_wait( &lock ); //spin_unlock_waitd等待自旋锁
	printk("<0>spin_unlock_wait, slock: %d\n",lock.raw_lock.slock);

	return 0;
}

void __exit spin_unlock_wait_exit(void) 
{ 
	printk("<0>exit!\n");
}

module_init(spin_unlock_wait_init); 
module_exit(spin_unlock_wait_exit);
