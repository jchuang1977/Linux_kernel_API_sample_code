/********************************************************************************
* File Name:	prepare_to_wait.c
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

/*×Óº¯ÊýŽŠÀíº¯Êý¶šÒå*/
int my_function(void * argc)
{
	printk("<0>in the kernel thread function!\n");	
	printk("<0>the current pid is:%d\n",current->pid); //ÏÔÊŸµ±Ç°œø³ÌµÄPIDÖµ
	printk("<0>out the kernel thread function\n");
	return 0;
}

/*Ä£¿éŒÓÔØº¯Êý¶šÒå*/
static int __init prepare_to_wait_init(void)
{	
	/*ŸÖ²¿±äÁ¿¶šÒå*/
	int result,result1;	
	int  wait_queue_num=0;
	wait_queue_head_t head;
	wait_queue_t data,data1,*curr, *next;	

	printk("<0>into prepare_to_wait_init.\n");	
	
	/*ŽŽœš2žöÐÂœø³Ì*/			
	result=kernel_thread(my_function,NULL,CLONE_KERNEL);
	result1=kernel_thread(my_function,NULL,CLONE_KERNEL);

	/*»ñÈ¡2žöÐÂœø³ÌµÄœø³ÌÃèÊö·ûÐÅÏ¢*/
	struct pid * kpid = find_get_pid(result);
	struct task_struct * task = pid_task(kpid,PIDTYPE_PID);
	struct pid * kpid1 = find_get_pid(result1);
	struct task_struct * task1 = pid_task(kpid1,PIDTYPE_PID);

	init_waitqueue_head(&head);        //³õÊŒ»¯µÈŽý¶ÓÁÐÍ·ÖžÕë
	init_waitqueue_entry(&data,task);  //ÓÃÐÂœø³Ì³õÊŒ»¯µÈŽý¶ÓÁÐÔªËØ
	data.task_list.next=&data.task_list; //³õÊŒ»¯µÈŽý¶ÓÁÐÔªËØµÄnext×Ö¶Î
	printk("<0>the state of the current thread is:%ld\n",current->state); //ÏÔÊŸµ±Ç°œø³ÌµÄ×ŽÌ¬
	prepare_to_wait(&head,&data,130); //œ«ÐÂœø³ÌŒÓÈëµÈŽý¶ÓÁÐ£¬²¢žüžÄµ±Ç°œø³ÌµÄ×ŽÌ¬
	printk("<0>the state of the current thread is:%ld\n",current->state); //ÏÔÊŸµ±Ç°œø³ÌµÄ×ŽÌ¬

	init_waitqueue_entry(&data1,task1); //ÓÃÐÂœø³Ì³õÊŒ»¯µÈŽý¶ÓÁÐÔªËØ
	prepare_to_wait(&head,&data1,1);   //œ«ÐÂœø³ÌŒÓÈëµÈŽý¶ÓÁÐ£¬²¢žüžÄµ±Ç°œø³ÌµÄ×ŽÌ¬
	printk("<0>the state of the current thread is:%ld\n",current->state); //ÏÔÊŸµ±Ç°œø³ÌµÄ×ŽÌ¬	

	/*Ñ­»·ÏÔÊŸµÈŽý¶ÓÁÐÖÐµÄµÈŽýÔªËØµÄÐÅÏ¢*/
	list_for_each_entry_safe(curr, next, &(head.task_list), task_list) 
	{
		wait_queue_num++; //ÀÛŒÓµÈŽý¶ÓÁÐÖÐµÄÔªËØžöÊý

		/*ÏÔÊŸµÈŽý¶ÓÁÐÖÐµ±Ç°µÈŽýÔªËØµÄflags×Ö¶ÎµÄÖµ*/
		printk("<0>the flag value of the current data of the waitqueue is:%d\n",curr->flags); 	
		
		/*ÏÔÊŸµÈŽý¶ÓÁÐÖÐµ±Ç°µÈŽýÔªËØ¶ÔÓŠµÄœø³ÌµÄPIDÖµ*/ 	
		printk("<0>the pid value of the current data of the waitqueue is:%d\n",((struct task_struct *)(curr->private))->pid);
	}
	printk("<0>the value of the wait_queue_num is :%d\n",wait_queue_num);  //ÏÔÊŸµ±Ç°µÈŽý¶ÓÁÐÖÐµÄµÈŽýÔªËØµÄžöÊý

	data1.task_list.next=&data1.task_list; //³õÊŒ»¯µÈŽý¶ÓÁÐÔªËØµÄnext×Ö¶Î
	prepare_to_wait(&head,&data1,1);   //œ«ÐÂœø³ÌŒÓÈëµÈŽý¶ÓÁÐ£¬²¢žüžÄµ±Ç°œø³ÌµÄ×ŽÌ¬
	wait_queue_num=0;

	/*Ñ­»·ÏÔÊŸµÈŽý¶ÓÁÐÖÐµÄµÈŽýÔªËØµÄÐÅÏ¢*/
	list_for_each_entry_safe(curr, next, &(head.task_list), task_list) 
	{
		wait_queue_num++; //ÀÛŒÓµÈŽý¶ÓÁÐÖÐµÄÔªËØžöÊý

		/*ÏÔÊŸµÈŽý¶ÓÁÐÖÐµ±Ç°µÈŽýÔªËØµÄflags×Ö¶ÎµÄÖµ*/
		printk("<0>the flag value of the current data of the waitqueue is:%d\n",curr->flags); 	
		
		/*ÏÔÊŸµÈŽý¶ÓÁÐÖÐµ±Ç°µÈŽýÔªËØ¶ÔÓŠµÄœø³ÌµÄPIDÖµ*/ 	
		printk("<0>the pid value of the current data of the waitqueue is:%d\n",((struct task_struct *)(curr->private))->pid);
	}
	printk("<0>the value of the wait_queue_num is :%d\n",wait_queue_num);  //ÏÔÊŸµ±Ç°µÈŽý¶ÓÁÐÖÐµÄµÈŽýÔªËØµÄžöÊý	

	/*ÏÔÊŸº¯Êýkernel_thread( )µÄ·µ»Øœá¹û*/
	printk("<0>the result of the kernel_thread is :%d\n",result);
	printk("<0>the result1 of the kernel_thread is :%d\n",result1);
	printk("<0>the current pid is:%d\n",current->pid); //ÏÔÊŸµ±Ç°œø³ÌµÄPIDÖµ
	printk("<0>out prepare_to_wait_init.\n");
	return 0;
}

/*Ä£¿éÐ¶ÔØº¯Êý¶šÒå*/
static void __exit prepare_to_wait_exit(void)
{	
        printk("<0>Goodbye prepare_to_wait\n");	
}

/*Ä£¿éŒÓÔØŒ°Ð¶ÔØº¯Êýµ÷ÓÃ*/
module_init(prepare_to_wait_init);
module_exit(prepare_to_wait_exit);

