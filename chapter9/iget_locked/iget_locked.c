/********************************************************************************
* File Name:	iget_locked.c
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

int iget_locked_init(void)
{
	struct super_block *sb; 
	sb = current->fs->pwd.dentry->d_sb; 
	struct inode *inode1; 
	inode1 = new_inode(sb); 
	printk("The i_ino of the new inode is %ld.\n",inode1->i_ino); 
	struct inode *inode2; 
	inode2 = iget_locked(sb,inode1->i_ino); 
	printk("After \"iget_locked\", to see the inode2's i_ino is %ld.\n",inode2->i_ino); 


	return 0;
}

void iget_locked_exit(void)
{
        printk("<0>Goodbye  iget_locked_test\n");
}



module_init(iget_locked_init);
module_exit(iget_locked_exit);

