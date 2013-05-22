/********************************************************************************
* File Name:	add_wait_queue.c
* Description:	第4章实例训练          
* Reference book:《Linux内核API完全参考手册》邱铁，周玉，邓莹莹 ，机械工业出版社.2010.9  
* E_mail:openlinux2100@gmail.com			                
*
********************************************************************************/

/*Í·ÎÄŒþÒýÓÃ*/
#include <linux/module.h>
#include <linux/sched.h>
#include <linux/list.h>
MODULE_LICENSE("GPL");

/*×Óœø³ÌŽŠÀíº¯Êý¶šÒå*/
int my_function(void * argc)
{
	printk("<0>in the kernel thread function!\n");	
	printk("<0>the current pid is:%d\n",current->pid); //ÏÔÊŸµ±Ç°œø³ÌPIDÖµ
	printk("<0>out the kernel thread function\n");
	return 0;
}

/*Ä£¿éŒÓÔØº¯Êý¶šÒå*/
static int __init add_wait_queue_init(void)
{	
	//ŸÖ²¿±äÁ¿¶šÒå
	int result,result1;	
	int  wait_queue_num=0;
	wait_queue_head_t head;
	wait_queue_t data,data1,*curr, *next;	

	printk("<0>into add_wait_queue_init.\n");
	
	/*ŽŽœš2žöÐÂœø³Ì*/				
	result=kernel_thread(my_function,NULL,CLONE_KERNEL);
	result1=kernel_thread(my_function,NULL,CLONE_KERNEL);

	/*»ñÈ¡ÐÂœø³ÌµÄœø³ÌÃèÊö·ûÐÅÏ¢*/
	struct pid * kpid = find_get_pid(result);
	struct task_struct * task = pid_task(kpid,PIDTYPE_PID);
	struct pid * kpid1 = find_get_pid(result1);
	struct task_struct * task1 = pid_task(kpid1,PIDTYPE_PID);

	init_waitqueue_head(&head);   //³õÊŒ»¯µÈŽý¶ÓÁÐÍ·ÖžÕë

	 /*ÓÃÐÂœø³Ì³õÊŒ»¯µÈŽý¶ÓÁÐÔªËØ*/
	init_waitqueue_entry(&data,task);
	init_waitqueue_entry(&data1,task1);

       /*œ«ÐÂœø³ÌŒÓÈëµÈŽý¶ÓÁÐÖÐ*/
	add_wait_queue(&head,&data);
	add_wait_queue(&head,&data1);

	/*Ñ­»·ÏÔÊŸµÈŽý¶ÓÁÐÖÐµÄœø³ÌµÄÐÅÏ¢*/
	list_for_each_entry_safe(curr, next, &(head.task_list), task_list) 
	{
		wait_queue_num++; //ÀÛŒÓµÈŽý¶ÓÁÐœø³ÌžöÊý
		
		/*ÏÔÊŸµÈŽý¶ÓÁÐÖÐµ±Ç°ÔªËØµÄflags×Ö¶ÎµÄÖµ*/
		printk("<0>the flag value of the current data of the waitqueue is:%d\n",curr->flags);	
		
		/*ÏÔÊŸµÈŽý¶ÓÁÐÖÐµ±Ç°œø³ÌµÄPIDÖµ*/	
		printk("<0>the pid value of the current data of the waitqueue is:%d\n",((struct task_struct *)(curr->private))->pid);
	}
	printk("<0>the value of the wait_queue_num is :%d\n",wait_queue_num); //ÏÔÊŸµ±Ç°µÈŽý¶ÓÁÐÖÐµÄœø³ÌÊý
	
	/*ÏÔÊŸŽŽœšÐÂœø³ÌµÄœø³ÌºÅ*/
	printk("<0>the result of the kernel_thread is :%d\n",result); 
	printk("<0>the result1 of the kernel_thread is :%d\n",result1);
	printk("<0>the current pid is:%d\n",current->pid);//ÏÔÊŸµ±Ç°œø³ÌµÄPIDÖµ
	printk("<0>out add_wait_queue_init.\n");
	return 0;
}

/*Ä£¿éÐ¶ÔØº¯Êý¶šÒå*/
static void __exit add_wait_queue_exit(void)
{	
        printk("<0>Goodbye add_wait_queue\n");	
}

/*Ä£¿éŒÓÔØŒ°Ð¶ÔØº¯Êýµ÷ÓÃ*/
module_init(add_wait_queue_init);
module_exit(add_wait_queue_exit);


