/********************************************************************************
* File Name:	add_preempt_count.c
* Description:	第4章实例训练          
* Reference book:《Linux内核API完全参考手册》邱铁，周玉，邓莹莹 ，机械工业出版社.2010.9  
* E_mail:openlinux2100@gmail.com			                
*
********************************************************************************/
#include <linux/module.h>
#include <linux/sched.h>
#include <linux/pid.h>
#include <linux/preempt.h>
#include <linux/list.h>
MODULE_LICENSE("GPL");

//Ä£¿éŒÓÔØº¯Êý¶šÒå
static int __init add_preempt_count_init(void)
{		
	int var=1;
	printk("<0>into add_preempt_count_init.\n");				
	printk("<0>the current pid is:%d\n",current->pid);
	struct thread_info * info=current_thread_info(); //»ñÈ¡µ±Ç°œø³ÌµÄÐÅÏ¢
	printk("<0>the value of the preempt_count is:%d\n",info->preempt_count); //ÏÔÊŸœø³ÌµÄÇÀÕŒŒÆÊýÆ÷µÄÖµ
	add_preempt_count(var); //	ÔöŒÓœø³ÌµÄÇÀÕŒŒÆÊýÆ÷µÄÖµ
	printk("<0>the new value of the preempt_count is:%d\n",info->preempt_count);//ÏÔÊŸº¯Êýadd_preempt_count()µ÷ÓÃÖ®ºóµÄœø³ÌµÄÇÀÕŒŒÆÊýÆ÷µÄÖµ
	printk("<0>out add_preempt_count_init.\n");
	return 0;
}

//Ä£¿éÐ¶ÔØº¯Êý¶šÒå
static void __exit add_preempt_count_exit(void)
{	
        printk("<0>Goodbye add_preempt_count\n");	
}

module_init(add_preempt_count_init);
module_exit(add_preempt_count_exit);


