/********************************************************************************
* File Name:	wait_for_completion.c
* Description:	第4章实例训练          
* Reference book:《Linux内核API完全参考手册》邱铁，周玉，邓莹莹 ，机械工业出版社.2010.9  
* E_mail:openlinux2100@gmail.com			                
*
********************************************************************************/
/*Í·ÎÄŒþÒýÓÃ*/
#include <linux/module.h>
#include <linux/sched.h>
#include <linux/pid.h>
#include <linux/completion.h>
#include <linux/wait.h>
#include <linux/list.h>
MODULE_LICENSE("GPL");

/*È«ŸÖ±äÁ¿¶šÒå*/
static struct completion comple;   //ÓÃÓÚ±£ŽæcompletionµÄ×ŽÌ¬

/*×Óœø³ÌŽŠÀíº¯Êý¶šÒå*/
int my_function(void * argc)
{
	wait_queue_head_t head;
	wait_queue_t data;		
	printk("<0>in the kernel thread function!\n");	
	init_waitqueue_head(&head);   //³õÊŒ»¯µÈŽý¶ÓÁÐÍ·ÔªËØ
	init_waitqueue_entry(&data,current);  //ÓÃµ±Ç°œø³Ì³õÊŒ»¯µÈŽý¶ÓÁÐÔªËØ
	add_wait_queue(&head,&data);  //œ«µ±Ç°œø³Ì²åÈëµœµÈµœ¶ÓÁÐÖÐ
	sleep_on_timeout(&head,10);	   //œ«µÈŽý¶ÓÁÐÖÃÓÚ²»¿ÉÖÐ¶ÏµÄµÈŽý×ŽÌ¬
	printk("<0>the current pid is:%d\n",current->pid);  //ÏÔÊŸµ±Ç°œø³ÌµÄPIDÖµ
	printk("<0>the state of the parent is:%ld\n",current->real_parent->state);  //ÏÔÊŸžžœø³ÌµÄ×ŽÌ¬
	//complete(&comple);  //µ÷ÓÃº¯Êý»œÐÑœø³Ì£¬²¢žüžÄdone×Ö¶ÎµÄÖµ
	printk("<0>out the kernel thread function\n");
	return 0;
}

//Ä£¿éŒÓÔØº¯Êý¶šÒå
static int __init wait_for_completion_init(void)
{	
	int result;
	wait_queue_t data;
	printk("<0>into wait_for_completion_init.\n");				
	result=kernel_thread(my_function,NULL,CLONE_KERNEL); //ŽŽœšÐÂœø³Ì

	/*»ñÈ¡ÐÂœø³ÌµÄÃèÊö·ûÐÅÏ¢*/
	struct pid * kpid=find_get_pid(result);
	struct task_struct * task=pid_task(kpid,PIDTYPE_PID);

	init_completion(&comple);	 //³õÊŒ»¯completion±äÁ¿
	init_waitqueue_entry(&data,task);  //ÓÃÐÂœø³Ì³õÊŒ»¯µÈŽý¶ÓÁÐÔªËØ
	__add_wait_queue_tail(&(comple.wait),&data);   //œ«ÐÂœø³ÌŒÓÈëµÈŽý¶ÓÁÐµÄÎ²²¿
	wait_for_completion(&comple);  	//×èÈûœø³Ì£¬µÈŽýÐÂœø³ÌµÄœáÊø
	printk("<0>the result of the kernel_thread is :%d\n",result); //ÏÔÊŸº¯Êýkernel_thread( )º¯ÊýµÄ·µ»Øœá¹û
	printk("<0>the current pid is:%d\n",current->pid);   //ÏÔÊŸµ±Ç°œø³ÌµÄPIDÖµ
	printk("<0>out wait_for_completion_init.\n");
	return 0;
}

/*Ä£¿éÐ¶ÔØº¯Êý¶šÒå*/
static void __exit wait_for_completion_exit(void)
{	
        printk("<0>Goodbye wait_for_completion\n");	
}

/*Ä£¿éŒÓÔØŒ°Ð¶ÔØº¯Êýµ÷ÓÃ*/
module_init(wait_for_completion_init);
module_exit(wait_for_completion_exit);


