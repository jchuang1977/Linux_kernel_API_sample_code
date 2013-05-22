/********************************************************************************
* File Name:	request_irq.c
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
   	return IRQ_HANDLED;
}

static int irq=10; //11

static int __init request_irq_init(void) 
{
	int result=0;
	printk("<0>into request_irq_init\n");
	/*
	     调用函数request_irq()申请中断，irq中断编号，myhandler中断处理函数，
          IRQF_DISABLED中断类型,"A_New_Device"中断设备名，NULL设备编号，
                    设备编号为NULL说明设备不真实存在
	*/
	result=request_irq(irq,irq_handler,IRQF_DISABLED,"A_New_Device",NULL);
	printk("<0>the result of the request_irq is: %d\n",result);   //显示申请结果
	printk("<0>out request_irq_init\n");
	return 0; 
}

static void __exit request_irq_exit(void)
{ 
	free_irq(irq,NULL); //释放申请的中断
	printk("<0>Goodbye request_irq\n");
 	return;
}

module_init(request_irq_init);
module_exit(request_irq_exit);
