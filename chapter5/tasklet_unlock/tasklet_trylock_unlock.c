/********************************************************************************
* File Name:	tasklet_trylock_unlock.c
* Description:	第5章实例训练          
* Reference book:《Linux内核API完全参考手册》邱铁，周玉，邓莹莹 ，机械工业出版社.2010.9  
* E_mail:openlinux2100@gmail.com			                
*
********************************************************************************/

#include<linux/interrupt.h>
#include <linux/module.h>
MODULE_LICENSE("GPL"); static unsigned long data=0;
static struct tasklet_struct tasklet;

//自定义软中断处理函数
static void irq_tasklet_action(unsigned long data)
{
	int result=-1;
  	printk("<0>tasklet running. by author\n");
	printk("<0>in irq_tasklet_action the state of the tasklet is :%ld\n",(&tasklet)->state);  //显示当前中断的状态
	result=tasklet_trylock(&tasklet);                            //给中断加锁
	if(result==0)                                                //显示加锁结果
		printk("<0>tasklet_trylock failed\n");
	else
		printk("<0>tasklet_trylock success\n");
	printk("<0>out irq_tasklet_action\n");
   	return;
}

static int  __init tasklet_trylock_unlock_init(void) 
{
	int result=-1;	
  	printk("<0>into tasklet_trylock_unlock_init\n");
	tasklet_init(&tasklet,irq_tasklet_action,data);       //初始化软中断变量
 	tasklet_schedule(&tasklet);                       //将软中断变量加入中断队列
	printk("<0>the state of the tasklet before tasklet_trylock is :%ld\n",tasklet.state);  //显示中断状态
        result=tasklet_trylock(&tasklet);                   //对中断加锁
	if(result==0)                                      //显示加锁结果
		printk("<0>tasklet_trylock failed\n");
	else
		printk("<0>tasklet_trylock success\n");
	printk("<0>the state of the tasklet after tasklet_trylock is :%ld\n",tasklet.state);
	tasklet_unlock(&tasklet);                         //对中断解锁
	printk("<0>the state of the tasklet after tasklet_unlock is :%ld\n",tasklet.state);
   	tasklet_kill(&tasklet);                           //杀死中断，恢复未调度之前的状态
	printk("<0>out tasklet_trylock_unlock_init\n");
	return 0; 
}

static void  __exit tasklet_trylock_unlock_exit(void)
{
	printk("<0>Goodbye tasklet_trylock_unlock\n");
 	return;
}

module_init(tasklet_trylock_unlock_init);
module_exit(tasklet_trylock_unlock_exit);
