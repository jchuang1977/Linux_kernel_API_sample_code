/********************************************************************************
* File Name:	get_empty_filp.c
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

int get_empty_filp_init(void)
{
	struct file *fs1=get_empty_filp(); 
	if(fs1!=NULL) 
		{
		printk("<0> The fs1 is an unused file structure!\n"); 
		printk("<0> The address of fs1 space is: 0x%x\n", (unsigned int) fs1);
		}
	else 
		printk("<0> The fs1 is not an unused file structure!\n"); 

	
	struct file *fs2=get_empty_filp(); 
	if(fs2!=NULL) 
		{
		printk("<0> The fs2 is an unused file structure!\n"); 
		printk("<0> The address of fs2 space is: 0x%x\n", (unsigned int) fs2);
		}
	else 
		printk("<0> The fs2 is not an unused file structure!\n"); 
	return 0; 
}


void get_empty_filp_exit(void)
{
        printk("<0>Goodbye  get_empty_filp_test\n");
}



module_init(get_empty_filp_init);
module_exit(get_empty_filp_exit);

