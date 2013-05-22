/********************************************************************************
* File Name:	abort_exclusive_wait.c
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
	printk("<0>the current pid is:%d\n",current->pid); //ÏÔÊŸµ±Ç°œø³ÌµÄœø³ÌºÅ
	printk("<0>out the kernel thread function\n");
	return 0;
}

//Ä£¿éŒÓÔØº¯Êý¶šÒå
static int __init abort_exclusive_wait_init(void)
{	
	/*ŸÖ²¿±äÁ¿¶šÒå*/
	int result,result1,result2;	 
	int  wait_queue_num=0;
	wait_queue_head_t head;
	wait_queue_t data,data1,data2,*curr, *next;	

	printk("<0>into abort_exclusive_wait_init.\n");	
	
	/*ŽŽœš3žöÐÂœø³Ì*/			
	result=kernel_thread(my_function,NULL,CLONE_KERNEL);
	result1=kernel_thread(my_function,NULL,CLONE_KERNEL);
	result2=kernel_thread(my_function,NULL,CLONE_KERNEL);

	/*»ñÈ¡3žöÐÂœø³ÌµÄÈÎÎñÃèÊö·û*/
	struct pid * kpid = find_get_pid(result);
	struct task_struct * task = pid_task(kpid,PIDTYPE_PID);
	struct pid * kpid1 = find_get_pid(result1);
	struct task_struct * task1 = pid_task(kpid1,PIDTYPE_PID);
	struct pid * kpid2=find_get_pid(result2);
	struct task_struct * task2=pid_task(kpid2,PIDTYPE_PID);	
	
	init_waitqueue_head(&head);    //³õÊŒ»¯µÈŽý¶ÓÁÐµÄÍ·ÖžÕë
	init_waitqueue_entry(&data,task);   //ÓÃÐÂœø³Ì³õÊŒ»¯µÈŽý¶ÓÁÐÖÐµÄÒ»žöÔªËØ
	data.task_list.next=&data.task_list;  //³õÊŒ»¯µÈŽý¶ÓÁÐÁŽ±íµÄnextÖµ
	prepare_to_wait(&head,&data,130);     //œ«ÐÂœø³ÌŒÓÈëµÈŽý¶ÓÁÐ,²¢žÄ±äµ±ÆÚœø³ÌµÄ×ŽÌ¬

	init_waitqueue_entry(&data1,task1);  //œ«ÐÂœø³ÌŒÓÈëµÈŽý¶ÓÁÐÖÐµÄÒ»žöÔªËØ
	data1.task_list.next=&data1.task_list;  //³õÊŒ»¯µÈŽý¶ÓÁÐÁŽ±íµÄnextÖµ
	prepare_to_wait_exclusive(&head,&data1,2);  //œ«ÐÂœø³ÌŒÓÈëµÈŽý¶ÓÁÐ,²¢žÄ±äµ±ÆÚœø³ÌµÄ×ŽÌ¬
	
	init_waitqueue_entry(&data2,task2);  //œ«ÐÂœø³ÌŒÓÈëµÈŽý¶ÓÁÐÖÐµÄÒ»žöÔªËØ 
	data2.task_list.next=&data2.task_list;  //³õÊŒ»¯µÈŽý¶ÓÁÐÁŽ±íµÄnextÖµ
	prepare_to_wait_exclusive(&head,&data2,1);  //œ«ÐÂœø³ÌŒÓÈëµÈŽý¶ÓÁÐ,²¢žÄ±äµ±ÆÚœø³ÌµÄ×ŽÌ¬
		
	list_for_each_entry_safe(curr, next, &(head.task_list), task_list)  //Ñ­»·ÏÔÊŸµÈŽý¶ÓÁÐÖÐµÄœø³ÌµÄPIDÖµŒ°×ŽÌ¬ÐÅÏ¢
	{
		wait_queue_num++;    //ÀÛŒÓµ±Ç°µÈŽý¶ÓÁÐÖÐµÄœø³ÌÊý
		printk("<0>the pid value of the current data of the waitqueue is:%d\n",((struct task_struct *)(curr->private))->pid); //ÏÔÊŸµÈŽý¶ÓÁÐÖÐµ±Ç°œø³ÌµÄPIDÖµ
		printk("<0>the state of the current data of the waitqueue is:%ld\n",((struct task_struct *)(curr->private))->state);  //ÏÔÊŸµÈŽý¶ÓÁÐÖÐµ±Ç°œø³ÌµÄ×ŽÌ¬
	}		
	printk("<0>the value of the wait_queue_num is :%d\n",wait_queue_num);  //ÏÔÊŸµ±Ç°µÈŽý¶ÓÁÐÖÐµÄµÈŽýœø³ÌÊý
	printk("<0>the state of the current thread is:%ld\n",current->state);  //ÏÔÊŸµ±Ç°œø³ÌµÄ×ŽÌ¬
	
	/*
	((struct task_struct *)(data2.private))->state=130;   //žüžÄœø³ÌµÄ×ŽÌ¬
	finish_wait(&head,&data1);  //œ«œø³ÌŽÓµÈŽý¶ÓÁÐÖÐÉŸ³ý
	wait_queue_num=0;
	list_for_each_entry_safe(curr, next, &(head.task_list), task_list)   //ÏÔÊŸº¯Êýµ÷ÓÃÖ®ºóµÈŽý¶ÓÁÐÖÐµÄœø³ÌµÄPIDÖµŒ°×ŽÌ¬ÐÅÏ¢
	{
		wait_queue_num++;	//ÀÛŒÓµ±Ç°µÈŽý¶ÓÁÐÖÐµÄœø³ÌÊý	
		printk("<0>the pid value of the current data of the waitqueue is:%d\n",((struct task_struct *)(curr->private))->pid); //ÏÔÊŸµÈŽý¶ÓÁÐÖÐµ±Ç°œø³ÌµÄPIDÖµ
		printk("<0>the state of the current data of the waitqueue is:%ld\n",((struct task_struct *)(curr->private))->state);  //ÏÔÊŸµÈŽý¶ÓÁÐÖÐµ±Ç°œø³ÌµÄ×ŽÌ¬
	}
	printk("<0>the value of the wait_queue_num is :%d\n",wait_queue_num); //ÏÔÊŸº¯Êýµ÷ÓÃÖ®ºóµÈŽý¶ÓÁÐÖÐµÄœø³ÌÊý
	*/

	abort_exclusive_wait(&head,&data1,TASK_NORMAL,NULL);      //žÄ±äµ±Ç°œø³ÌµÄ×ŽÌ¬£¬ÉŸ³ýµÈŽý¶ÓÁÐÖÐµÄœø³Ì»ò»œÐÑµÈŽý¶ÓÁÐÖÐµÄœø³Ì
	printk("<0>the state of the current thread is:%ld\n",current->state); //ÏÔÊŸµ±Ç°œø³ÌµÄ×ŽÌ¬

	wait_queue_num=0;
	list_for_each_entry_safe(curr, next, &(head.task_list), task_list)   //ÏÔÊŸº¯Êýµ÷ÓÃÖ®ºóµÈŽý¶ÓÁÐÖÐµÄœø³ÌµÄPIDÖµŒ°×ŽÌ¬ÐÅÏ¢
	{
		wait_queue_num++;	//ÀÛŒÓµ±Ç°µÈŽý¶ÓÁÐÖÐµÄœø³ÌÊý	
		printk("<0>the pid value of the current data of the waitqueue is:%d\n",((struct task_struct *)(curr->private))->pid); //ÏÔÊŸµÈŽý¶ÓÁÐÖÐµ±Ç°œø³ÌµÄPIDÖµ
		printk("<0>the state of the current data of the waitqueue is:%ld\n",((struct task_struct *)(curr->private))->state);  //ÏÔÊŸµÈŽý¶ÓÁÐÖÐµ±Ç°œø³ÌµÄ×ŽÌ¬
	}
	printk("<0>the value of the wait_queue_num is :%d\n",wait_queue_num); //ÏÔÊŸº¯Êýµ÷ÓÃÖ®ºóµÈŽý¶ÓÁÐÖÐµÄœø³ÌÊý
		
	/*ÏÔÊŸº¯Êýkernel_thread( )µÄ·µ»Øœá¹û*/
	printk("<0>the result of the kernel_thread is :%d\n",result);   
	printk("<0>the result1 of the kernel_thread is :%d\n",result1);
	printk("<0>the result2 of the kernel_thread is :%d\n",result2);
	printk("<0>the current pid is:%d\n",current->pid);  //ÏÔÊŸµ±Ç°œø³ÌµÄPIDÖµ
	printk("<0>out abort_exclusive_wait_init.\n");
	return 0;
}

/*Ä£¿éÐ¶ÔØº¯Êý¶šÒå*/
static void __exit abort_exclusive_wait_exit(void)
{	
        printk("<0>Goodbye abort_exclusive_wait\n");	
}

/*Ä£¿éŒÓÔØŒ°Ð¶ÔØº¯Êýµ÷ÓÃ*/
module_init(abort_exclusive_wait_init);
module_exit(abort_exclusive_wait_exit);


