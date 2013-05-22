/********************************************************************************
* File Name:	new_inode.c
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

int new_inode_init(void)
{
	struct super_block *sb; 
	sb = current->fs->pwd.dentry->d_sb; 
	struct inode *inode1,*inode2; 
	inode1 = new_inode(sb); 
	printk("<0>The i_ino of the new inode1 is %ld.\n",inode1->i_ino); 
	inode2 = new_inode(sb); 
	printk("<0>The i_ino of the new inode2 is %ld.\n",inode2->i_ino); 

	return 0;
}

void new_inode_exit(void)
{
        printk("<0>Goodbye  new_inode_test\n");
}



module_init(new_inode_init);
module_exit(new_inode_exit);

