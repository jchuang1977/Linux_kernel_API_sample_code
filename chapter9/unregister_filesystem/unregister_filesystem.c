/********************************************************************************
* File Name:	unregister_filesystem.c
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

int unregister_filesystem_init(void)
{
	const char *name="ext2"; 
	struct file_system_type *fs=get_fs_type(name);  

	int data1 = unregister_filesystem(fs); 
	printk("<0>Unregister filesystem:\n"); 
	printk("<0>This result is :%d\n",data1); 

	int data = register_filesystem(fs); 
	printk("<0>Register filesystem:\n"); 
	printk("<0>This result is :%d\n",data);

	return 0;
}

void unregister_filesystem_exit(void)
{
        printk("<0>Goodbye  unregister_filesystem_test\n");
}



module_init(unregister_filesystem_init);
module_exit(unregister_filesystem_exit);

