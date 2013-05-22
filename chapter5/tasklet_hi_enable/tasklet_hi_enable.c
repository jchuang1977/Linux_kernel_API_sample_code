/********************************************************************************
* File Name:	tasklet_hi_enable.c
* Description:	第5章实例训练          
* Reference book:《Linux内核API完全参考手册》邱铁，周玉，邓莹莹 ，机械工业出版社.2010.9  
* E_mail:openlinux2100@gmail.com			                
*
********************************************************************************/

#include <linux/interrupt.h>
#include <linux/module.h>
MODULE_LICENSE("GPL");   

static unsigned long data=0;
static struct tasklet_struct tasklet;
//自定义软中断处理函数  ，在此处只有显示的功能                                   
static void irq_tasklet_action(unsigned long data)
{	
  	printk("<0>tasklet running. by author\n");
   	return;
}

static int __init tasklet_hi_enable_init(void) 
{
  	printk("<0>into tasklet_hi_enable_init\n");
	tasklet_init(&tasklet,irq_tasklet_action,data);    //初始化一个struct tasklet_struct 变量     
	tasklet_schedule(&tasklet);                  //把软件中断放入后台线程
	printk("<0>the count value of the tasklet before tasklet_disable is:%d\n",tasklet.count);
	tasklet_disable(&tasklet);                   //调用tasklet_disable()使tasklet对应的处理函数不能执行
	if(atomic_read(&(tasklet.count)) != 0)     //测试当前的count的值
		printk("<0>tasklet is disabled.\n");
	printk("<0>the count value of the tasklet after tasklet_disable is:%d\n",tasklet.count);
	tasklet_hi_enable(&tasklet);                   //调用函数tasklet_enable()使能tasklet
	if(atomic_read(&(tasklet.count))==0)
		printk("<0>tasklet is enabled\n");
	printk("<0>the count value of the tasklet after tasklet_hi_enable is:%d\n",tasklet.count);
	tasklet_kill(&tasklet);                  //等待tasklet被调度
	printk("<0>out tasklet_hi_enable_init\n");
	return 0; 
}

static void __exit tasklet_hi_enable_exit(void)
{ 
	printk("<0>Goodbye tasklet_hi_enable\n");   	            
 	return;
}
module_init(tasklet_hi_enable_init);
module_exit(tasklet_hi_enable_exit);
