/********************************************************************************
* File Name:	__task_pid_nr_ns.c
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
	return 0;
}

//Ä£¿éŒÓÔØº¯Êý¶šÒå
static int __init __task_pid_nr_ns_init(void)
{	
	int result;	
	printk("<0> into __task_pid_nr_ns_init.\n");		
	result=kernel_thread(my_function,NULL,CLONE_KERNEL);  //ŽŽœšÐÂœø³Ì
	struct pid * kpid=find_get_pid(result);  //»ñÈ¡×Óœø³ÌµÄœø³ÌÃèÊö·û
	struct task_struct * task=pid_task(kpid,PIDTYPE_PID); //»ñÈ¡œø³ÌËùÊôµÄÈÎÎñµÄÈÎÎñÃèÊö·û
	pid_t result1=__task_pid_nr_ns(task,PIDTYPE_PID,kpid->numbers[kpid->level].ns); //»ñÈ¡ÈÎÎñ¶ÔÓŠœø³ÌµÄœø³ÌÃèÊö·û
	printk("<0>the pid of the find_get_pid is :%d\n",kpid->numbers[kpid->level].nr); //ÏÔÊŸº¯Êýfind_get_pid()·µ»ØÖµµÄœø³ÌÃèÊö·ûµÄœø³ÌºÅ
	printk("<0>the result of the __task_pid_nr_ns is:%d\n",result1); //ÏÔÊŸº¯Êý__task_pid_nr_ns()µÄ·µ»ØÖµ
	printk("<0>the result of the kernel_thread is :%d\n",result);  //ÏÔÊŸº¯Êýkernel_thread()µÄ·µ»ØÖµ
	printk("<0>the pid of current thread is :%d\n",current->pid);  //ÏÔÊŸµ±Ç°œø³ÌºÅ
	printk("<0> out __task_pid_nr_ns_init.\n");
	return 0;
}

//Ä£¿éÍË³öº¯Êý¶šÒå
static void __exit __task_pid_nr_ns_exit(void)
{
        printk("<0>Goodbye __task_pid_nr_ns\n");	
}

module_init(__task_pid_nr_ns_init);
module_exit(__task_pid_nr_ns_exit);


