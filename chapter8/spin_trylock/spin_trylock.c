/********************************************************************************
* File Name:	spin_trylock.c
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
static int __init spin_trylock_init(void); 
static void __exit spin_trylock_exit(void);

//子进程函数定义
spinlock_t lock = SPIN_LOCK_UNLOCKED;
int ret;

int my_function(void * argc)
{
	printk("<0>\nin child, the current pid is:%d\n",current->pid);      //显示子进程PID
	ret = spin_trylock( &lock );	
	if( ret == 1 )
	{
		printk("<0>in child, after spin_trylock, slock: %d\n",lock.raw_lock.slock);
		spin_unlock( &lock );
		printk("<0>in child, after spin_unlock, slock: %d\n",lock.raw_lock.slock);
	}
	else
	{
		printk("<0>spin_trylock could't get the lock!\n");
		printk("<0>need the parent to unlock.\n\n");
	}
	return 0;
}

int __init spin_trylock_init(void) 
{
	int ret0;

	printk("<0>in parent, the current pid is:%d\n",current->pid);   //显示父进程PID

	spin_lock_init( &lock );  //初始化自旋锁
	spin_lock( &lock );       //获取自旋锁
	printk("<0>after spin_lock, slock: %d\n",lock.raw_lock.slock);

	ret0 = kernel_thread(my_function,NULL,CLONE_KERNEL);	
	
	/*init_waitqueue_head( &head );              //初始化等待队列的头结点
	init_waitqueue_entry( &data, current );    //用当前进程初始化等待队列中的节点元素
	add_wait_queue( &head, &data );            //将当前进程加入等待队列
	ret1 = sleep_on_timeout( &head, 100 );     //将等待队列中的进程置于睡眠状态*/

	spin_unlock( &lock );    //释放自旋锁
	printk("<0>parent unlock!\n");
	printk("<0>after spin_unlock, slock: %d\n",lock.raw_lock.slock);

	return 0;
}

void __exit spin_trylock_exit(void) 
{ 
	printk("<0>exit!\n");
}

module_init(spin_trylock_init); 
module_exit(spin_trylock_exit);
