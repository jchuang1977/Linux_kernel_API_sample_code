/********************************************************************************
* File Name:	have_submounts.c
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

int have_submounts_init(void) 
{
	struct dentry *dentry_parent = current->fs->pwd.dentry->d_parent; 
	int data = have_submounts(dentry_parent); 
	if(data==0)
		printk("<0> Current dentry has not munt.\n"); 
	else
		printk("<0> Current dentry has munt.\n"); 
		

	return 0; 
}



void have_submounts_exit(void)
{
        printk("<0>Goodbye  have_submounts_test\n");
}



module_init(have_submounts_init);
module_exit(have_submounts_exit);

