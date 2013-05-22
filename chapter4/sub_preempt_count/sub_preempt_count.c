/********************************************************************************
* File Name:	sub_preempt_count.c
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
static int __init sub_preempt_count_init(void)
{		
	int var=1;
	printk("<0>into sub_preempt_count_init.\n");				
	printk("<0>the current pid is:%d\n",current->pid); //ÏÔÊŸµ±Ç°œø³ÌµÄPID
	struct thread_info * info=current_thread_info(); //»ñÈ¡µ±Ç°œø³ÌµÄÄÚºË¶ÑÕ»±£ŽæµÄÐÅÏ¢
	printk("<0>the value of the preempt_count is:%d\n",info->preempt_count); //ÏÔÊŸ×Ö¶Îpreempt_countµÄÖµ
       add_preempt_count(var);  //ÔöŒÓ×Ö¶Îpreempt_countµÄÖµ
	printk("<0>the new value of the preempt_count is:%d\n",info->preempt_count); //ÏÔÊŸº¯Êýadd_preempt_count()ÖŽÐÐÍêÖ®ºó×Ö¶Îpreempt_countµÄÖµ
	sub_preempt_count(var);  //ŒõÉÙ×Ö¶Îpreempt_countµÄÖµ
	printk("<0>the new value of the preempt_count is:%d\n",info->preempt_count); //ÏÔÊŸº¯Êýsub_preempt_count()ÖŽÐÐÍêÖ®ºó×Ö¶Îpreempt_countµÄÖµ
	printk("<0>out sub_preempt_count_init.\n");
	return 0;
}

//Ä£¿éÐ¶ÔØº¯Êý¶šÒå
static void __exit sub_preempt_count_exit(void)
{	
        printk("<0>Goodbye sub_preempt_count\n");	
}

module_init(sub_preempt_count_init);
module_exit(sub_preempt_count_exit);


