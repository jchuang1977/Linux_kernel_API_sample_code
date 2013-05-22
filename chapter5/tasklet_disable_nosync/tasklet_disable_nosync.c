/********************************************************************************
* File Name:	tasklet_disable_nosync.c
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

static int __init tasklet_disable_nosync_init(void) 
{
  	printk("<0>into tasklet_disable_nosync_init\n");
	tasklet_init(&tasklet,irq_tasklet_action,data);    //初始化一个struct tasklet_struct 变量     
	tasklet_schedule(&tasklet);                  //把软件中断放入后台线程
        //tasklet_disable(&tasklet)被替换成下面的两行代码功能将相同
	printk("<0>the value of the tasklet before tasklet_disable_nosync is :%d\n",tasklet.count);
	tasklet_disable_nosync(&tasklet);
	//tasklet_unlock_wait(&tasklet);
	if(atomic_read(&(tasklet.count)) != 0)     //测试当前的count的值
		printk("<0>tasklet is disabled.\n");
	printk("<0>the value of the tasklet after tasklet_disable_nosync is :%d\n",tasklet.count);
	tasklet_enable(&tasklet);                   //调用函数tasklet_enable()使能tasklet
	if(atomic_read(&(tasklet.count))==0)      //测试当前的count的值
		printk("<0>tasklet is enabled.\n");
	printk("<0>the value of the tasklet after tasklet_enable is :%d\n",tasklet.count);
	tasklet_kill(&tasklet);                   //释放申请的tasklet变量
	printk("<0>out tasklet_disable_nosync_init\n");
	return 0; 
}

static void __exit tasklet_disable_nosync_exit(void)
{ 
	printk("<0>Goodbye tasklet_disable_nosync\n");
 	return;
}

module_init(tasklet_disable_nosync_init);
module_exit(tasklet_disable_nosync_exit);
