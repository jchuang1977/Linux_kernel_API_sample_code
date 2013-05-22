/********************************************************************************
* File Name:	generic_fillattr.c
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

struct kstat stat= 
{ 
	.nlink = 0, 
};
int generic_fillattr_init(void)
{
	struct dentry *dentry;  
	struct inode *inode; 
	 
	dentry = current->fs->pwd.dentry; 
	inode = dentry->d_inode; 

	printk("<0>Before \"generic_fillattr\",the kstat.nlink is :%d\n",stat.nlink);
	generic_fillattr(inode,&stat); 
 
	printk("<0>After \"generic_fillattr\",the kstat.nlink is :%d\n",stat.nlink); 


	return 0;
}

void generic_fillattr_exit(void)
{
        printk("<0>Goodbye  generic_fillattr_test\n");
}



module_init(generic_fillattr_init);
module_exit(generic_fillattr_exit);

