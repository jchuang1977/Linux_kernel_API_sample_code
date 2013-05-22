/********************************************************************************
* File Name:	remove_irq.c
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

//自定义中断处理函数，在此只是起显示作用
static irqreturn_t irq_handler(int data,void *dev_id)
{
	printk("<0>the data is :%d\n",data);
  	printk("<0>in the interrupt handler function\n");
   	return IRQ_NONE;
}

/*声明一个变量，中断号为10，中断处理函数是myhandler()，中断的类型是IRQF_DISABLED类型的，
    中断对应的设备名是A_New_Device，设备编号是NULL(即设备不真实存在)*/
static struct irqaction act =
{
	.irq=11,
	.handler=irq_handler,
	.flags=IRQF_DISABLED,
	.name="A_New_Device",
	.dev_id=NULL
};

static int __init remove_irq_init(void) 
{
	int result=0;
	printk("<0>into remove_irq_init\n");
	struct irqaction *myact=&act;
	result=request_irq(myact->irq,myact->handler,myact->flags,myact->name,myact->dev_id);//申请中断
	printk("<0>the result is: %d\n",result);//显示申请结果
	printk("<0>out remove_irq_init\n");
	return 0; 
}

static void __exit remove_irq_exit(void)
{ 
	printk("<0>remove the irq in the remove_irq_exit function\n");
	remove_irq(irq,&act);//调用函数remove_irq()，irq是对应的中断号，act是对应的中断变量
	printk("<0>Goodbye remove_irq\n");
 	return;
}
module_init(remove_irq_init);
module_exit(remove_irq_exit);
