/********************************************************************************
* File Name:	kernel_thread.c
* Description:	第3章实例训练          
* Reference book:《Linux内核API完全参考手册》邱铁，周玉，邓莹莹 ，机械工业出版社.2010.9  
* E_mail:openlinux2100@gmail.com			                
*
********************************************************************************/
#include <linux/module.h>
#include <linux/sched.h>
#include <linux/pid.h>

MODULE_LICENSE("GPL");

int my_function(void * argc)    //×Óœø³ÌÖŽÐÐµÄº¯Êý¶šÒå
{
	printk("<0>in the kernel thread function!\n");	
	printk("<0>the current pid is:%d\n",current->pid); //ÏÔÊŸµ±Ç°œøÐÐµÄœø³ÌºÅ
	return 0;
}

static int __init kernel_thread_init(void)   //Ä£¿éŒÓÔØº¯Êý¶šÒå
{	
	int result;
	printk("<0> into kernel_thread_init.\n");		
	result=kernel_thread(my_function,NULL,CLONE_KERNEL);  //ŽŽœšÒ»žöÐÂµÄœø³Ì
	printk("<0>the kernel_thread result is:%d\n",result); //ÏÔÊŸº¯ÊýÖŽÐÐœá¹û
	printk("<0>the current pid is:%d\n",current->pid);    //ÏÔÊŸµ±Ç°œø³ÌµÄœø³ÌºÅ
	printk("<0> out kernel_thread_init.\n");
	return 0;
}

static void __exit kernel_thread_exit(void)  //Ä£¿éÍË³öº¯Êý¶šÒå
{
        printk("<0>Goodbye  kernel_thread\n");
}

module_init(kernel_thread_init);
module_exit(kernel_thread_exit);


