/********************************************************************************
* File Name:	init_waitqueue_entry.c
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

/*×Óœø³ÌŽŠÀíº¯Êý¶šÒå*/
int my_function(void * argc)
{
	printk("<0>in the kernel thread function!\n");	
	printk("<0>the current pid is:%d\n",current->pid); //ÏÔÊŸµ±Ç°œø³ÌPIDÖµ
	printk("<0>out the kernel thread function\n");
	return 0;
}

/*Ä£¿éŒÓÔØº¯Êý¶šÒå*/
static int __init init_waitqueue_entry_init(void)
{	
	//ŸÖ²¿±äÁ¿¶šÒå
	int result;	
	wait_queue_t data;	

	printk("<0>into init_waitqueue_entry_init.\n");
	
	/*ŽŽœš1žöÐÂœø³Ì*/				
	result=kernel_thread(my_function,NULL,CLONE_KERNEL);

	/*»ñÈ¡ÐÂœø³ÌµÄœø³ÌÃèÊö·ûÐÅÏ¢*/
	struct pid * kpid = find_get_pid(result);
	struct task_struct * task = pid_task(kpid,PIDTYPE_PID);
	
	if(data.private==NULL||data.func==NULL)
	{
		printk("<0>the data has not been initialized\n");	
	}	

	 /*ÓÃÐÂœø³Ì³õÊŒ»¯µÈŽý¶ÓÁÐÔªËØ*/
	init_waitqueue_entry(&data,task);
	if(data.private==task && data.func!=NULL)
	{
		printk("<0>the data has been initialized\n");
		printk("<0>the flags of the data is:%d\n",data.flags);
	}	
	else
	{
		printk("<0>the data has not been initialized\n");
	}
	
	/*ÏÔÊŸŽŽœšÐÂœø³ÌµÄœø³ÌºÅ*/
	printk("<0>the result of the kernel_thread is :%d\n",result); 
	printk("<0>the current pid is:%d\n",current->pid);//ÏÔÊŸµ±Ç°œø³ÌµÄPIDÖµ
	printk("<0>out init_waitqueue_entry_init.\n");
	return 0;
}

/*Ä£¿éÐ¶ÔØº¯Êý¶šÒå*/
static void __exit init_waitqueue_entry_exit(void)
{	
        printk("<0>Goodbye init_waitqueue_entry\n");	
}

/*Ä£¿éŒÓÔØŒ°Ð¶ÔØº¯Êýµ÷ÓÃ*/
module_init(init_waitqueue_entry_init);
module_exit(init_waitqueue_entry_exit);


