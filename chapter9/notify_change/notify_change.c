/********************************************************************************
* File Name:	notify_change.c
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
struct iattr attr=
{
	.ia_valid = 0
};

int notify_change_init(void)
{
	struct dentry *dentry; 
	dentry = current->fs->pwd.dentry; 

	printk("attr.ia_atime.tv_sec = %ld\n",attr.ia_atime.tv_sec);

	int res = notify_change(dentry,&attr);
	printk("The returned value of \"notify_change\" is %d.\n",res);

	printk("attr.ia_atime.tv_sec = %ld\n",attr.ia_atime.tv_sec);

	return 0;
}

void notify_change_exit(void)
{
        printk("Goodbye  notify_change_test\n");
}



module_init(notify_change_init);
module_exit(notify_change_exit);

