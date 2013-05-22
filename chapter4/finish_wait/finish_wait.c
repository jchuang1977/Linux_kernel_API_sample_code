/********************************************************************************
* File Name:	finish_wait.c
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
	printk("<0>the current pid is:%d\n",current->pid); //ÏÔÊŸµ±Ç°œø³ÌµÄPIDÖµ
	printk("<0>out the kernel thread function\n");
	return 0;
}

/*Ä£¿éŒÓÔØº¯Êý¶šÒå*/
static int __init finish_wait_init(void)
{	
	/*Ò»Ð©ŸÖ²¿±äÁ¿¶šÒå*/
	int result,result1;	
	int  wait_queue_num=0;
	wait_queue_head_t head;
	wait_queue_t data,data1,*curr, *next;	

	printk("<0>into finish_wait_init.\n");			
		
	/*ŽŽœšÐÂœø³Ì£¬ÓÃÓÚŒÓÈëµÈŽý¶ÓÁÐ*/	
	result=kernel_thread(my_function,NULL,CLONE_KERNEL); 
	result1=kernel_thread(my_function,NULL,CLONE_KERNEL);

	/*»ñÈ¡ÐÂœø³ÌµÄÃèÊö·ûÐÅÏ¢*/
	struct pid * kpid = find_get_pid(result);
	struct task_struct * task = pid_task(kpid,PIDTYPE_PID);
	struct pid * kpid1 = find_get_pid(result1);
	struct task_struct * task1 = pid_task(kpid1,PIDTYPE_PID);

	init_waitqueue_head(&head);  //³õÊŒ»¯µÈŽý¶ÓÁÐÍ·ÖžÕë
	init_waitqueue_entry(&data,task); //ÓÃÐÂœø³Ì³õÊŒ»¯µÈŽý¶ÓÁÐÔªËØ
	data.task_list.next=&data.task_list; //³õÊŒ»¯µÈŽý¶ÓÁÐÁŽ±íµÄnext×Ö¶ÎµÄÖµ
	printk("<0>the state of the current thread is:%ld\n",current->state); //ÏÔÊŸµ±Ç°œø³ÌµÄ×ŽÌ¬Öµ
	prepare_to_wait(&head,&data,130);  //œ«ÐÂœø³ÌŒÓÈëµÈŽý¶ÓÁÐÖÐ
	printk("<0>the state of the current thread is:%ld\n",current->state);  //ÏÔÊŸµ±Ç°œø³ÌµÄ×ŽÌ¬Öµ

	init_waitqueue_entry(&data1,task1); //ÓÃÐÂœø³Ì³õÊŒ»¯µÈŽý¶ÓÁÐÔªËØ
	data1.task_list.next=&data1.task_list; //³õÊŒ»¯µÈŽý¶ÓÁÐÁŽ±íµÄnext×Ö¶ÎµÄÖµ
	prepare_to_wait_exclusive(&head,&data1,2);  //œ«ÐÂœø³ÌŒÓÈëµÈŽý¶ÓÁÐÖÐ
	printk("<0>the state of the current thread is:%ld\n",current->state);  //ÏÔÊŸµ±Ç°œø³ÌµÄ×ŽÌ¬Öµ
	
       /*ÏÔÊŸµÈŽý¶ÓÁÐÖÐµÄœø³ÌµÄPIDÖµŒ°µÈŽý¶ÓÁÐÖÐÔªËØµÄflagsÖµ*/
	list_for_each_entry_safe(curr, next, &(head.task_list), task_list) 
	{
		wait_queue_num++;  //ÀÛŒÓµÈŽý¶ÓÁÐÖÐµÄÔªËØžöÊý
		printk("<0>the flag value of the current data of the waitqueue is:%d\n",curr->flags); //ÏÔÊŸ×Ö¶ÎflagsµÄÖµ		
		printk("<0>the pid value of the current data of the waitqueue is:%d\n",((struct task_struct *)(curr->private))->pid); //ÏÔÊŸPIDÖµ
	}		
	printk("<0>the value of the wait_queue_num is :%d\n",wait_queue_num); //ÏÔÊŸµ±Ç°µÈŽý¶ÓÁÐÖÐµÄÔªËØžöÊý
	finish_wait(&head,&data1);        //µ÷ÓÃº¯ÊýÉŸ³ýµÈŽý¶ÓÁÐÖÐµÄÒ»žöÔªËØ
	printk("<0>the state of the current thread is:%ld\n",current->state);  //ÏÔÊŸº¯Êýµ÷ÓÃÖ®ºóµ±Ç°œø³ÌµÄPIDÖµ

	wait_queue_num=0;
	/*ÏÔÊŸº¯Êýµ÷ÓÃÖ®ºóµÈŽý¶ÓÁÐÖÐœø³ÌµÄPIDÖµŒ°µÈŽý¶ÓÁÐÖÐÔªËØµÄflagsÖµ*/
	list_for_each_entry_safe(curr, next, &(head.task_list), task_list) 
	{
		wait_queue_num++;   //ÀÛŒÓµÈŽý¶ÓÁÐÖÐµÄÔªËØžöÊý
		printk("<0>the flag value of the current data of the waitqueue is:%d\n",curr->flags);	 //ÏÔÊŸ×Ö¶ÎflagsµÄÖµ 	
		printk("<0>the pid value of the current data of the waitqueue is:%d\n",((struct task_struct *)(curr->private))->pid); //ÏÔÊŸPIDÖµ
	}
	printk("<0>the value of the wait_queue_num is :%d\n",wait_queue_num); //ÏÔÊŸº¯Êýµ÷ÓÃÖ®ºóµÈŽý¶ÓÁÐÖÐµÄÔªËØžöÊý
	printk("<0>the result of the kernel_thread is :%d\n",result);        //ÏÔÊŸº¯Êýkernel_thread( )µÄ·µ»Øœá¹û
	printk("<0>the result1 of the kernel_thread is :%d\n",result1);
	printk("<0>the current pid is:%d\n",current->pid);             //ÏÔÊŸµ±Ç°œø³ÌµÄPIDÖµ
	printk("<0>out finish_wait_init.\n");
	return 0;
}

//Ä£¿éÐ¶ÔØº¯Êý¶šÒå
static void __exit finish_wait_exit(void)
{	
        printk("<0>Goodbye finish_wait\n");	
}

//Ä£¿éŒÓÔØŒ°Ð¶ÔØº¯Êýµ÷ÓÃ
module_init(finish_wait_init);
module_exit(finish_wait_exit);


