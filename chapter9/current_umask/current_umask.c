/********************************************************************************
* File Name:	current_umask.c
* Description:	第9章实例训练          
* Reference book:《Linux内核API完全参考手册》邱铁，周玉，邓莹莹 ，机械工业出版社.2010.9  
* E_mail:openlinux2100@gmail.com			                
*
********************************************************************************/

#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/fs_struct.h>
#include <linux/path.h>
#include <linux/sched.h>

MODULE_LICENSE("GPL");

static int current_umask_init_module(void) 
{ 
	int umask = current_umask(); 
	printk("<0>The current umask is 00%o\n",umask); 
	printk("<0>1111111111111111The current umask is 00%o\n",S_IRUSR); 
	return 0;
	
}


void current_umask_exit_module(void)
{
        printk("<0>Goodbye  current_umask_test\n");
}



module_init(current_umask_init_module);
module_exit(current_umask_exit_module);

