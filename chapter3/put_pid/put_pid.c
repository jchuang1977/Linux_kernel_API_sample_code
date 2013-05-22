/********************************************************************************
* File Name:	put_pid.c
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
	printk("<0>in the kernel thread function!\n");	
	return 0;
}

//Ä£¿é³õÊŒ»¯º¯Êýº¯Êý¶šÒå
static int __init put_pid_init(void)
{	
	int result;	
	printk("<0> into put_pid_init.\n");		
	result=kernel_thread(my_function,NULL,CLONE_KERNEL); //ŽŽœšÐÂœø³Ì
	struct pid * kpid=find_get_pid(result);  //»ñÈ¡ÐÂœø³ÌÃèÊö·û
	printk("<0>the count of the pid is :%d\n",kpid->count); //ÏÔÊŸÄ¿Ç°œø³ÌµÄÓÃ»§Á¿
	printk("<0>the level of the pid is :%d\n",kpid->level); //ÏÔÊŸœø³ÌµÄlevelÖµ
	printk("<0>the pid of the find_get_pid is :%d\n",kpid->numbers[kpid->level].nr); //ÏÔÊŸœø³ÌµÄPIDÖµ
	put_pid(kpid);  //µ÷ÓÃº¯ÊýÊÍ·Åœø³Ì
	printk("<0>the new value after the function put_pid:\n");
	printk("<0>the new count of the pid is:%d\n",kpid->count); //ÏÔÊŸº¯Êýµ÷ÓÃÖ®ºócountµÄÖµ
	printk("<0>the new level of the pid is:%d\n",kpid->level); //ÏÔÊŸº¯Êýµ÷ÓÃÖ®ºólevelµÄÖµ
	printk("<0>the new pid of the thread is:%d\n",kpid->numbers[kpid->level].nr); //ÏÔÊŸœø³ÌµÄPIDÖµ
	printk("<0>the result of the kernel_thread is :%d\n",result); //ÏÔÊŸº¯Êýkernel_thread()º¯ÊýµÄ·µ»ØÖµ
	printk("<0> out put_pid_init.\n");
	return 0;
}

//Ä£¿éÐ¶ÔØº¯Êý¶šÒå
static void __exit put_pid_exit(void)
{
        printk("<0>Goodbye put_pid\n");	
}

module_init(put_pid_init);
module_exit(put_pid_exit);


