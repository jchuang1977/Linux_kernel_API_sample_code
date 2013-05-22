/********************************************************************************
* File Name:	current_thread_info.c
* Description:	第4章实例训练          
* Reference book:《Linux内核API完全参考手册》邱铁，周玉，邓莹莹 ，机械工业出版社.2010.9  
* E_mail:openlinux2100@gmail.com			                
*
********************************************************************************/
#include <linux/module.h>
#include <linux/sched.h>
#include <linux/pid.h>
#include <asm/thread_info.h>
MODULE_LICENSE("GPL");

//Ä£¿éŒÓÔØº¯Êý¶šÒå
static int __init current_thread_info_init(void)
{	
	printk("<0>into current_thread_info_init.\n");						
	printk("<0>the current pid is:%d\n",current->pid); //ÏÔÊŸµ±Ç°œø³ÌµÄœø³ÌºÅ
	struct thread_info * info=current_thread_info(); //»ñÈ¡µ±Ç°œø³ÌµÄ»ù±ŸÐÅÏ¢
	struct task_struct * task=info->task;  //»ñÈ¡µ±Ç°œø³ÌµÄÃèÊö·ûÐÅÏ¢
	printk("<0>the pid of the thread is:%d\n",task->pid);  //ÏÔÊŸœø³ÌµÄPID
	printk("<0>the tgid of the thread is:%d\n",task->tgid); //ÏÔÊŸœø³ÌµÄTGID
	printk("<0>the low level flags is:%u\n",info->flags); //ÏÔÊŸœø³ÌµÄ×Ö¶ÎflagsÖµ
	printk("<0>the thread synchronous flags is:%u\n",info->status); //ÏÔÊŸœø³ÌµÄ×ŽÌ¬
	printk("<0>current CPU is:%u\n",info->cpu); //ÏÔÊŸœø³ÌËùÔÚCPU±àºÅ
	printk("<0>the preempt_count is:%d\n",info->preempt_count); //ÏÔÊŸœø³ÌµÄÇÀÕŒŒÆÊýÆ÷Öµ
	printk("<0>out current_thread_info_init.\n");
	return 0;
}

//Ä£¿éÐ¶ÔØº¯Êý¶šÒå
static void __exit current_thread_info_exit(void)
{	
        printk("<0>Goodbye current_thread_info\n");	
}

module_init(current_thread_info_init);
module_exit(current_thread_info_exit);


