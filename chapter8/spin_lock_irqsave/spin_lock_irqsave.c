/********************************************************************************
* File Name:	spin_lock_irqsave.c
* Description:	第8章实例训练          
* Reference book:《Linux内核API完全参考手册》邱铁，周玉，邓莹莹 ，机械工业出版社.2010.9  
* E_mail:openlinux2100@gmail.com			                
*
********************************************************************************/

#include <linux/spinlock.h> 
#include <linux/hardirq.h>
#include <linux/init.h> 
#include <linux/module.h> 

MODULE_LICENSE("GPL"); 
static int __init spin_lock_irqsave_init(void); 
static void __exit spin_lock_irqsave_exit(void);

int __init spin_lock_irqsave_init(void) 
{	
	
	unsigned long flags = 0;

	spinlock_t lock = SPIN_LOCK_UNLOCKED; 	
	
	spin_lock_init( &lock );    //初始化自旋锁
	printk("<0>after init, slock: %d\n",lock.raw_lock.slock);
	
	
	printk("<0>lock........\n");
	/*获取自旋锁同时禁止本地中断,同时把标志寄存器的值保存到变量flag中*/
	spin_lock_irqsave( &lock, flags );    
	
	printk("<0>irqs_disabled():%d\n",irqs_disabled());  //查看中断是否被禁止
	printk("<0>after spin_lock_irq, slock: %d\n",lock.raw_lock.slock);

	printk("<0>flags = 0x%lx\n",flags);  //输出标志寄存器的值

	printk("<0>unlock........\n");
	/*释放自旋锁同时使能本地中断,同时恢复标志寄存器的值为变量flags所保存的值*/
	spin_unlock_irqrestore( &lock, flags );
	printk("<0>irqs_disabled():%d\n",irqs_disabled());
	
	printk("<0>after spin_unlock_irqrestore, slock: %d\n",lock.raw_lock.slock);


	return 0;
}

void __exit spin_lock_irqsave_exit(void) 
{ 
	printk("<0>exit!\n");
}

module_init(spin_lock_irqsave_init); 
module_exit(spin_lock_irqsave_exit);
