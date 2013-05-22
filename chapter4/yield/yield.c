/********************************************************************************
* File Name:	yield.c
* Description:	第4章实例训练          
* Reference book:《Linux内核API完全参考手册》邱铁，周玉，邓莹莹 ，机械工业出版社.2010.9  
* E_mail:openlinux2100@gmail.com			                
*
********************************************************************************/
#include <linux/module.h>
#include <linux/sched.h>
#include <linux/pid.h>
MODULE_LICENSE("GPL");

//×Óº¯Êý¶šÒå
int my_function(void * argc)
{
	printk("<0>in the kernel thread function!\n");	
	printk("<0>the current pid is:%d\n",current->pid); //ÏÔÊŸµ±Ç°œø³ÌµÄPID
	printk("<0>out the kernel thread function\n");
	return 0;
}

//Ä£¿éŒÓÔØº¯Êý¶šÒå
static int __init yield_init(void)
{	
	int result;	
	printk("<0>into yield_init.\n");				
	result=kernel_thread(my_function,NULL,CLONE_KERNEL);	//ŽŽœšÐÂœø³Ì	
	yield(); //×èÈûžžœø³Ì£¬Ê¹×Óœø³ÌÖŽÐÐ
	printk("<0>the result of the kernel_thread is :%d\n",result); //ÏÔÊŸº¯Êýkernel_thread()µÄ·µ»Øœá¹û
	printk("<0>the current pid is:%d\n",current->pid); //ÏÔÊŸµ±Ç°œø³ÌµÄPID
	printk("<0>out yield_init.\n");
	return 0;
}

//Ä£¿éÐ¶ÔØº¯Êý¶šÒå
static void __exit yield_exit(void)
{	
        printk("<0>Goodbye yield\n");	
}

module_init(yield_init);
module_exit(yield_exit);


