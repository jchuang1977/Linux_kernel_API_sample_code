/********************************************************************************
* File Name:	sleep_on_timeout.c
* Description:	第4章实例训练          
* Reference book:《Linux内核API完全参考手册》邱铁，周玉，邓莹莹 ，机械工业出版社.2010.9  
* E_mail:openlinux2100@gmail.com			                
*
********************************************************************************/
#include <linux/module.h>
#include <linux/sched.h>
#include <linux/pid.h>
#include <linux/wait.h>
MODULE_LICENSE("GPL");

//×Óœø³Ìº¯Êý¶šÒå
int my_function(void * argc)
{
	printk("<0>in the kernel thread function!\n");	
	printk("<0>the current pid is:%d\n",current->pid); //ÏÔÊŸµ±Ç°œø³ÌPID
	printk("<0>the state of the parent is:%ld\n",current->real_parent->state); //ÏÔÊŸžžœø³ÌµÄ×ŽÌ¬
	//wake_up_process(current->real_parent); //»œÐÑžžœø³Ì
	printk("<0>out the kernel thread function\n");
	return 0;
}

//Ä£¿éŒÓÔØº¯Êý¶šÒå
static int __init sleep_on_timeout_init(void)
{	
	int result;
	long result1;
	wait_queue_head_t head;
	wait_queue_t data;
	printk("<0>into sleep_on_timeout_init.\n");				
	result=kernel_thread(my_function,NULL,CLONE_KERNEL);	//ŽŽœšÐÂœø³Ì
    init_waitqueue_head(&head);  //³õÊŒ»¯µÈŽý¶ÓÁÐµÄÍ·œáµã
	init_waitqueue_entry(&data,current); //ÓÃµ±Ç°œø³Ì³õÊŒ»¯µÈŽý¶ÓÁÐÖÐµÄœÚµãÔªËØ
	add_wait_queue(&head,&data); //œ«µ±Ç°œø³ÌŒÓÈëµÈŽý¶ÓÁÐ
	result1=sleep_on_timeout(&head,100); //œ«µÈŽý¶ÓÁÐÖÐµÄœø³ÌÖÃÓÚË¯Ãß×ŽÌ¬	
	printk("<0>the result of the kernel_thread is :%d\n",result); //ÏÔÊŸkernel_thread()º¯ÊýµÄ·µ»Øœá¹û
	printk("<0>the result of the sleep_on_timeout is:%ld\n",result1); //ÏÔÊŸº¯Êýsleep_on_timeout()µÄ·µ»Øœá¹û
	printk("<0>the current pid is:%d\n",current->pid); //ÏÔÊŸµ±Ç°œø³ÌµÄPID
	printk("<0>out sleep_on_timeout_init.\n");
	return 0;
}

//Ä£¿éÐ¶ÔØº¯Êý¶šÒå
static void __exit sleep_on_timeout_exit(void)
{	
        printk("<0>Goodbye sleep_on_timeout\n");	
}

module_init(sleep_on_timeout_init);
module_exit(sleep_on_timeout_exit);


