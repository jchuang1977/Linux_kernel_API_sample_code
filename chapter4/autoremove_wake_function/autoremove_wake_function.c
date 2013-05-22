/********************************************************************************
* File Name:	autoremove_wake_function.c
* Description:	第4章实例训练          
* Reference book:《Linux内核API完全参考手册》邱铁，周玉，邓莹莹 ，机械工业出版社.2010.9  
* E_mail:openlinux2100@gmail.com			                
*
********************************************************************************/
/*Í·ÎÄŒþÒýÓÃ*/
#include <linux/module.h>
#include <linux/sched.h>
#include <linux/list.h>
#include <linux/wait.h>
MODULE_LICENSE("GPL");

/*È«ŸÖ±äÁ¿¶šÒå*/ 
wait_queue_head_t head;  //µÈŽý¶ÓÁÐÍ·ÔªËØ
wait_queue_t data;      //µÈŽý¶ÓÁÐÔªËØ

/*×Óœø³ÌŽŠÀíº¯Êý¶šÒå*/
int my_function(void * argc)
{
	int  wait_queue_num=0,return_data;
	wait_queue_t *curr, *next;
	printk("<0>in the kernel thread function!\n");	
	list_for_each_entry_safe(curr, next, &(head.task_list), task_list)    //ÉšÃèµÈŽý¶ÓÁÐ£¬ÏÔÊŸµÈŽý¶ÓÁÐÖÐµÄœø³ÌµÄPIDÖµŒ°œø³ÌËùŽŠµÄ×ŽÌ¬
	{
		wait_queue_num++;		  //ŒÇÂŒµ±Ç°µÈŽý¶ÓÁÐÖÐµÄœø³ÌµÄÊý
		printk("<0>the pid value of the current data of the waitqueue is:%d\n",((struct task_struct *)(curr->private))->pid); //ÏÔÊŸœø³ÌµÄPIDÖµ
		printk("<0>the state of the current data of the waitqueue is:%ld\n",((struct task_struct *)(curr->private))->state);  //ÏÔÊŸœø³ÌµÄ×ŽÌ¬
	}		
	printk("<0>the value of the wait_queue_num is :%d\n",wait_queue_num); //Êä³öµÈŽý¶ÓÁÐÖÐµÄœø³ÌÊý
	return_data=autoremove_wake_function(&data,TASK_NORMAL,1,NULL);   //µ÷ÓÃº¯Êýœ«žžœø³ÌŽÓµÈŽý¶ÓÁÐÖÐÉŸ³ý
	wait_queue_num=0;
	list_for_each_entry_safe(curr, next, &(head.task_list), task_list)   //ÏÔÊŸº¯Êýµ÷ÓÃÖ®ºóµÈŽý¶ÓÁÐÖÐœø³ÌµÄÐÅÏ¢
	{
		wait_queue_num++;		
		printk("<0>the pid value of the current data of the waitqueue is:%d\n",((struct task_struct *)(curr->private))->pid);
		printk("<0>the state of the current data of the waitqueue is:%ld\n",((struct task_struct *)(curr->private))->state);
	}		
	printk("<0>the value of the wait_queue_num is :%d\n",wait_queue_num); //ÏÔÊŸº¯Êýµ÷ÓÃÖ®ºóµÈŽý¶ÓÁÐÖÐµÄÔªËØžöÊý
	printk("<0>the return_data of the autoremove_wake_function is :%d\n",return_data); //ÏÔÊŸautoremove_wake_function( )º¯ÊýµÄ·µ»Øœá¹û
	printk("<0>the current pid is:%d\n",current->pid);   //ÏÔÊŸµ±Ç°œø³ÌµÄPIDÖµ
	printk("<0>out the kernel thread function\n");
	return 0;
}

/*Ä£¿éŒÓÔØº¯Êý¶šÒå*/
static int __init autoremove_wake_function_init(void)
{	
	int result,result1=-2,wait_queue_num=0,left_time;
	wait_queue_t *curr, *next;	
	printk("<0>into autoremove_wake_function_init.\n");				
	result=kernel_thread(my_function,NULL,CLONE_KERNEL);  //ŽŽœšÐÂœø³Ì
	init_waitqueue_head(&head);   //³õÊŒ»¯µÈŽý¶ÓÁÐÍ·ÔªËØ
	init_waitqueue_entry(&data,current); //ÓÃµ±Ç°œø³Ì³õÊŒ»¯µÈŽý¶ÓÁÐÖÐµÄÒ»žöÔªËØ
	add_wait_queue(&head,&data);   //œ«µ±Ç°œø³ÌŒÓÈëµÈŽý¶ÓÁÐ
	left_time=sleep_on_timeout(&head,100);  //œ«µÈŽý¶ÓÁÐÖÃÓÚ²»¿ÉÖÐ¶ÏµÄµÈŽý×ŽÌ¬
	if(data.private!=NULL)	
            result1=autoremove_wake_function(&data,TASK_ALL,0,NULL);	  //œ«µ±Ç°œø³ÌŽÓµÈŽý¶ÓÁÐÖÐÉŸ³ý
	list_for_each_entry_safe(curr, next, &(head.task_list), task_list)   //ÏÔÊŸµ±Ç°µÈŽý¶ÓÁÐÖÐµÄœø³ÌµÄÐÅÏ¢
	{
		wait_queue_num++;		
		printk("<0>the pid value of the current data of the waitqueue is:%d\n",((struct task_struct *)(curr->private))->pid);
		printk("<0>the state of the current data of the waitqueue is:%ld\n",((struct task_struct *)(curr->private))->state);
	}
	printk("<0>the letf time of the sleep_on_timeout is :%d\n",left_time);  //ÏÔÊŸº¯Êýsleep_on_timeout( )µÄ·µ»Øœá¹û
	printk("<0>the return result of the autoremove_wake_function is :%d\n",result1); //ÏÔÊŸº¯Êýautoremove_wake_function( )µÄ·µ»Øœá¹û
	printk("<0>the value of the wait_queue_num is :%d\n",wait_queue_num);   //ÏÔÊŸµ±Ç°µÈŽý¶ÓÁÐÖÐµÄÔªËØžöÊý
	printk("<0>the result of the kernel_thread is :%d\n",result); //ÏÔÊŸº¯Êýkernel_thread( )µÄ·µ»Øœá¹û
	printk("<0>the current pid is:%d\n",current->pid);         //ÏÔÊŸµ±Ç°œø³ÌµÄPIDÖµ
	printk("<0>out autoremove_wake_function_init.\n");
	return 0;
}

/*Ä£¿éÐ¶ÔØº¯Êý¶šÒå*/
static void __exit autoremove_wake_function_exit(void)
{	
        printk("<0>Goodbye autoremove_wake_function\n");	
}

/*Ä£¿éŒÓÔØŒ°Ð¶ÔØº¯Êýµ÷ÓÃ*/
module_init(autoremove_wake_function_init);
module_exit(autoremove_wake_function_exit);


