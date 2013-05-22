/********************************************************************************
* File Name:	d_invalidate.c
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

int d_invalidate_init(void)
{
	struct dentry *dentry_pwd = current->fs->pwd.dentry; 
	struct dentry *dentry_parent = current->fs->pwd.dentry->d_parent; 
	int data2 = d_invalidate(dentry_pwd); 
	printk("<0>After \"d_invalidate\", the rensult is %d\n",data2);
 
	d_delete(dentry_pwd); 

	int data3 = d_invalidate(dentry_pwd); 
	printk("<0>After \"d_delete\", the result of \"d_invalidate\" testing is %d\n",data3); 

	int data4 = d_validate(dentry_pwd,dentry_parent); 
	printk("<0>After \"d_validate\", the result is %d\n",data4); 

	return 0;

	return 0;
}

void d_invalidate_exit(void)
{
        printk("<0>Goodbye  d_invalidate_test\n");
}



module_init(d_invalidate_init);
module_exit(d_invalidate_exit);

