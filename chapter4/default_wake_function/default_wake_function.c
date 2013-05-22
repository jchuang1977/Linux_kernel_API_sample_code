/**c******************************************************************************
* File Name:	default_wake_function.c
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
MODULE_LICENSE("GPL");

/*È«ŸÖ±äÁ¿¶šÒå*/
static wait_queue_head_t head;  //µÈŽý¶ÓÁÐÍ·±äÁ¿
static wait_queue_t data;      //µÈŽý¶ÓÁÐÔªËØ±äÁ¿

/*×Ô¶šÒå×Óœø³ÌŽŠÀíº¯Êý*/
int my_function(void * argc)
{
	int result=-1;
	printk("<0>in the kernel thread function!\n");	
	printk("<0>the current pid is:%d\n",current->pid); //ÏÔÊŸµ±Ç°œø³ÌµÄPIDÖµ
	printk("<0>the state of the parent process before default_wake_function is:%ld\n",current->real_parent->state); //ÏÔÊŸµ±Ç°œø³ÌµÄžžœø³ÌµÄ×ŽÌ¬
	if(data.private!=NULL)
	    result=default_wake_function(&data,TASK_ALL,0,NULL);  //µ÷ÓÃº¯Êý»œÐÑŽŠÓÚË¯Ãß×ŽÌ¬µÄœø³Ì
	printk("<0>the state of the parent process after default_wake_function is:%ld\n",current->real_parent->state); //ÏÔÊŸº¯Êýµ÷ÓÃÖ®ºóžžœø³ÌµÄ×ŽÌ¬
	printk("<0>the result of the default_wake_function is:%d\n",result);		 //ÏÔÊŸº¯Êýdefault_wake_function( )µÄ·µ»Øœá¹û					
	printk("<0>out the kernel thread function\n");
	return 0;
}

/*Ä£¿éŒÓÔØº¯Êý¶šÒå*/
static int __init default_wake_function_init(void)
{	
	int result=0,result2=0;  //ŸÖ²¿±äÁ¿¶šÒå
	long result1=0;
	printk("<0>into default_wake_function_init.\n");				
	result=kernel_thread(my_function,NULL,CLONE_KERNEL);	 //ŽŽœšÐÂœø³Ì	
       init_waitqueue_head(&head); //³õÊŒ»¯µÈŽý¶ÓÁÐµÄÍ·ÔªËØ
	init_waitqueue_entry(&data,current); //ÓÃµ±Ç°œø³Ì³õÊŒ»¯µÈŽý¶ÓÁÐÔªËØ
	add_wait_queue(&head,&data);   //œ«µÈŽý¶ÓÁÐÔªËØŒÓÈëµÈŽý¶ÓÁÐ
	result1=sleep_on_timeout(&head,10);  //œ«µÈŽý¶ÓÁÐÖÃÓÚË¯Ãß×ŽÌ¬£¬ŽËË¯Ãß×ŽÌ¬ÊÇ²»¿ÉÖÐ¶ÏµÄ
	if(data.private!=NULL)	
            result2=default_wake_function(&data,TASK_ALL,0,NULL);	 //µ÷ÓÃº¯Êý»œÐÑÔÚµÈŽý¶ÓÁÐÖÐµÄœø³Ì
	printk("<0>the result of the kernel_thread is :%d\n",result); //ÏÔÊŸº¯Êýkernel_thread( )º¯ÊýµÄ·µ»Øœá¹û
	printk("<0>the result of the sleep_on_timeout is:%ld\n",result1); //ÏÔÊŸº¯Êýsleep_on_timeout( )µÄ·µ»Øœá¹û
	printk("<0>the result of the default_wake_function is:%d\n",result2); //ÏÔÊŸº¯Êýdefault_wake_function( )µÄ·µ»Øœá¹û
	printk("<0>the current pid is:%d\n",current->pid); //ÏÔÊŸµ±Ç°œø³ÌµÄPIDÖµ
	printk("<0>out default_wake_function_init.\n");
	return 0;
}

/*Ä£¿éÐ¶ÔØº¯Êý¶šÒå*/
static void __exit default_wake_function_exit(void)
{	
        printk("<0>Goodbye default_wake_function\n");	
}

/*Ä£¿éŒÓÔØŒ°Ð¶ÔØº¯Êýµ÷ÓÃ*/
module_init(default_wake_function_init);
module_exit(default_wake_function_exit);


