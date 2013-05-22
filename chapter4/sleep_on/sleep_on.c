/********************************************************************************
* File Name:	sleep_on.c
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
	printk("<0>the current pid is:%d\n",current->pid); //ÏÔÊŸµ±Ç°œø³ÌµÄPID
	printk("<0>the state of the parent is:%ld\n",current->real_parent->state); //ÏÔÊŸžžœø³ÌµÄ×ŽÌ¬
	printk("<0>out the kernel thread function\n");
	return 0;
}

//Ä£¿é³õÊŒ»¯º¯Êýº¯Êý¶šÒå
static int __init sleep_on_init(void)
{	
	int result;
	wait_queue_head_t head;
	wait_queue_t data;
	printk("<0>into sleep_on_init.\n");				
	result=kernel_thread(my_function,NULL,CLONE_KERNEL);	//ŽŽœšÐÂœø³Ì	
       init_waitqueue_head(&head);      //³õÊŒ»¯µÈŽý¶ÓÁÐÍ·œáµã
	init_waitqueue_entry(&data,current);  //ÓÃµ±Ç°œø³Ì³õÊŒ»¯µÈŽý¶ÓÁÐÔªËØ
	add_wait_queue(&head,&data);  //œ«µ±Ç°œø³ÌŒÓÈëµÈŽý¶ÓÁÐÖÐ
	sleep_on(&head);	 //œ«µÈŽý¶ÓÁÐÖÐµÄœø³ÌÖÃÓÚË¯Ãß×ŽÌ¬
	printk("<0>the result of the kernel_thread is :%d\n",result);  //ÏÔÊŸº¯Êýkernel_thread()µÄ·µ»ØÖµ
	printk("<0>the current pid is:%d\n",current->pid);   //ÏÔÊŸµ±Ç°œø³ÌµÄPIDÖµ
	printk("<0>out sleep_on_init.\n");
	return 0;
}

//Ä£¿éÐ¶ÔØº¯Êý¶šÒå
static void __exit sleep_on_exit(void)
{	
        printk("<0>Goodbye sleep_on\n");	
}

module_init(sleep_on_init);
module_exit(sleep_on_exit);


