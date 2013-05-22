/********************************************************************************
* File Name:	inode_get_bytes.c
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

int inode_get_bytes_init(void)
{
	struct dentry *dentry; 
	struct inode *inode; 
	dentry = current->fs->pwd.dentry; 
	inode = dentry->d_inode; 


	printk("<0>The result of  \"inode->i_blocks\" is :%ld\n",inode->i_blocks); 

	printk("<0>The result of  \"inode->i_bytes\" is :%ld\n",inode->i_bytes); 

	unsigned long data1 = inode_get_bytes(inode); 
	printk("<0>The result of  \"inode_get_bytes\" is :%ld\n",data1); 

	return 0;
}

void inode_get_bytes_exit(void)
{
        printk("<0>Goodbye  inode_get_bytes_test\n");
}



module_init(inode_get_bytes_init);
module_exit(inode_get_bytes_exit);

