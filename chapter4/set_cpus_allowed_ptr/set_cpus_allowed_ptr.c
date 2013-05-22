/********************************************************************************
* File Name:	set_cpus_allowed_ptr.c
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
#include <linux/cpumask.h>
MODULE_LICENSE("GPL");

/*È«ŸÖ±äÁ¿¶šÒå*/
static int cpu;  //±£Žæœø³ÌµÄµ÷¶ÈCPUÖµ

/*×Óœø³ÌŽŠÀíº¯Êý¶šÒå*/
int my_function(void * argc)
{
	int data=-1;  //±£Žæº¯Êý·µ»Øœá¹û
	cpumask_var_t mask;  //CPUÑÚÂë±äÁ¿
	alloc_cpumask_var(&mask,GFP_KERNEL);  //ÎªCPUÑÚÂë±äÁ¿¿ª±ÙÄÚŽæ¿ÕŒä
	cpumask_set_cpu(cpu,mask);   //³õÊŒ»¯CPUÑÚÂë±äÁ¿
	printk("<0>in the kernel thread function!\n");	
	printk("<0>the current pid is:%d\n",current->pid);  //ÏÔÊŸµ±Ç°œø³ÌµÄPIDÖµ
	data=set_cpus_allowed_ptr(current->real_parent,mask);  //µ÷ÓÃº¯ÊýžüžÄžžœø³ÌµÄËùÔÚCPUÖµ
       printk("<0>the return result of the set_cpus_allowed_ptr is:%d\n",data);  //ÏÔÊŸº¯Êýµ÷ÓÃ·µ»Øœá¹û					
	printk("<0>out the kernel thread function\n");
	return 0;
}

/*Ä£¿éŒÓÔØº¯Êý¶šÒå*/
static int __init set_cpus_allowed_ptr_init(void)
{	
       /*ŸÖ²¿±äÁ¿¶šÒå*/
	int result;
	long result1;
	struct thread_info * info;
	wait_queue_head_t head;
	wait_queue_t data;
	printk("<0>into set_cpus_allowed_ptr_init.\n");
	info=current_thread_info();    //»ñÈ¡µ±Ç°œø³ÌµÄœø³ÌÐÅÏ¢
	result=kernel_thread(my_function,NULL,CLONE_KERNEL);	//ŽŽœšÐÂœø³Ì
	cpu=(info->cpu==0)?1:0;    //žøÈ«ŸÖ±äÁ¿ž³Öµ£¬Ê¹ÆäÖµÓëµ±Ç°œø³ÌµÄCPUÖµ²»Í¬
	printk("<0>the cpu of the current thread is:%d\n",info->cpu);	 //ÏÔÊŸµ±Ç°œø³ÌËùÔÚCPUµÄÖµ		
       init_waitqueue_head(&head);      //³õÊŒ»¯µÈŽý¶ÓÁÐµÄÍ·ÔªËØ
	init_waitqueue_entry(&data,current);    //ÓÃµ±Ç°œø³Ì³õÊŒ»¯µÈŽý¶ÓÁÐÖÐµÄÒ»žöÔªËØ
	add_wait_queue(&head,&data);     //œ«µ±Ç°œø³ÌŒÓÈëµÈŽý¶ÓÁÐÖÐ
	result1=sleep_on_timeout(&head,100);    //œ«µÈŽý¶ÓÁÐÖÃÓÚ²»¿ÉÖÐ¶ÏµÄµÈŽý×ŽÌ¬
	printk("<0>the new cpu of the current thread is:%d\n",info->cpu);	//ÏÔÊŸµ±Ç°œø³ÌµÄÐÂµÄCPUÖµ
	printk("<0>the return result of the kernel_thread is :%d\n",result); //ÏÔÊŸº¯Êýkernel_thread( )µÄ·µ»Øœá¹û
	printk("<0>the return result of the sleep_on_timeout is:%ld\n",result1); //ÏÔÊŸº¯Êýsleep_on_timeout( )µÄ·µ»Øœá¹û
	printk("<0>the current pid is:%d\n",current->pid); //ÏÔÊŸµ±Ç°œø³ÌµÄPIDÖµ
	printk("<0>out set_cpus_allowed_ptr_init.\n");
	return 0;
}

/*Ä£¿éÐ¶ÔØº¯Êý¶šÒå*/
static void __exit set_cpus_allowed_ptr_exit(void)
{	
        printk("<0>Goodbye set_cpus_allowed_ptr\n");	
}

/*Ä£¿éŒÓÔØŒ°Ð¶ÔØº¯Êýµ÷ÓÃ*/
module_init(set_cpus_allowed_ptr_init);
module_exit(set_cpus_allowed_ptr_exit);


