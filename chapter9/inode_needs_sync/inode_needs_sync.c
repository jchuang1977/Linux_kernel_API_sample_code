/********************************************************************************
* File Name:	inode_needs_sync.c
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

int inode_needs_sync_init(void)
{
	struct super_block *sb; 
	sb = current->fs->pwd.dentry->d_sb;
	struct inode *inode1; 
	inode1 = new_inode(sb);
	int data1 = inode_needs_sync(inode1); 
	printk("After \"inode_needs_sync\", the returned value is %d.\n",data1); 

	struct dentry *dentry; 
	struct inode *inode2; 

	dentry = current->fs->pwd.dentry; 
	inode2 = dentry->d_inode; 

	int data2 = inode_needs_sync(inode2); 
	data2 = inode_needs_sync(inode2); 
	printk("After \"inode_needs_sync\", the returned value is %d.\n",data2); 


	return 0;
}

void inode_needs_sync_exit(void)
{
        printk("<0>Goodbye  inode_needs_sync_test\n");
}



module_init(inode_needs_sync_init);
module_exit(inode_needs_sync_exit);

