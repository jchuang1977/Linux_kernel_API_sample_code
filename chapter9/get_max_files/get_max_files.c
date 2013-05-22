/********************************************************************************
* File Name:	get_max_files.c
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

int get_max_files_init(void)
{
	int data = get_max_files(); 
	printk("<0>The returned value of \"get_max_files\" is:%d.\n",data);  

	return 0;
}

void get_max_files_exit(void)
{
        printk("<0>Goodbye  get_max_files_test\n");
}



module_init(get_max_files_init);
module_exit(get_max_files_exit);

