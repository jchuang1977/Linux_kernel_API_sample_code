/********************************************************************************
* File Name:	pid_nr.c
* Description:	第3章实例训练          
* Reference book:《Linux内核API完全参考手册》邱铁，周玉，邓莹莹 ，机械工业出版社.2010.9  
* E_mail:openlinux2100@gmail.com			                
*
********************************************************************************/
#include <linux/module.h>
#include <linux/sched.h>
#include <linux/pid.h>
MODULE_LICENSE("GPL");

//×Óœø³Ìº¯Êý¶šÒå
int my_function(void * argc)
{
	printk("<0>in the kernel thread function\n");
	printk("<0>the current pid is:%d\n",current->pid);  //ÏÔÊŸµ±Ç°œø³ÌµÄœø³ÌºÅ
	printk("<0>the current tgid is:%d\n",current->tgid); //ÏÔÊŸµ±Ç°œø³ÌµÄÏß³Ì×éºÅ
	printk("<0>out the kernel thread function\n");
	return 0;
}

//Ä£¿é³õÊŒ»¯º¯Êýº¯Êý¶šÒå
static int __init pid_nr_init(void)
{	
	int result;
	printk("<0> into pid_nr_init.\n");		
	result=kernel_thread(my_function,NULL,CLONE_KERNEL); //ŽŽœšÐÂœø³Ì
	struct pid * kpid=find_get_pid(result);   //»ñÈ¡ÐÂœø³ÌµÄÃèÊö·û
	printk("<0>the level of the pid is:%d\n",kpid->level); //ÏÔÊŸœø³ÌÃèÊö·ûµÄlevelµÄÖµ
	printk("<0>the pid of the pid is:%d\n",kpid->numbers[kpid->level].nr); //ÏÔÊŸœø³ÌµÄœø³ÌºÅ
	int nr = pid_nr(kpid); //»ñÈ¡œø³ÌÃèÊö·ûµÄÈ«ŸÖœø³ÌºÅ
	printk("<0>the pid_nr result is:%d\n",nr); //ÏÔÊŸÈ«ŸÖœø³ÌºÅ
	printk("<0>the current pid is:%d\n",current->pid); //ÏÔÊŸµ±Ç°œø³ÌµÄœø³ÌºÅ
	printk("<0>the current tgid is:%d\n",current->tgid); //ÏÔÊŸµ±Ç°œø³ÌµÄÏß³Ì×éºÅ
	printk("<0> out pid_nr_init.\n");
	return 0;
}

//Ä£¿éÐ¶ÔØº¯Êý¶šÒå
static void __exit pid_nr_exit(void)
{
        printk("<0>Goodbye  pid_nr\n");
}

module_init(pid_nr_init);
module_exit(pid_nr_exit);


