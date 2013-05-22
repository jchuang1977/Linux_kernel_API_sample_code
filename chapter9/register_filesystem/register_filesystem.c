/********************************************************************************
* File Name:	register_filesystem.c
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

int register_filesystem_init(void)
{
	const char *name="ext4"; 
	struct file_system_type *fs=get_fs_type(name);  
	
	if(register_filesystem(fs) == 0)
	{ 
		printk("<0>Register filesystem successfully!\n"); 
		printk("<0>The name of registered filesystem is %s.\n",fs->name);
	}
	else
	{
		printk("<0>Filesystem register failed!\n");
	}

	if( unregister_filesystem(fs) == 0) 
	{
		printk("<0>Unregister filesystem sucessfully!\n"); 
		printk("<0>The name of registered filesystem is %s.\n",fs->name);
	}
	else
	{
		printk("<0>Filesystem unregister failed!\n");
	} 

	return 0;
}


void register_filesystem_exit(void)
{
        printk("<0>Goodbye  register_filesystem_test\n");
}



module_init(register_filesystem_init);
module_exit(register_filesystem_exit);

