/********************************************************************************
* File Name:	d_find_alias.c
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

int d_find_alias_init(void)
{
	struct inode *inode; 
	inode = current->fs->pwd.dentry->d_inode; 
	struct dentry *dentry_pwd = current->fs->pwd.dentry; 
	printk("<0>The name of current dentry is %s\n",dentry_pwd->d_name.name); 
	struct dentry *dentry_alias; 
	dentry_alias = d_find_alias(inode); 
	printk("<0>After \"d_find_alias\",The name of current dentry is %s\n",dentry_alias->d_name.name); 
 

	return 0;
}

void d_find_alias_exit(void)
{
        printk("<0>Goodbye  d_find_alias_test\n");
}



module_init(d_find_alias_init);
module_exit(d_find_alias_exit);

