/********************************************************************************
* File Name:	find_get_pid.c
* Description:	第3章实例训练          
* Reference book:《Linux内核API完全参考手册》邱铁，周玉，邓莹莹 ，机械工业出版社.2010.9  
* E_mail:openlinux2100@gmail.com			                
*
********************************************************************************/
#include <linux/module.h>
#include <linux/sched.h>
#include <linux/pid.h>

MODULE_LICENSE("GPL");

//×Óœø³Ì¶ÔÓŠº¯ÊýµÄ¶šÒå
int my_function(void * argc)  
{
	printk("<0>in the kernel thread function!\n");	
	return 0;
}

//Ä£¿éŒÓÔØº¯Êý¶šÒå
static int __init find_get_pid_init(void)
{	
	int result;	
	printk("<0> into find_get_pid_init.\n");		
	result=kernel_thread(my_function,NULL,CLONE_KERNEL);  //ŽŽœšÒ»žöÐÂµÄœø³Ì
	struct pid * kpid=find_get_pid(result);	  //žùŸÝœø³ÌºÅ£¬µ÷ÓÃº¯Êý»ñÈ¡œø³ÌÃèÊö·ûÐÅÏ¢
	printk("<0>the count of the pid is :%d\n",kpid->count);   //ÏÔÊŸœø³ÌÃèÊö·ûÐÅÏ¢
	printk("<0>the level of the pid is :%d\n",kpid->level);
	printk("<0>the pid of the find_get_pid is :%d\n",kpid->numbers[kpid->level].nr); //ÏÔÊŸœø³ÌºÅ
	printk("<0>the result of the kernel_thread is :%d\n",result);  //ÏÔÊŸkernel_threadº¯Êý·µ»Øœá¹û
	printk("<0> out find_get_pid_init.\n");
	return 0;
}

//Ä£¿éÐ¶ÔØº¯Êý¶šÒå
static void __exit find_get_pid_exit(void)
{
        printk("<0>Goodbye  find_get_pid\n");	
}

module_init(find_get_pid_init);
module_exit(find_get_pid_exit);


