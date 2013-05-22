/********************************************************************************
* File Name:	d_alloc.c
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

int d_alloc_init(void)
{
	struct inode *inode; 
	inode = current->fs->pwd.dentry->d_inode; 

	struct dentry *dentry_pwd = current->fs->pwd.dentry; 
	struct dentry *dentry_parent = current->fs->pwd.dentry->d_parent; 
	struct qstr name = current->fs->pwd.dentry->d_name; 
	struct dentry *dentry; 
	dentry = d_alloc(dentry_parent,&name); 
	printk("<0>The name of current dentry is %s\n",dentry_pwd->d_name.name); 
	printk("<0>After \"d_alloc\" the name of the dentry is %s\n",dentry->d_name.name); 
 

	return 0;
}

void d_alloc_exit(void)
{
        printk("<0>Goodbye  d_alloc_test\n");
}



module_init(d_alloc_init);
module_exit(d_alloc_exit);

