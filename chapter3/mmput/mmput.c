/********************************************************************************
* File Name:	mmput.c
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
	printk("<0>the current PID is :%d\n",current->pid); //ÏÔÊŸµ±Ç°œø³ÌµÄPID
	return 0;
}

//Ä£¿éŒÓÔØº¯Êý¶šÒå
static int __init mmput_init(void)
{	
	int result;
	printk("<0>into mmput_init.\n");		
	result=kernel_thread(my_function,NULL,CLONE_KERNEL); //ŽŽœšÐÂœø³Ì
	struct pid * kpid=find_get_pid(result);		 //»ñÈ¡ÐÂœø³ÌµÄÃèÊö·ûÐÅÏ¢
	struct task_struct * task=pid_task(kpid,PIDTYPE_PID); //»ñÈ¡ÐÂœø³ÌµÄÈÎÎñÃèÊö·ûÐÅÏ¢
	struct mm_struct * mm_task=get_task_mm(task);	 //»ñÈ¡œø³Ì¶ÔÓŠÈÎÎñµÄÄÚŽæÐÅÏ¢

       /*ÏÔÊŸ×Ö¶Îmm_usersºÍ×Ö¶Îmm_countµÄÖµ*/
	printk("<0>the mm_users of the mm_struct is:%d\n",mm_task->mm_users);
	printk("<0>the mm_count of the mm_struct is:%d\n",mm_task->mm_count);

       /*ÏÔÊŸÓëŽËmm_structÏà¹Øœø³ÌµÄžžœø³ÌµÄTGIDºÍPID*/
	printk("<0>the tgid of the mm_strcut is:%d\n",mm_task->owner->tgid);
	printk("<0>the pid of the mm_struct is:%d\n",mm_task->owner->pid);
	mmput(mm_task);     //µ÷ÓÃº¯Êýmmput()ÊÍ·Åœø³ÌµÄÄÚŽæ¿ÕŒä
	printk("the new value of the mm_struct after the function mmput:\n");
    
       /*ÏÔÊŸº¯Êýmmput()µ÷ÓÃÖ®ºóµÄœø³Ì¶ÔÓŠÄÚŽæ¿ÕŒä²¿·Ö×Ö¶ÎµÄÖµ*/
	printk("<0>the mm_users of the mm_struct is:%d\n",mm_task->mm_users);
	printk("<0>the mm_count of the mm_struct is:%d\n",mm_task->mm_count);
	printk("<0>the tgid of the mm_strcut is:%d\n",mm_task->owner->tgid);
	printk("<0>the pid of the mm_struct is:%d\n",mm_task->owner->pid);
	printk("<0>the current PID is:%d\n",current->pid); //ÏÔÊŸµ±Ç°œø³ÌµÄPIDÖµ
	printk("<0>the kernel_thread result is:%d\n",result); //ÏÔÊŸº¯Êýkernel_thread()µÄ·µ»ØÖµ
	printk("<0>out mmput_init.\n");
	return 0;
}

//Ä£¿éÐ¶ÔØº¯Êý¶šÒå
static void __exit mmput_exit(void)
{
        printk("<0>Goodbye mmput\n");
}

module_init(mmput_init);
module_exit(mmput_exit);


