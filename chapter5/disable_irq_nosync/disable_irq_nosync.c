/********************************************************************************
* File Name:	disable_irq_nosync.c
* Description:	第5章实例训练          
* Reference book:《Linux内核API完全参考手册》邱铁，周玉，邓莹莹 ，机械工业出版社.2010.9  
* E_mail:openlinux2100@gmail.com			                
*
********************************************************************************/

#include <linux/interrupt.h>
#include <linux/module.h>
MODULE_LICENSE("GPL");                                      

 //自定义中断中断处理函数，此处只显示参数data的值与提示程序的执行位置
static irqreturn_t irq_handler(int data,void *dev_id)
{
	printk("<0>the data is :%d\n",data);//data对应的是相应的中断号
  	printk("<0>in the interrupt handler function\n");
   	return IRQ_NONE; // 函数返回，返回值类型为irqreturn_t类型，可取值为IRQ_NONE、IRQ_HANDLED,此处两者皆可
}

static int irq=11;    //定义中断号，并初始化为11

static int __init disable_irq_nosync_init(void) 
{
	int result=0;
	printk("<0>into disable_irq_nosync_init\n");
        /*申请一个新的中断，中断号对应的是10，中断处理函数是myhandler()，
                 中断类型是IRQF_DISABLED,中断设备明是A_NEW_Device,设备编号是NULL(即不对应真实的设备)*/
	result=request_irq(irq,irq_handler,IRQF_DISABLED,"A_New_Device",NULL);                
	disable_irq_nosync(irq);//调用disable_irq_nosync()函数，使中断的深度增加1,可以被替换成disabel_irq(irq);     
	enable_irq(irq);     //调用enable_irq()函数，使中断的深度减少1，同时触发中断处理函数执行
	printk("<0>the result of the request_irq is: %d\n",result);   //输出中断申请的结果
	printk("<0>out disable_irq_nosync_init\n");
	return 0; 
}

static void __exit disable_irq_nosync_exit(void)
{ 
	free_irq(irq,NULL);  //释放中断
	printk("<0>Goodbye disable_irq_nosync\n");
 	return;
}

module_init(disable_irq_nosync_init);
module_exit(disable_irq_nosync_exit);
