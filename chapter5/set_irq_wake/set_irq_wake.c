/********************************************************************************
* File Name:	set_irq_wake.c
* Description:	第5章实例训练          
* Reference book:《Linux内核API完全参考手册》邱铁，周玉，邓莹莹 ，机械工业出版社.2010.9  
* E_mail:openlinux2100@gmail.com			                
*
********************************************************************************/

#include<linux/module.h>
#include<linux/interrupt.h> 
MODULE_LICENSE("GPL");    

//自定义中断处理函数，在此只有显示功能 
static irqreturn_t irq_handler(int data,void *dev_id)
{
	printk("<0>the data is :%d\n",data);
  	printk("<0>in the interrupt handler function\n");	
   	return IRQ_NONE;
}
static int irq=3;
static int __init set_irq_wake_init(void) 
{
	int result=0,result1=0,result2=0;
	printk("<0>into set_irq_wake_init\n");
	result=request_irq(irq,irq_handler,IRQF_DISABLED,"A_New_Device",NULL);//申请中断
	result1=set_irq_wake(irq,0);//调用disable_irq_wake()函数 ,可替换为set_irq_wake(irq,0);
	result2=set_irq_wake(irq,1);  //调用enable_irq_wake()函数,可替换为set_irq_wake(irq,1);		
	printk("<0>the request_irq result is: %d\n",result);	//显示函数调用结果
	printk("<0>the set_irq_wake(irq,0) result is :%d\n",result1);
	printk("<0>the set_irq_wake(irq,1) result is :%d\n",result2);	
	printk("<0>out set_irq_wake_init\n");
	return 0;  
}

static void __exit set_irq_wake_exit(void)
{ 
	free_irq(irq,NULL); //释放申请的中断
	printk("<0>Goodbye set_irq_wake\n");
 	return;
}  

module_init(set_irq_wake_init);
module_exit(set_irq_wake_exit);
