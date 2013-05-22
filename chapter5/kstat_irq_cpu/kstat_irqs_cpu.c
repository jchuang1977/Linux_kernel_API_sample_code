/********************************************************************************
* File Name:	kstat_irqs_cpu.c
* Description:	第5章实例训练          
* Reference book:《Linux内核API完全参考手册》邱铁，周玉，邓莹莹 ，机械工业出版社.2010.9  
* E_mail:openlinux2100@gmail.com			                
*
********************************************************************************/

#include <linux/module.h>
#include <linux/kernel_stat.h>
MODULE_LICENSE("GPL"); 

static int __init kstat_irqs_cpu_init(void) 
{
	unsigned int data;  //保存函数调用结果
	unsigned int irq=0; //中断号
	int cpu=0;          //CPU编号
	printk("<0>into kstat_irqs_cpu_init\n");         /*双层循环用于显示数组kstat_irqs中的值 */	                             
	for(irq=0;irq<NR_IRQS;irq++)
	{
		for(cpu=0;cpu<NR_CPUS;cpu++)
		{
			data=kstat_irqs_cpu(irq,cpu);  //调用函数kstat_irqs_cpu()，irq是对应的中断号，cpu是对应的cpu编号，返回的值是数组中的值
			if(data!=0) 		 	
			{
			     printk("<0>data is:%d---current cpu is:%d---current irq is:%d\n",data,cpu,irq);
                     	}
		}
	}
	printk("<0>The num of the NR_IRQS is:%d\n",NR_IRQS);
	printk("<0>The num of the NR_CPUS is:%d\n",NR_CPUS);
	printk("<0>out kstat_irqs_cpu_init\n"); 
	return 0; 
}  

static void __exit kstat_irqs_cpu_exit(void) 
{ 	
	printk("<0>Goodbye kstat_irqs_cpu\n"); 
}  

module_init(kstat_irqs_cpu_init); 
module_exit(kstat_irqs_cpu_exit);
