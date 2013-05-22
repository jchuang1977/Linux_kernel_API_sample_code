/********************************************************************************
* File Name:	seqlock_init.c
* Description:	第8章实例训练          
* Reference book:《Linux内核API完全参考手册》邱铁，周玉，邓莹莹 ，机械工业出版社.2010.9  
* E_mail:openlinux2100@gmail.com			                
*
********************************************************************************/

#include <linux/seqlock.h> 
#include <linux/init.h> 
#include <linux/module.h> 

MODULE_LICENSE("GPL"); 
static int __init seqlock_init_init(void); 
static void __exit seqlock_init_exit(void);

seqlock_t seqlock ;

int __init seqlock_init_init(void) 
{	 
	seqlock_init( &seqlock );       //初始化顺序锁
	printk("<0>after seqlock_init, lock: 0x%x\n",seqlock.lock.raw_lock.slock);
	printk("<0>after seqlock_init, sequence: %d\n\n", seqlock.sequence);

	write_seqlock( &seqlock );     //写者第一次申请顺序锁
	printk("<0>first write_seqlock, lock: 0x%x\n",seqlock.lock.raw_lock.slock);
	printk("<0>first write_seqlock, sequence: %d\n\n", seqlock.sequence);

	write_sequnlock( &seqlock );   //写者第一次释放顺序锁
	printk("<0>first write_sequnlock, lock: 0x%x\n",seqlock.lock.raw_lock.slock);
	printk("<0>first write_sequnlock, sequence: %d\n\n", seqlock.sequence);

	write_seqlock( &seqlock );     //写者第二次申请顺序锁
	printk("<0>second write_seqlock, lock: 0x%x\n",seqlock.lock.raw_lock.slock);
	printk("<0>second write_seqlock, sequence: %d\n\n", seqlock.sequence);


	write_sequnlock( &seqlock );   //写者第二次申请顺序锁
	printk("<0>second write_sequnlock, lock: 0x%x\n",seqlock.lock.raw_lock.slock);
	printk("<0>second write_sequnlock, sequence: %d\n\n", seqlock.sequence);
	
	return 0;
}

void __exit seqlock_init_exit(void) 
{ 
	printk("<0>exit!\n");
}

module_init(seqlock_init_init); 
module_exit(seqlock_init_exit);
