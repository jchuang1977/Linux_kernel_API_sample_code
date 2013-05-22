/********************************************************************************
* File Name:	set_irq_type.c
* Description:	第5章实例训练          
* Reference book:《Linux内核API完全参考手册》邱铁，周玉，邓莹莹 ，机械工业出版社.2010.9  
* E_mail:openlinux2100@gmail.com			                
*
********************************************************************************/

#include <linux/interrupt.h>
#include<linux/irq.h>
#include <linux/module.h>
MODULE_LICENSE("GPL");   
                                   
//#define IRQ_TYPE_NONE		0x00000000	/* Default, unspecified type */
//#define IRQ_TYPE_EDGE_RISING	0x00000001	/* Edge rising type */
//#define IRQ_TYPE_EDGE_FALLING	0x00000002	/* Edge falling type */
//#define IRQ_TYPE_EDGE_BOTH (IRQ_TYPE_EDGE_FALLING | IRQ_TYPE_EDGE_RISING)
//#define IRQ_TYPE_LEVEL_HIGH	0x00000004	/* Level high type */
//#define IRQ_TYPE_LEVEL_LOW	0x00000008	/* Level low type */
//#define IRQ_TYPE_SENSE_MASK	0x0000000f	/* Mask of the above */
//#define IRQ_TYPE_PROBE		0x00000010	/* Probing in progress */


//自定义中断处理函数
static irqreturn_t irq_handler(int irq,void *dev_id)
{
	printk("<0>the irq is :%d\n",irq);
  	printk("<0>in the interrupt handler function\n");
   	return IRQ_WAKE_THREAD;
}

//自定义中断线程处理函数
static irqreturn_t irq_thread_fn(int irq,void *dev_id)
{
	printk("<0>the irq is :%d\n",irq);
  	printk("<0>in the thread handler function\n");
   	return IRQ_HANDLED;
}


static int irq=10;  //static int irq=1000;
static int __init set_irq_type_init(void) 
{
	int result=-1,result1=-1;
	int irqtype=1;	
	printk("<0>into set_irq_type_init\n");
	result=request_threaded_irq(irq,irq_handler,irq_thread_fn,IRQF_DISABLED,"A_NEW_DEVICE",NULL);
	result1=set_irq_type(irq,irqtype); //调用set_irq_type()函数设置中断类型
	printk("<0>the request_threaded_irq result is: %d\n",result);
	printk("<0>the set_irq_type result is:%d\n",result1);
	printk("<0>out set_irq_type_init\n");
	return 0; 
}

static void __exit set_irq_type_exit(void)
{ 
	free_irq(irq,NULL);
	printk("<0>Goodbye set_irq_type\n");
 	return;
}
module_init(set_irq_type_init);
module_exit(set_irq_type_exit);
