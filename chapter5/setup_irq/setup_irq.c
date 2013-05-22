/********************************************************************************
* File Name:	setup_irq.c
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
   	return IRQ_NONE;
}

static int irq=10;

/*
      定义一个struct irqaction 变量,irq 为中断号，handler为中断处理函数，flags为中断类型，
   name为中断设备名，dev_id 为中断设备编号（为NULL说明设备是并不真实存在的）
*/
static struct irqaction  act =
{
	.irq=10,
	.handler=irq_handler,
	.flags=IRQF_DISABLED,
	.name="A_New_Device",
	.dev_id=NULL
};

static int __init setup_irq_init(void) 
{
	int result=0;
	printk("<0>into setup_irq_init\n");
	result=setup_irq(irq,&act);  //调用函数setup_irq()完成申请中断
	printk("the result of the setup_irq is: %d\n",result);
	printk("<0>out setup_irq_init\n");
	return 0; 
}

static void __exit setup_irq_exit(void)
{ 
	remove_irq(irq,&act);     //移除申请的中断
	printk("<0>Goodbye setup_irq\n");
 	return;
}
module_init(setup_irq_init);
module_exit(setup_irq_exit);
