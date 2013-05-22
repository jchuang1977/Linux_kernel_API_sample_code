/********************************************************************************
* File Name:	is_bad_inode.c
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

int is_bad_inode_init(void)
{
	struct inode *inode;
	inode = current->fs->pwd.dentry->d_inode;

	int resBefore = is_bad_inode(inode);
	if(resBefore == 1)
		printk("<0>It is a bad node.\n");
	else
		printk("<0>It is not a bad node.\n");;

	make_bad_inode(inode);

	int resAfter = is_bad_inode(inode);
	if(resAfter == 1)
		printk("<0>It is a bad node.\n");
	else
		printk("<0>It is not a bad node.\n");

	return 0;
}

void is_bad_inode_exit(void)
{
        printk("<0>Goodbye  is_bad_inode_test\n");
}



module_init(is_bad_inode_init);
module_exit(is_bad_inode_exit);

