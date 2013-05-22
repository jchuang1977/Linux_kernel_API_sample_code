/********************************************************************************
* File Name:	preempt_notifer_unregister.c
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

//È«ŸÖ±äÁ¿¶šÒå
static struct preempt_notifier notifier; //œø³ÌÇÀÕŒÍšÖªÆ÷¶šÒå
static struct preempt_ops ops;      //œø³ÌÇÀÕŒ²Ù×÷±äÁ¿¶šÒå

//œø³ÌÇÀÕŒÍšÖªÆ÷ÖØµ÷¶Èº¯Êý¶šÒå
void sched_in(struct preempt_notifier * notifier,int cpu)
{
	printk("<0>into the sched_in function\n");
	printk("<0>the value of the parameter cpu is:%d\n",cpu); //ÏÔÊŸ²ÎÊýCPUµÄÖµ
	printk("<0>the current pid is:%d\n",current->pid); //ÏÔÊŸµ±Ç°œø³ÌPIDµÄÖµ
	printk("<0>out the sched_in function\n");
}

//œø³ÌÇÀÕŒÍšÖªÆ÷ÈÃÇÀÕŒº¯Êý¶šÒå
void sched_out(struct preempt_notifier *notifier,struct task_struct * next)
{
	printk("<0>into the sched_out function\n");
	printk("<0>the pid of the next task is:%d\n",next->pid); //ÏÔÊŸÏÂÒ»žöœø³ÌµÄPIDÖµ
	printk("<0>the current pid is:%d\n",current->pid); //µ±Ç°œø³ÌµÄPIDÖµ
	printk("<0>out the sched_out function\n");
}

//×Óœø³Ìº¯Êý¶šÒå
int my_function(void * argc)
{
	printk("<0>in the kernel thread function!\n");	
	printk("<0>the current pid is:%d\n",current->pid); //ÏÔÊŸµ±Ç°œø³ÌµÄPIDµÄÖµ
	//preempt_notifier_unregister(&notifier);   //ÊŸÀý2£¬ ×¢Ïúœø³ÌÇÀÕŒÍšÖªÆ÷
	printk("<0>out the kernel thread function\n");
	return 0;
}

//Ä£¿éŒÓÔØº¯Êý¶šÒå
static int __init preempt_notifer_unregister_init(void)
{	
	int result;
	printk("<0>into preempt_notifer_unregister_init.\n");				
	result=kernel_thread(my_function,NULL,CLONE_KERNEL); //ŽŽœšÐÂœø³Ì
	ops.sched_in=sched_in; //³õÊŒ»¯œø³ÌÇÀÕŒ²Ù×÷±äÁ¿
       ops.sched_out=sched_out;
	preempt_notifier_init(&notifier,&ops);  //³õÊŒ»¯œø³ÌÇÀÕŒÍšÖªÆ÷
	preempt_notifier_register(&notifier); //×¢²áœø³ÌÇÀÕŒÍšÖªÆ÷
	preempt_notifier_unregister(&notifier); //ÊŸÀý1£¬×¢Ïúœø³ÌÇÀÕŒÍšÖªÆ÷
	printk("<0>the result of the kernel_thread is :%d\n",result); //ÏÔÊŸº¯Êýkernel_thread()º¯ÊýµÄ·µ»Øœá¹û
	printk("<0>the current pid is:%d\n",current->pid); //ÏÔÊŸµ±Ç°œø³ÌPIDÖµ
	printk("<0>out preempt_notifer_unregister_init.\n");
	return 0;
}

//Ä£¿éÐ¶ÔØº¯Êý¶šÒå
static void __exit preempt_notifer_unregister_exit(void)
{	
        printk("<0>Goodbye preempt_notifer_unregister\n");	
}

module_init(preempt_notifer_unregister_init);
module_exit(preempt_notifer_unregister_exit);


