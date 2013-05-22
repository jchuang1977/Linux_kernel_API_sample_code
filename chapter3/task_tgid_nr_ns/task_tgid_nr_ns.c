/********************************************************************************
* File Name:	task_tgid_nr_ns.c
* Description:	第3章实例训练          
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
	printk("<0>the current pid is :%d\n",current->pid);ÏÔÊŸµ±Ç°œø³ÌµÄPID	
	return 0;
}

//Ä£¿éŒÓÔØº¯Êý¶šÒå
static int __init task_tgid_nr_ns_init(void)
{	
	int result;	
	printk("<0>into task_tgid_nr_ns_init.\n");		
	result=kernel_thread(my_function,NULL,CLONE_KERNEL); //ŽŽœšÐÂœø³Ì
	struct pid * kpid=find_get_pid(result); //»ñÈ¡œø³ÌµÄœø³ÌÃèÊö·ûÐÅÏ¢
	struct task_struct * task=pid_task(kpid,PIDTYPE_PID); //»ñÈ¡œø³ÌËùÔÚÈÎÎñµÄÈÎÎñÃèÊö·ûÐÅÏ¢
	pid_t result1=task_tgid_nr_ns(task,kpid->numbers[kpid->level].ns); //»ñÈ¡œø³ÌºÅ
	printk("<0>the pid of the find_get_pid is :%d\n",kpid->numbers[kpid->level].nr); //ÏÔÊŸœø³ÌµÄœø³ÌºÅ
	printk("<0>the result of the task_tgid_nr_ns is:%d\n",result1); //ÏÔÊŸº¯Êýtask_tgid_nr_ns()µÄ·µ»ØÖµ
	printk("<0>the result of the kernel_thread is :%d\n",result); //ÏÔÊŸº¯Êýkernel_thread()µÄ·µ»ØÖµ
	printk("<0>the pid of current thread is :%d\n",current->pid); //ÏÔÊŸµ±Ç°œø³ÌµÄœø³ÌºÅ
	printk("<0>out task_tgid_nr_ns_init.\n");
	return 0;
}

//Ä£¿éÐ¶ÔØº¯Êý¶šÒå
static void __exit task_tgid_nr_ns_exit(void)
{
        printk("<0>Goodbye task_tgid_nr_ns\n");	
}

module_init(task_tgid_nr_ns_init);
module_exit(task_tgid_nr_ns_exit);


