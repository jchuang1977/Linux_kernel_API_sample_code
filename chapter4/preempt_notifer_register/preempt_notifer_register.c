/********************************************************************************
* File Name:	preempt_notifer_register.c
* Description:	第4章实例训练          
* Reference book:《Linux内核API完全参考手册》邱铁，周玉，邓莹莹 ，机械工业出版社.2010.9  
* E_mail:openlinux2100@gmail.com			                
*
********************************************************************************/
#include <linux/module.h>
#include <linux/sched.h>
#include <linux/pid.h>
#include <linux/preempt.h>
#include <linux/list.h>
MODULE_LICENSE("GPL");

/*Ÿ²Ì¬È«ŸÖ±äÁ¿¶šÒå*/
static struct preempt_notifier notifier;  //ÇÀÕŒÍšÖª±äÁ¿¶šÒå
static struct preempt_ops ops; //ÇÀÕŒ²Ù×÷±äÁ¿¶šÒå

//ÇÀÕŒœø³ÌÖØµ÷¶Èº¯Êý¶šÒå
void sched_in(struct preempt_notifier * notifier,int cpu)
{
	printk("<0>into the sched_in function\n");
	printk("<0>the value of the parameter cpu is:%d\n",cpu); //ÏÔÊŸ²ÎÊýCPUµÄÖµ
	printk("<0>the current pid is:%d\n",current->pid); //ÏÔÊŸµ±Ç°œø³ÌµÄPIDÖµ
	printk("<0>out the sched_in function\n");
}

//œø³Ì±»ÇÀÕŒÈÃ¶ÉCPUº¯Êý¶šÒå
void sched_out(struct preempt_notifier *notifier,struct task_struct * next)
{
	printk("<0>into the sched_out function\n");
	printk("<0>the pid of the next task is:%d\n",next->pid);  //ÏÔÊŸÏÂÒ»žöœø³ÌµÄPIDÖµ
	printk("<0>the current pid is:%d\n",current->pid); //ÏÔÊŸµ±Ç°œø³ÌµÄPIDÖµ
	printk("<0>out the sched_out function\n");
}

//×Óœø³ÌŽŠÀíº¯Êý¶šÒå
int my_function(void * argc)
{
	printk("<0>in the kernel thread function!\n");	
	printk("<0>the current pid is:%d\n",current->pid); //ÏÔÊŸµ±Ç°œø³ÌµÄPIDÖµ
	printk("<0>out the kernel thread function\n");
	return 0;
}

//Ä£¿éŒÓÔØº¯Êý¶šÒå
static int __init preempt_notifer_register_init(void)
{	
	int result;
	printk("<0>into preempt_notifer_register_init.\n");				
	result=kernel_thread(my_function,NULL,CLONE_KERNEL); //ŽŽœšÐÂœø³Ì
	ops.sched_in=sched_in; //œø³ÌÇÀÕŒ²Ù×÷º¯Êý³õÊŒ»¯
       ops.sched_out=sched_out; 
	preempt_notifier_init(&notifier,&ops);	//œø³ÌÇÀÕŒÍšÖª±äÁ¿³õÊŒ»¯
	preempt_notifier_register(&notifier);   //œø³ÌÇÀÕŒÍšÖª±äÁ¿×¢²á
	printk("<0>the result of the kernel_thread is :%d\n",result); //ÏÔÊŸº¯Êýkernel_thread()·µ»Øœá¹û
	printk("<0>the current pid is:%d\n",current->pid); //ÏÔÊŸµ±Ç°œø³ÌPIDÖµ
	printk("<0>out preempt_notifer_register_init.\n");
	return 0;
}

//Ä£¿éÐ¶ÔØº¯Êý¶šÒå
static void __exit preempt_notifer_register_exit(void)
{	
        printk("<0>Goodbye preempt_notifer_register\n");	
}

module_init(preempt_notifer_register_init);
module_exit(preempt_notifer_register_exit);


