/********************************************************************************
* File Name:	find_inode_number.c
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

int find_inode_number_init(void)
{
	struct inode *inode; 
	inode = current->fs->pwd.dentry->d_inode; 
	struct qstr name = current->fs->pwd.dentry->d_name; 
	struct dentry *dentry_parent = current->fs->pwd.dentry->d_parent; 
	printk("<0>The i_ino of the current dentry's inode is %ld\n",inode->i_ino);
	ino_t data1 = find_inode_number(dentry_parent,&name); 
	printk("<0>After \"find_inode_number\",the result is %ld\n",data1);	  

	return 0;
}

void find_inode_number_exit(void)
{
        printk("<0>Goodbye  find_inode_number_test\n");
}



module_init(find_inode_number_init);
module_exit(find_inode_number_exit);

