/********************************************************************************
* File Name:	__set_irq_handler.c
* Description:	第5章实例训练          
* Reference book:《Linux内核API完全参考手册》邱铁，周玉，邓莹莹 ，机械工业出版社.2010.9  
* E_mail:openlinux2100@gmail.com			                
*
********************************************************************************/

#include <linux/interrupt.h>
#include<linux/irq.h>
#include <linux/module.h>
MODULE_LICENSE("GPL");   
static int irq=11;

//自定义中断处理函数
static irqreturn_t irq_handler(int irq,void *dev_id)
{
	printk("<0>the irq is :%d\n",irq);
  	printk("<0>in the interrupt handler function\n");
   	return IRQ_WAKE_THREAD;   //触发中断线程处理函数执行
}

//自定义中断线程处理函数
static irqreturn_t irq_thread_fn(int irq,void *dev_id)
{
	printk("<0>the irq is :%d\n",irq);
  	printk("<0>in the thread handler function\n");
   	return IRQ_HANDLED;
}

static int __init __set_irq_handler_init(void) 
{
	unsigned int result=0;
	printk("<0>into __set_irq_handler_init\n");
        //申请中断
	result=request_threaded_irq(irq,irq_handler,irq_thread_fn,IRQF_DISABLED,"A_NEW_DEVICE",NULL);
	__set_irq_handler(irq,NULL,1,"A-NEW-HANDLER");  //调用函数__set_irq_handler()设置新的中断处理函数，此处设置为NULL
	enable_irq(irq);  //触发中断处理函数执行
	printk("<0>the result of the request_threaded_irq is: %d\n",result);
	printk("<0>out __set_irq_handler_init\n");
	return 0; 
}

static void __exit __set_irq_handler_exit(void)
{ 
	free_irq(irq,NULL);//释放申请的中断
	printk("<0>Goodbye __set_irq_handler\n");
 	return;
}

module_init(__set_irq_handler_init);
module_exit(__set_irq_handler_exit);
