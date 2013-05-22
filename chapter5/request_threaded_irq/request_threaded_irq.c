/********************************************************************************
* File Name:	request_threaded_irq.c
* Description:	第5章实例训练          
* Reference book:《Linux内核API完全参考手册》邱铁，周玉，邓莹莹 ，机械工业出版社.2010.9  
* E_mail:openlinux2100@gmail.com			                
*
********************************************************************************/

#include <linux/interrupt.h>
#include<linux/irq.h>
#include <linux/module.h>
MODULE_LICENSE("GPL");                                      

//自定义中断处理函数
static irqreturn_t irq_handler(int data,void *dev_id)
{
	printk("<0>the data is :%d\n",data);
  	printk("<0>in the interrupt handler function\n");
   	return IRQ_WAKE_THREAD;     //触发中断线程函数执行
}

//自定义中断线程处理函数
static irqreturn_t irq_thread_fn(int data,void *dev_id)
{
	printk("<0>the data is :%d\n",data);
  	printk("<0>in the interrupt thread function\n");
   	return IRQ_HANDLED;
}


static int irq=10;

static int __init request_threaded_irq_init(void) 
{
	int result=0;
	printk("<0>into request_threaded_irq_init\n");
	/* 调用request_threaded_irq()函数，irq是对应的中断编号，myhandler是定义的中断处理函数，
            mythread_fn是对应的中断线程处理函数，IRQF_DISABLED中断的类型*/
	result=request_threaded_irq(irq,irq_handler,irq_thread_fn,IRQF_DISABLED,"A_New_Device",NULL);
	printk("<0>the result of the request_threaded_irq is: %d\n",result);
	disable_irq(irq);
	enable_irq(irq);
	printk("<0>out request_threaded_irq_init\n");
	return 0; 
}

static void __exit request_threaded_irq_exit(void)
{ 
	free_irq(irq,NULL); //释放申请的中断
	printk("<0>Goodbye request_threaded_irq\n");
 	return;
}
module_init(request_threaded_irq_init);
module_exit(request_threaded_irq_exit);
