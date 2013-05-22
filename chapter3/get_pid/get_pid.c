/********************************************************************************
* File Name:	get_pid.c
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
static int __init get_pid_init(void)
{
	int result;
	printk("<0> into get_pid_init.\n");		
	result=kernel_thread(my_function,NULL,CLONE_KERNEL); //ŽŽœšÐÂœø³Ì
	struct pid * mypid=find_get_pid(result);  //»ñÈ¡ÐÂœø³ÌµÄÃèÊö·û
  
       //ÏÔÊŸº¯Êýfind_get_pid()·µ»Øœø³ÌÃèÊö·ûµÄÐÅÏ¢
	printk("<0> the count of mypid is :%d\n",mypid->count);
	printk("<0> the level of mypid is :%d\n",mypid->level);
	struct pid * mypid1 = get_pid(mypid);	 //»ñÈ¡ÐÂœø³ÌÃèÊö·û

	//ÏÔÊŸº¯Êýget_pid()·µ»Øœø³ÌÃèÊö·ûµÄÐÅÏ¢
	printk("<0> the count of mypid1 is %d\n",mypid1->count);
	printk("<0> the level of mypid1 is %d\n",mypid1->level);
	printk("<0> out get_pid_init.\n");
	return 0;
}

//Ä£¿éÐ¶ÔØº¯Êý¶šÒå
static void __exit get_pid_exit(void)
{
        printk("<0>Goodbye  get_pid\n");
}

module_init(get_pid_init);
module_exit(get_pid_exit);


