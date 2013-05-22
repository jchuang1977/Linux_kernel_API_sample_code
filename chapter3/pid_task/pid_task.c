/********************************************************************************
* File Name:	pid_task.c
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

//Ä£¿é³õÊŒ»¯º¯Êýº¯Êý¶šÒå
static int __init pid_task_init(void)
{	
	int result;
	printk("<0> into pid_task_init.\n");		
	result=kernel_thread(my_function,NULL,CLONE_KERNEL); //ŽŽœšÐÂœø³Ì
	struct pid * kpid=find_get_pid(result);		 //»ñÈ¡ÐÂœø³ÌµÄÃèÊö·ûÐÅÏ¢
        struct task_struct * task=pid_task(kpid,PIDTYPE_PID); //»ñÈ¡œø³ÌµÄÈÎÎñÃèÊö·ûÐÅÏ¢
        printk("<0>the state of the task is:%d\n",task->state);  //ÏÔÊŸÈÎÎñµ±Ç°ËùŽŠµÄ×ŽÌ¬
	printk("<0>the pid of the task is:%d\n",task->pid);  //ÏÔÊŸÈÎÎñµÄœø³ÌºÅ
	printk("<0>the tgid of the task is:%d\n",task->tgid);  //ÏÔÊŸÈÎÎñµÄÏß³Ì×éºÅ
	printk("<0>the kernel_thread result is:%d\n",result);  //ÏÔÊŸº¯Êýkernel_thread()º¯ÊýÖŽÐÐœá¹û
	printk("<0> out pid_task_init.\n");
	return 0;
}

//Ä£¿éÐ¶ÔØº¯Êý¶šÒå
static void __exit pid_task_exit(void)
{
        printk("<0>Goodbye  pid_task\n");
}

module_init(pid_task_init);
module_exit(pid_task_exit);


