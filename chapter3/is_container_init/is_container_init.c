/********************************************************************************
* File Name:	is_container_init.c
* Description:	第3章实例训练          
* Reference book:《Linux内核API完全参考手册》邱铁，周玉，邓莹莹 ，机械工业出版社.2010.9  
* E_mail:openlinux2100@gmail.com			                
*
********************************************************************************/
#include <linux/module.h>
#include <linux/pid.h>
#include <linux/sched.h>
MODULE_LICENSE("GPL");

//×Óœø³Ìº¯Êý¶šÒå
int my_function(void * argc)
{
	printk("<0>in the kernel thread function!\n");	
	return 0;
}

//Ä£¿éŒÓÔØº¯Êý¶šÒå
static int __init is_container_init_init(void)
{
	int result,result1;
	printk("<0> into is_container_init.\n");
	result=kernel_thread(my_function,NULL,CLONE_KERNEL);//ŽŽœšÐÂœø³Ì
	struct pid * kpid=find_get_pid(result);	//»ñÈ¡ÐÂœø³ÌµÄœø³ÌÃèÊö·û	
       struct task_struct * task=pid_task(kpid,PIDTYPE_PID);	 //»ñÈ¡ÐÂœø³ÌËùÊôÈÎÎñµÄÈÎÎñÃèÊö·û
	result1=is_container_init(task); //ÅÐ¶ÏÈÎÎñµÄœø³ÌºÅÊÇ²»ÊÇ1
	printk("<0> the kernel_thread resutl is:%d\n",result); //ÏÔÊŸº¯Êýkernel_thread()µÄ·µ»Øœá¹û
	printk("<0> the is_container_init result is:%d\n",result1); //ÏÔÊŸis_container_init()º¯ÊýµÄ·µ»Øœá¹û	
	printk("<0> out is_container_init.\n");
	return 0;
}

//Ä£¿éÐ¶ÔØº¯Êý¶šÒå
static void __exit is_container_init_exit(void)
{
        printk("<0>Goodbye  is_container_init\n");
}

module_init(is_container_init_init);
module_exit(is_container_init_exit);


