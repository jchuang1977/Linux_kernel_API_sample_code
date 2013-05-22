/********************************************************************************
* File Name:	dput.c
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

int dput_init(void)
{
	struct dentry *dentry_pwd = current->fs->pwd.dentry; 
	printk("Before \"dput\", the d_count of current dentry is %d\n",dentry_pwd->d_count); 
	dput(dentry_pwd); 
	printk("After \"dput\", the d_count of current dentry is %d\n",dentry_pwd->d_count); 
 

	return 0;
}

void dput_exit(void)
{
        printk("<0>Goodbye  dput_test\n");
}



module_init(dput_init);
module_exit(dput_exit);

