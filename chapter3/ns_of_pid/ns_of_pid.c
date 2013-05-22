/********************************************************************************
* File Name:	ns_of_pid.c
* Description:	第3章实例训练          
* Reference book:《Linux内核API完全参考手册》邱铁，周玉，邓莹莹 ，机械工业出版社.2010.9  
* E_mail:openlinux2100@gmail.com			                
*
********************************************************************************/
#include <linux/module.h>
#include <linux/sched.h>
#include <linux/pid.h>
#include <linux/pid_namespace.h>
MODULE_LICENSE("GPL");

//×Óœø³Ìº¯Êý¶šÒå
int my_function(void * argc)
{
	printk("<0>in the kernel thread function\n");
	printk("<0>the current pid is:%d\n",current->pid); //ÏÔÊŸµ±Ç°œø³ÌµÄPID
	printk("<0>the current tgid is:%d\n",current->tgid);//ÏÔÊŸµ±Ç°œø³ÌµÄTGID
	return 0;
}

//Ä£¿é³õÊŒ»¯º¯Êýº¯Êý¶šÒå
static int __init ns_of_pid_init(void)
{	
	int result;
	printk("<0> into ns_of_pid_init.\n");		
	result=kernel_thread(my_function,NULL,CLONE_KERNEL); //ŽŽœšÐÂœø³Ì
	struct pid * kpid=find_get_pid(result); //»ñÈ¡ÐÂœø³ÌµÄÃèÊö·û
	printk("<0>the level of the pid is:%d\n",kpid->level); //ÏÔÊŸÐÂœø³ÌµÄlevelÖµ
	printk("<0>the pid of the pid is:%d\n",kpid->numbers[kpid->level].nr); //ÏÔÊŸÐÂœø³ÌµÄPIDÖµ
	struct pid_namespace * pid_ns = ns_of_pid(kpid); //»ñÈ¡ÐÂœø³ÌµÄÃüÃû¿ÕŒä
	printk("<0>the level of the pid_namespace is:%d\n",pid_ns->level); //ÏÔÊŸÃüÁî¿ÕŒäµÄlevelÖµ	
	printk("<0>the last_pid of the pid_namespace is:%d\n",pid_ns->last_pid);//ÏÔÊŸÃüÃû¿ÕŒäµÄlast_pidÖµ
	printk("<0>the kernel_thread result is:%d\n",result); //ÏÔÊŸº¯Êýkernel_thread()µÄ·µ»Øœá¹û
	printk("<0>the current pid is:%d\n",current->pid);    //ÏÔÊŸµ±Ç°œø³ÌµÄPID
	printk("<0>the current tgid is:%d\n",current->tgid);  //ÏÔÊŸµ±Ç°œø³ÌµÄTGID
	printk("<0> out ns_of_pid_init.\n");
	return 0;
}

//Ä£¿éÐ¶ÔØº¯Êý¶šÒå
static void __exit ns_of_pid_exit(void)
{
        printk("<0>Goodbye  ns_of_pid\n");
}

module_init(ns_of_pid_init);
module_exit(ns_of_pid_exit);


