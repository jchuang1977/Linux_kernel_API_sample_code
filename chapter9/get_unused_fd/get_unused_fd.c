/********************************************************************************
* File Name:	get_unused_fd.c
* Description:	第9章实例训练          
* Reference book:《Linux内核API完全参考手册》邱铁，周玉，邓莹莹 ，机械工业出版社.2010.9  
* E_mail:openlinux2100@gmail.com			                
*
********************************************************************************/
#include <linux/init.h>
#include <linux/module.h>
#include <linux/file.h> 
#include <linux/fs.h>
#include <linux/fs_struct.h>
#include <linux/path.h>
#include <linux/sched.h>

MODULE_LICENSE("GPL");

int get_unused_fd_init(void)
{
	int data1 = get_unused_fd(); 
	printk("<0>First returned value of \"get_unused_fd\" is %d.\n",data1);  

	int data2 = get_unused_fd(); 
	printk("<0>Second returned value of \"get_unused_fd\" is %d.\n",data2);  
	int data3 = get_unused_fd(); 
	printk("<0>Third returned value of \"get_unused_fd\" is %d.\n",data3);  

	return 0;
}



void get_unused_fd_exit(void)
{
        printk("<0>Goodbye  get_unused_fd_test\n");
}



module_init(get_unused_fd_init);
module_exit(get_unused_fd_exit);

