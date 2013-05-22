/********************************************************************************
* File Name:	set_user_nice.c
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
	printk("<0>the current static_prio is:%d\n",current->static_prio);  //ÏÔÊŸµ±Ç°œø³ÌµÄŸ²Ì¬ÓÅÏÈŒ¶
	printk("<0>the current nice is:%d\n",task_nice(current));	 //»ñÈ¡µ±Ç°œø³ÌµÄniceÖµ
	printk("<0>the current pid is:%d\n",current->pid);         //ÏÔÊŸµ±Ç°œø³ÌµÄPIDÖµ
	printk("<0>out the kernel thread function\n");
	return 0;
}

//Ä£¿éŒÓÔØº¯Êý¶šÒå
static int __init set_user_nice_init(void)
{	
	int result;
	struct pid * kpid;
	struct task_struct * task;
	printk("<0>into set_user_nice_init.\n");			
	result=kernel_thread(my_function,NULL,CLONE_KERNEL);	 //ŽŽœšÐÂœø³Ì
	kpid=find_get_pid(result);  //»ñÈ¡ÐÂœø³ÌµÄÃèÊö·ûÐÅÏ¢
	task=pid_task(kpid,PIDTYPE_PID);  //»ñÈ¡ÐÂœø³ÌµÄÈÎÎñÃèÊö·ûÐÅÏ¢
	printk("<0>the static_prio of the child thread is:%d\n",task->static_prio); //ÏÔÊŸÐÂœø³ÌµÄŸ²Ì¬ÓÅÏÈŒ¶
	printk("<0>the nice of the child thread is:%d\n",task_nice(task)); //»ñÈ¡ÐÂœø³ÌµÄniceÖµ
	printk("<0>the prio of the child thread is:%d\n",task->prio); //ÏÔÊŸÐÂœø³ÌµÄ¶¯Ì¬ÓÅÏÈŒ¶
	set_user_nice(task,-20); //ÉèÖÃÐÂœø³ÌµÄniceÖµ
	//set_user_nice(task,19);
	//set_user_nice(task,-21);
	//set_user_nice(task,20);
	printk("<0>the new value static_prio of the child thread is:%d\n",task->static_prio); //ÏÔÊŸÐÂœø³ÌµÄŸ²Ì¬ÓÅÏÈŒ¶
	printk("<0>the new value nice of the child thread is:%d\n",task_nice(task)); //ÏÔÊŸÐÂœø³ÌµÄniceÖµ
	printk("<0>the result of the kernel_thread is :%d\n",result); //ÏÔÊŸkernel_thread()º¯ÊýµÄ·µ»Øœá¹û
	printk("<0>the current pid is:%d\n",current->pid);   //ÏÔÊŸµ±Ç°œø³ÌµÄPIDÖµ
	printk("<0>out set_user_nice_init.\n");
	return 0;
}

//Ä£¿éÐ¶ÔØº¯Êý¶šÒå
static void __exit set_user_nice_exit(void)
{	
        printk("<0>Goodbye set_user_nice\n");	
}

module_init(set_user_nice_init);
module_exit(set_user_nice_exit);


