/********************************************************************************
* File Name:	get_task_mm.c
* Description:	第3章实例训练          
* Reference book:《Linux内核API完全参考手册》邱铁，周玉，邓莹莹 ，机械工业出版社.2010.9  
* E_mail:openlinux2100@gmail.com			                
*
********************************************************************************/
#include <linux/module.h>
#include <linux/sched.h>
#include <linux/pid.h>
#include <linux/mm_types.h>
MODULE_LICENSE("GPL");

//×Óœø³Ìº¯Êý¶šÒå
int my_function(void * argc)
{
	printk("<0>in the kernel thread function!\n");	
	printk("<0>the current PID is :%d\n",current->pid);  //ÏÔÊŸµ±Ç°œø³ÌµÄPID
	return 0;
}

//Ä£¿éŒÓÔØº¯Êý¶šÒå
static int __init get_task_mm_init(void)
{	
	int result;
	printk("<0>into get_task_mm_init.\n");		
	result=kernel_thread(my_function,NULL,CLONE_KERNEL); //ŽŽœšÐÂœø³Ì
	struct pid * kpid=find_get_pid(result);		 //»ñÈ¡ÐÂœø³ÌµÄÃèÊö·ûÐÅÏ¢
	struct task_struct * task=pid_task(kpid,PIDTYPE_PID); //»ñÈ¡œø³ÌµÄÈÎÎñÃèÊö·ûÐÅÏ¢
	struct mm_struct * mm_task=get_task_mm(task);	//»ñÈ¡ÈÎÎñµÄÄÚŽæÃèÊö·û
	printk("<0>the mm_users of the mm_struct is:%d\n",mm_task->mm_users); //ÏÔÊŸ×Ö¶Îmm_usersµÄÖµ
	printk("<0>the mm_count of the mm_struct is:%d\n",mm_task->mm_count); //ÏÔÊŸ×Ö¶Îmm_countµÄÖµ
	printk("<0>the tgid of the mm_strcut is:%d\n",mm_task->owner->tgid); //ÏÔÊŸŽËœø³ÌµÄžžœø³ÌµÄTGIDºÅ
	printk("<0>the pid of the mm_struct is:%d\n",mm_task->owner->pid); //ÏÔÊŸŽËœø³ÌµÄžžœø³ÌµÄPIDºÅ
	printk("<0>the current PID is:%d\n",current->pid); //ÏÔÊŸµ±Ç°œø³ÌµÄPIDºÅ
	printk("<0>the kernel_thread result is:%d\n",result); //ÏÔÊŸº¯Êýkernel_thread()µÄ·µ»Øœá¹û
	printk("<0>out get_task_mm_init.\n");
	return 0;
}

//Ä£¿éÐ¶ÔØº¯Êý¶šÒå
static void __exit get_task_mm_exit(void)
{
        printk("<0>Goodbye get_task_mm\n");
}

module_init(get_task_mm_init);
module_exit(get_task_mm_exit);


