/********************************************************************************
* File Name:	complete.c
* Description:	第4章实例训练          
* Reference book:《Linux内核API完全参考手册》邱铁，周玉，邓莹莹 ，机械工业出版社.2010.9  
* E_mail:openlinux2100@gmail.com			                
*
********************************************************************************/
/*Í·ÎÄŒþÒýÓÃ*/
#include <linux/module.h>
#include <linux/sched.h>
#include <linux/pid.h>
#include <linux/wait.h>
#include <linux/completion.h>
MODULE_LICENSE("GPL");

/*È«ŸÖ±äÁ¿¶šÒå*/
static struct completion comple; //ÓÃÓÚ±£ŽæcompletionµÄ×ŽÌ¬

/*×Óœø³ÌŽŠÀíº¯Êý¶šÒå*/
int my_function(void * argc)
{
	printk("<0>in the kernel thread function!\n");	
	printk("<0>the current pid is:%d\n",current->pid); //ÏÔÊŸµ±Ç°œø³ÌµÄPIDÖµ
	printk("<0>the state of the real_parent is:%ld\n",current->real_parent->state); //ÏÔÊŸµ±Ç°œø³ÌµÄžžœø³Ì×ŽÌ¬
	printk("<0>the value of done of the comple:%d\n",comple.done); //ÏÔÊŸ×Ö¶ÎdoneµÄÖµ
	complete(&comple);	 //µ÷ÓÃº¯Êý»œÐÑœø³Ì£¬²¢žüžÄdone×Ö¶ÎµÄÖµ
	printk("<0>the value of done of the comple:%d\n",comple.done); //ÏÔÊŸº¯Êýµ÷ÓÃÖ®ºó×Ö¶ÎdoneµÄÖµ
	printk("<0>the state of the real_parent is:%ld\n",current->real_parent->state); //ÏÔÊŸº¯Êýµ÷ÓÃÖ®ºóžžœø³ÌµÄ×ŽÌ¬
	printk("<0>out the kernel thread function\n");
	return 0;
}

/*Ä£¿éŒÓÔØº¯Êý¶šÒå*/
static int __init complete_init(void)
{	
	int result;
	long left_time;
	wait_queue_t data;
	printk("<0>into complete_init.\n");	
	result=kernel_thread(my_function,NULL,CLONE_KERNEL); //ŽŽœšÐÂœø³Ì
	init_completion(&comple);	//³õÊŒ»¯È«ŸÖ±äÁ¿	 
	init_waitqueue_entry(&data,current); //ÓÃµ±Ç°œø³Ì³õÊŒ»¯µÈŽý¶ÓÁÐÔªËØ
	add_wait_queue(&(comple.wait),&data); //œ«µ±Ç°œø³ÌŒÓÈëµÈŽý¶ÓÁÐÖÐ
	left_time=sleep_on_timeout(&(comple.wait),100);	 //œ«µ±Ç°œø³ÌÖÃÓÚ²»¿ÉÖÐ¶ÏµÄµÈŽý×ŽÌ¬
	printk("<0>the return result of the kernel_thread is :%d\n",result); //ÏÔÊŸº¯Êýkernel_thread( )µÄ·µ»Øœá¹û
	printk("<0>the return result of the sleep_on_timeout is:%ld\n",left_time); //ÏÔÊŸº¯Êýsleep_on_timeout( )µÄ·µ»Øœá¹û
	printk("<0>the current pid is:%d\n",current->pid); //ÏÔÊŸµ±Ç°œø³ÌµÄPIDÖµ
	printk("<0>out complete_init.\n");
	return 0;
}

/*Ä£¿éÐ¶ÔØº¯Êý¶šÒå*/
static void __exit complete_exit(void)
{	
        printk("<0>Goodbye complete\n");	
}

/*Ä£¿éŒÓÔØŒ°Ð¶ÔØº¯Êýµ÷ÓÃ*/
module_init(complete_init);
module_exit(complete_exit);


