/********************************************************************************
* File Name:	interruptible_sleep_on_timeout.c
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

int my_function(void * argc)
{
	printk("<0>in the kernel thread function!\n");	
	printk("<0>the current pid is:%d\n",current->pid);
	printk("<0>the state of the parent is:%ld\n",current->real_parent->state);
	//wake_up_process(current->real_parent);
	printk("<0>out the kernel thread function\n");
	return 0;
}

static int __init interruptible_sleep_on_timeout_init(void)
{	
	int result;
	long result1;
	wait_queue_head_t head;
	wait_queue_t data;
	printk("<0>into interruptible_sleep_on_timeout_init.\n");				
	result=kernel_thread(my_function,NULL,CLONE_KERNEL);		
        init_waitqueue_head(&head);
	init_waitqueue_entry(&data,current);
	add_wait_queue(&head,&data);
	
result1=interruptible_sleep_on_timeout(&head,100);
	printk("<0>the result of the kernel_thread is :%d\n",result);
	printk("<0>the result of the interruptible_sleep_on_timeout is:%ld\n",result1);
	printk("<0>the current pid is:%d\n",current->pid);
	printk("<0>out interruptible_sleep_on_timeout_init.\n");
	return 0;
}

static void __exit interruptible_sleep_on_timeout_exit(void)
{	
        printk("<0>Goodbye interruptible_sleep_on_timeout\n");	
}

module_init(interruptible_sleep_on_timeout_init);
module_exit(interruptible_sleep_on_timeout_exit);


