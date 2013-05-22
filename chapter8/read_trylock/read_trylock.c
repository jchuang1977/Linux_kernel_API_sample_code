/********************************************************************************
* File Name:	read_trylock.c
* Description:	第8章实例训练          
* Reference book:《Linux内核API完全参考手册》邱铁，周玉，邓莹莹 ，机械工业出版社.2010.9  
* E_mail:openlinux2100@gmail.com			                
*
********************************************************************************/

#include <linux/spinlock.h> 
#include <linux/sched.h>
#include <linux/wait.h> 
#include <linux/module.h> 
MODULE_LICENSE("GPL"); 
static int __init read_trylock_init(void); 
static void __exit read_trylock_exit(void);

rwlock_t rwlock = RW_LOCK_UNLOCKED;

int __init read_trylock_init(void) 
{
	int ret;
	rwlock_init( &rwlock );     //读写自旋锁初始化
	read_lock( &rwlock );       //读者申请得到读写锁rwlock
	/* 输出读写自旋锁lock字段信息*/
	printk("<0>after read_lock,lock: 0x%x\n",rwlock.raw_lock.lock);
	
	printk("<0>\n");
	ret = read_trylock( &rwlock );   //读者试图获得自旋锁
	if( ret == 1 )
	{
		printk("<0>after read_trylock, lock: 0x%x\n",rwlock.raw_lock.lock);
		read_unlock( &rwlock );
		printk("<0>after read_unlock, lock: 0x%x\n",rwlock.raw_lock.lock);
	}
	else
	{
		printk("<0>read_trylock could't get the lock!\n");
	}	
	printk("<0>\n");	

	read_unlock( &rwlock );    //读者释放读写锁rwlock
	printk("<0>after read_unlock,lock: 0x%x\n",rwlock.raw_lock.lock);

	return 0;
}

void __exit read_trylock_exit(void) 
{ 
	printk("<0>exit!\n");
}

module_init(read_trylock_init); 
module_exit(read_trylock_exit);
