/********************************************************************************
* File Name:	task_active_pid_ns.c
* Description:	第3章实例训练          
* Reference book:《Linux内核API完全参考手册》邱铁，周玉，邓莹莹 ，机械工业出版社.2010.9  
* E_mail:openlinux2100@gmail.com			                
*
********************************************************************************/
#include <linux/module.h>
#include <linux/sched.h>
#include <linux/pid.h>
#include <linux/pid_namespace.h>
MODULE_LICENSE("GPL");

//×Óœø³Ìº¯Êý¶šÒå
int my_function(void * argc)
{
	printk("<0>in the kernel thread function!\n");
	printk("<0>the current pid is :%d\n",current->pid); //ÏÔÊŸµ±Ç°œø³ÌµÄPID	
	return 0;
}

//Ä£¿é³õÊŒ»¯º¯Êý¶šÒå
static int __init task_active_pid_ns_init(void)
{	
	int result;	
	printk("<0>into task_active_pid_ns_init.\n");		
	result=kernel_thread(my_function,NULL,CLONE_KERNEL); //ŽŽœšÐÂœø³Ì
	struct pid * kpid=find_get_pid(result);  //»ñÈ¡œø³ÌÃèÊö·û
	struct task_struct * task=pid_task(kpid,PIDTYPE_PID); //»ñÈ¡ÈÎÎñÃèÊö·û
	struct pid_namespace * ns=task_active_pid_ns(task);  //»ñÈ¡ÈÎÎñÖÐœø³ÌµÄÃüÃû¿ÕŒä
	printk("<0>the pid of the find_get_pid result is :%d\n",kpid->numbers[kpid->level].nr);//ÏÔÊŸœø³ÌµÄPID
	printk("<0>the last_pid of the task_active_pid_ns result is:%d\n",ns->last_pid); //ÏÔÊŸÃüÃû¿ÕŒä×Ö¶Îlast_pidµÄÖµ
	printk("<0>the result of the kernel_thread is :%d\n",result); //ÏÔÊŸº¯Êýkernel_thread()º¯Êýµ÷ÓÃœá¹û
	printk("<0>the pid of current thread is :%d\n",current->pid); //ÏÔÊŸµ±Ç°œø³ÌµÄPID
	printk("<0>out task_active_pid_ns_init.\n");
	return 0;
}

//Ä£¿éÐ¶ÔØº¯Êý¶šÒå
static void __exit task_active_pid_ns_exit(void)
{
        printk("<0>Goodbye task_active_pid_ns\n");	
}

module_init(task_active_pid_ns_init);
module_exit(task_active_pid_ns_exit);


