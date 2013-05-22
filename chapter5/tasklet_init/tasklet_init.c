/********************************************************************************
* File Name:	tasklet_init.c
* Description:	第5章实例训练          
* Reference book:《Linux内核API完全参考手册》邱铁，周玉，邓莹莹 ，机械工业出版社.2010.9  
* E_mail:openlinux2100@gmail.com			                
*
********************************************************************************/

#include <linux/interrupt.h> 
#include <linux/module.h> 
#include <linux/init.h> 
MODULE_LICENSE("GPL");
static unsigned long data=10; 
static struct tasklet_struct tasklet; 

//自定义软中断处理函数，在此只有显示功能
static void irq_tasklet_action(unsigned long data) 
{ 
	printk("<0>The state of the tasklet is :%ld\n",(&tasklet)->state); 
  	printk("<0>tasklet running. by author\n"); 
   	return; 
} 

static int  __init tasklet_init_init(void) 
{ 
  	printk("<0>into tasklet_init_init\n"); 
	printk("<0>the data value of the tasklet is :%ld\n",tasklet.data);
	if(tasklet.func==NULL)
	{
		printk("<0>the tasklet has not been initialized\n");
	}
	tasklet_init(&tasklet,irq_tasklet_action,data); //初始化一个struct tasklet_struct 变量，即申请一个软中断变量
	printk("<0>the data value of the tasklet is :%ld\n",tasklet.data);
	if(tasklet.func==NULL)
	{
		printk("<0>the tasklet has not been initialized\n");
	}
	else
	{
		printk("<0>the tasklet has been initialized\n");
	}
	printk("<0>out tasklet_init_init\n"); 
	return 0; 
} 

static void  __exit tasklet_init_exit(void) 
{ 
	printk("<0>Goodbye tasklet_init\n"); 
 	return; 
} 

module_init(tasklet_init_init); 
module_exit(tasklet_init_exit);

