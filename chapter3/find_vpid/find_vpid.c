/********************************************************************************
* File Name:	find_vpid.c
* Description:	第3章实例训练          
* Reference book:《Linux内核API完全参考手册》邱铁，周玉，邓莹莹 ，机械工业出版社.2010.9  
* E_mail:openlinux2100@gmail.com			                
*
********************************************************************************/
#include <linux/module.h>
#include <linux/sched.h>
#include <linux/pid.h>
MODULE_LICENSE("GPL");

//×Óœø³Ì¶ÔÓŠº¯Êý¶šÒå
int my_function(void * argc)
{
	printk("<0>in the kernel thread function!\n");	
	return 0;
}

//Ä£¿éŒÓÔØº¯Êý¶šÒå
static int __init find_vpid_init(void)
{	
	int result;	
	printk("<0> into find_vpid_init.\n");		
	result=kernel_thread(my_function,NULL,CLONE_KERNEL); //ŽŽœšÒ»žöÐÂµÄœø³Ì
	struct pid *vpid =find_vpid(result);  //ÖŽÐÐº¯Êýfind_vpid()»ñÈ¡œø³ÌÃèÊö·û
       
       //ÏÔÊŸœø³ÌÃèÊö·ûÐÅÏ¢
       printk("<0>the count of the pid is :%d\n",vpid->count);
	printk("<0>the level of the pid is :%d\n",vpid->level);
       //ÏÔÊŸ×Óœø³Ìœø³ÌºÅ
	printk("<0>the pid of the find_vpid is :%d\n",vpid->numbers[vpid->level].nr);
       //ÏÔÊŸº¯Êýkernel_thread()º¯ÊýÖŽÐÐœá¹û
	printk("<0>the result of the kernel_thread is :%d\n",result);
	printk("<0> out find_vpid_init.\n");
	return 0;
}

//Ä£¿éÐ¶ÔØº¯Êý¶šÒå
static void __exit find_vpid_exit(void)
{
        printk("<0>Goodbye  find_vpid\n");	
}

module_init(find_vpid_init);
module_exit(find_vpid_exit);


