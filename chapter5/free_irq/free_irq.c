/********************************************************************************
* File Name:	free_irq.c
* Description:	第5章实例训练          
* Reference book:《Linux内核API完全参考手册》邱铁，周玉，邓莹莹 ，机械工业出版社.2010.9  
* E_mail:openlinux2100@gmail.com			                
*
********************************************************************************/

#include <linux/interrupt.h>
#include<linux/irq.h>
#include <linux/module.h>
MODULE_LICENSE("GPL");   

static int irq=11;   //定义中断号	 
 
//定义中断处理函数
static irqreturn_t irq_handler(int data,void *dev_id)
{
	printk("<0>the data is :%d\n",data);      //data对应的是中断号
  	printk("<0>in the interrupt handler function\n");
   	return IRQ_NONE;   //返回值类型是irqreturn_t 类型，可取值有IRQ_NONE、IRQ_HANDLED
}	 
 
static int __init free_irq_init(void)
{
       int result=0; //保存函数执行结果
       printk("<0>into free_irq_init\n");

       //申请中断，对应的中断号是11,中断处理函数是myhandler()，中断类型是IRQF_DISABLED
       result=request_irq(irq,irq_handler,IRQF_DISABLED,"A_New_Device",NULL);
       printk("<0>the result of the request_irq is: %d \n",result);
       printk("<0>out free_irq_init\n");
       return 0;
}	 
 
static void __exit free_irq_exit(void)
{ 
	free_irq(irq,NULL);      //调用函数free_irq()释放申请的中断
	printk("<0>Goodbye free_irq\n");
 	return;
}	 
 
module_init(free_irq_init);
module_exit(free_irq_exit);
