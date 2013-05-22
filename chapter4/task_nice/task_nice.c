/********************************************************************************
* File Name:	task_nice.c
* Description:	第4章实例训练          
* Reference book:《Linux内核API完全参考手册》邱铁，周玉，邓莹莹 ，机械工业出版社.2010.9  
* E_mail:openlinux2100@gmail.com			                
*
********************************************************************************/
#include <linux/module.h>
#include <linux/sched.h>
#include <linux/pid.h>
MODULE_LICENSE("GPL");

//×Óœø³Ìº¯Êý¶šÒå
int my_function(void * argc)
{
	printk("<0>in the kernel thread function!\n");
	printk("<0>the current static_prio is:%d\n",current->static_prio); //ÏÔÊŸµ±Ç°œø³ÌµÄŸ²Ì¬ÓÅÏÈŒ¶
	printk("<0>the current nice is:%d\n",task_nice(current)); //ÏÔÊŸµ±Ç°œø³ÌµÄniceÖµ	 
	printk("<0>the current pid is:%d\n",current->pid); //ÏÔÊŸµ±Ç°œø³ÌµÄPIDÖµ
	printk("<0>out the kernel thread function\n");
	return 0;
}

//Ä£¿éŒÓÔØº¯Êý¶šÒå
static int __init task_nice_init(void)
{	
	int result,priority;
	struct pid * kpid;
	struct task_struct * task;
	printk("<0>into task_nice_init.\n");				
	result=kernel_thread(my_function,NULL,CLONE_KERNEL); //ŽŽœšÐÂœø³Ì
	kpid=find_get_pid(result);  //»ñÈ¡ÐÂœø³ÌµÄÃèÊö·ûÐÅÏ¢
	task=pid_task(kpid,PIDTYPE_PID); //»ñÈ¡ÐÂœø³ÌµÄÈÎÎñÃèÊöÐÅÏ¢
	priority=task_nice(task);  //»ñÈ¡ÐÂœø³ÌµÄniceÖµ
	printk("<0>the static_prio of the child thread is:%d\n",task->static_prio); //ÏÔÊŸÐÂœø³ÌµÄŸ²Ì¬ÓÅÏÈŒ¶
	printk("<0>the nice of the child thread is:%d\n",priority); //ÏÔÊŸÐÂœø³ÌµÄniceÖµ
	printk("<0>the result of the kernel_thread is :%d\n",result); //ÏÔÊŸº¯Êýkernel_thread()µÄ·µ»Øœá¹û
	printk("<0>the current static_prio is:%d\n",current->static_prio); //ÏÔÊŸµ±Ç°œø³ÌµÄŸ²Ì¬ÓÅÏÈŒ¶
	printk("<0>the current pid is:%d\n",current->pid); //ÏÔÊŸµ±Ç°œø³ÌµÄPIDÖµ
	printk("<0>the current nice is:%d\n",task_nice(current)); //ÏÔÊŸµ±Ç°œø³ÌµÄniceÖµ
	printk("<0>out task_nice_init.\n");
	return 0;
}

//Ä£¿éÐ¶ÔØº¯Êý¶šÒå
static void __exit task_nice_exit(void)
{	
        printk("<0>Goodbye task_nice\n");	
}

module_init(task_nice_init);
module_exit(task_nice_exit);


