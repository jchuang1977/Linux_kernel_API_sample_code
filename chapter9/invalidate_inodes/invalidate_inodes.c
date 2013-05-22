/********************************************************************************
* File Name:	invalidate_inodes.c
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

int invalidate_inodes_init(void)
{
	struct super_block *sb; 
	sb = current->fs->pwd.dentry->d_sb; 
	int data = invalidate_inodes(sb); 
	printk("<0>After \"invalidate_inodes\", the returned value is %d.\n",data); 


	return 0;
}

void invalidate_inodes_exit(void)
{
        printk("<0>Goodbye  invalidate_inodes_test\n");
}



module_init(invalidate_inodes_init);
module_exit(invalidate_inodes_exit);

