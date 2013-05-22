/********************************************************************************
* File Name:	__tasklet_schedule.c
* Description:	第5章实例训练          
* Reference book:《Linux内核API完全参考手册》邱铁，周玉，邓莹莹 ，机械工业出版社.2010.9  
* E_mail:openlinux2100@gmail.com			                
*
********************************************************************************/

#include <linux/interrupt.h> 
#include <linux/module.h> 
#include <linux/init.h> 
MODULE_LICENSE("GPL");
static unsigned long data=0; 
static struct tasklet_struct tasklet; 

//自定义软中断处理函数，在此只有显示功能
static void irq_tasklet_action(unsigned long data) 
{ 
	printk("<0>in the irq_tasklet_action the state of the tasklet is :%ld\n",(&tasklet)->state); 
  	printk("<0>tasklet running. by author\n"); 
   	return; 
} 

static int  __init __tasklet_schedule_init(void) 
{ 
  	printk("<0>into __tasklet_schedule\n"); 
	tasklet_init(&tasklet,irq_tasklet_action,data); //初始化一个struct tasklet_struct 变量，即申请一个软中断变量
	printk("<0>the state of the tasklet after tasklet_init is :%ld\n",(&tasklet)->state); //显示软中断状态
	if (!test_and_set_bit(TASKLET_STATE_SCHED, &tasklet.state))
		__tasklet_schedule(&tasklet);                //将中断变量放入软中断执行队列
	printk("<0>the state of the tasklet after __tasklet_schedule is :%ld\n",(&tasklet)->state);   //显示中断当前状态	 
	printk("<0>out __tasklet_schedule_init\n"); 
	return 0; 
} 

static void  __exit __tasklet_schedule_exit(void) 
{ 
	printk("<0>Goodbye __tasklet_schedule\n"); 
 	return; 
} 

module_init(__tasklet_schedule_init); 
module_exit(__tasklet_schedule_exit);
