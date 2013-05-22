/********************************************************************************
* File Name:	wake_up_process.c
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
	int data=-1;
	printk("<0>in the kernel thread function!\n");	
	printk("<0>the current pid is:%d\n",current->pid); //ÏÔÊŸµ±Ç°œø³ÌµÄPID
	printk("<0>the state of the parent process before wake_up_process is:%ld\n",current->real_parent->state); //ÏÔÊŸµ±Ç°žžœø³ÌµÄ×ŽÌ¬
	data=wake_up_process(current->real_parent); //µ÷ÓÃº¯Êý»œÐÑžžœø³Ì£¬žžœø³ÌŽŠÓÚË¯Ãß×ŽÌ¬
	printk("<0>the state of the parent process after wake_up_process is:%ld\n",current->real_parent->state); //ÏÔÊŸº¯Êýµ÷ÓÃÖ®ºóžžœø³ÌµÄ×ŽÌ¬
	printk("<0>the result of the wake_up_process is:%d\n",data);  //ÏÔÊŸº¯Êýwake_up_process()µ÷ÓÃ·µ»Øœá¹û							
	printk("<0>out the kernel thread function\n");
	return 0;
}

//Ä£¿éŒÓÔØº¯Êý¶šÒå
static int __init wake_up_process_init(void)
{	
	int result,result2;
	long result1;
	wait_queue_head_t head; //µÈŽý¶ÓÁÐÍ·œáµã¶šÒå
	wait_queue_t data;   //µÈŽý¶ÓÁÐÒ»žöÔªËØ¶šÒå
	printk("<0>into wake_up_process_init.\n");				
	result=kernel_thread(my_function,NULL,CLONE_KERNEL);  //ŽŽœšÐÂœø³Ì	
    init_waitqueue_head(&head);   //³õÊŒ»¯µÈŽý¶ÓÁÐµÄÍ·œáµã
	init_waitqueue_entry(&data,current);   //ÓÃµ±Ç°œø³Ì³õÊŒ»¯µÈŽý¶ÓÁÐµÄœáµã
	add_wait_queue(&head,&data);           //œ«µ±Ç°œø³ÌŒÓÈëµÈŽý¶ÓÁÐ
	result1=sleep_on_timeout(&head,10);   //œ«µÈŽý¶ÓÁÐÖÃÓÚË¯Ãß×ŽÌ¬
	result2=wake_up_process(current);	 //»œÐÑµ±Ç°œø³Ì£¬µ±Ç°œø³ÌŽŠÓÚRUNNING×ŽÌ¬
	printk("<0>the result of the kernel_thread is :%d\n",result); //ÏÔÊŸº¯Êýkernel_thread()µÄ·µ»Øœá¹û
	printk("<0>the result of the sleep_on_timeout is:%d\n",result1);  //ÏÔÊŸsleep_on_timeout()º¯ÊýµÄ·µ»Øœá¹û
	printk("<0>the result of the wake_up_process is:%d\n",result2);   //ÏÔÊŸº¯Êýwake_up_process()º¯ÊýµÄ·µ»Øœá¹û
	printk("<0>the current pid is:%d\n",current->pid);  //ÏÔÊŸµ±Ç°œø³ÌµÄPIDÖµ
	printk("<0>out wake_up_process_init.\n");
	return 0;
}

//Ä£¿éÐ¶ÔØº¯Êý¶šÒå
static void __exit wake_up_process_exit(void)
{	
        printk("<0>Goodbye wake_up_process\n");	
}

module_init(wake_up_process_init);
module_exit(wake_up_process_exit);


