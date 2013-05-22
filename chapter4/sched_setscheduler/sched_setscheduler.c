/********************************************************************************
* File Name:	sched_setscheduler.c
* Description:	第4章实例训练          
* Reference book:《Linux内核API完全参考手册》邱铁，周玉，邓莹莹 ，机械工业出版社.2010.9  
* E_mail:openlinux2100@gmail.com			                
*
********************************************************************************/
/*Í·ÎÄŒþÒýÓÃ*/
#include <linux/module.h>
#include <linux/sched.h>
#include <linux/pid.h>
MODULE_LICENSE("GPL");

/*×Óœø³ÌŽŠÀíº¯Êý¶šÒå*/
int my_function(void * argc)
{
	printk("<0>in the kernel thread function!\n");
	printk("<0>the policy of current thread is:%d\n",current->policy); //ÏÔÊŸµ±Ç°œø³ÌµÄpolicyÖµ
	printk("<0>the rt_priority of current thread is:%d\n",current->rt_priority); //ÏÔÊŸµ±Ç°œø³ÌµÄrt_priorityÖµ
	printk("<0>the current pid is:%d\n",current->pid);  //ÏÔÊŸµ±Ç°œø³ÌµÄPIDÖµ
	printk("<0>out the kernel thread function\n");
	return 0;
}

/*Ä£¿éŒÓÔØº¯Êý¶šÒå*/
static int __init sched_setscheduler_init(void)
{	
	/*ŸÖ²¿±äÁ¿¶šÒå*/
	int result,result1;
	struct pid * kpid;
	struct task_struct * task;
	struct sched_param param;
	printk("<0>into sched_setscheduler_init.\n");			
	result=kernel_thread(my_function,NULL,CLONE_KERNEL);	 //ŽŽœšÐÂœø³Ì
	kpid=find_get_pid(result); //»ñÈ¡ÐÂœø³ÌµÄœø³ÌÃèÊö·ûÖžÕë
	task=pid_task(kpid,PIDTYPE_PID); //»ñÈ¡ÈÎÎñµÄÈÎÎñÃèÊö·ûÖžÕë
	param.sched_priority=100;   //ÉèÖÃ×Ö¶Îsched_priorityµÄÖµ
	printk("<0>the policy of the child thread is:%d\n",task->policy); //ÏÔÊŸÐÂœø³ÌµÄpolicyµÄÖµ
	printk("<0>the rt_priority of the child thread is:%d\n",task->rt_priority); //ÏÔÊŸÐÂœø³ÌµÄrt_priorityµÄÖµ
	result1=sched_setscheduler(task,1,&param);    //µ÷ÓÃº¯ÊýžÄ±äœø³ÌµÄµ÷¶È²ßÂÔ
	printk("<0>the new policy of the child thread is:%d\n",task->policy); //ÏÔÊŸº¯Êýµ÷ÓÃÖ®ºóÐÂœø³ÌµÄpolicyµÄÖµ
	printk("<0>the new rt_priority of the child thread is:%d\n",task->rt_priority);  //ÏÔÊŸº¯Êýµ÷ÓÃÖ®ºóÐÂœø³ÌµÄrt_priorityµÄÖµ
	printk("<0>the result of the kernel_thread is :%d\n",result);  //ÏÔÊŸº¯Êýkernel_thread( )µÄ·µ»Øœá¹û
	printk("<0>the result of the sched_setscheduler is:%d\n",result1);  //ÏÔÊŸº¯Êýsched_setscheduler( )µÄ·µ»Øœá¹û
	printk("<0>the current pid is:%d\n",current->pid); //ÏÔÊŸµ±Ç°œø³ÌµÄPIDÖµ
	printk("<0>out sched_setscheduler_init.\n");
	return 0;
}

/*Ä£¿éÐ¶ÔØº¯Êý¶šÒå*/
static void __exit sched_setscheduler_exit(void)
{	
        printk("<0>Goodbye sched_setscheduler\n");	
}

/*Ä£¿éŒÓÔØŒ°Ð¶ÔØº¯Êýµ÷ÓÃ*/
module_init(sched_setscheduler_init);
module_exit(sched_setscheduler_exit);


