/********************************************************************************
* File Name:	init_waitqueue_head.c
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

/*Ä£¿éŒÓÔØº¯Êý¶šÒå*/
static int __init init_waitqueue_head_init(void)
{	
	wait_queue_head_t head;  //µÈŽý¶ÓÁÐÍ·
	printk("<0>into init_waitqueue_head_init.\n");
	if(head.task_list.next==NULL||head.task_list.prev==NULL)
	{
		printk("<0>the head has not been initialized\n");	
	}
	init_waitqueue_head(&head);   //³õÊŒ»¯µÈŽý¶ÓÁÐÍ·ÖžÕë
	if(head.task_list.next==&head.task_list&&head.task_list.prev==&head.task_list)
	{
		printk("<0>the head has been initialized\n");
	}
	else
	{
		printk("<0>the head has not been initialized\n");
	}
	printk("<0>out init_waitqueue_head_init.\n");
	return 0;
}

/*Ä£¿éÐ¶ÔØº¯Êý¶šÒå*/
static void __exit init_waitqueue_head_exit(void)
{	
        printk("<0>Goodbye init_waitqueue_head\n");	
}

/*Ä£¿éŒÓÔØŒ°Ð¶ÔØº¯Êýµ÷ÓÃ*/
module_init(init_waitqueue_head_init);
module_exit(init_waitqueue_head_exit);


