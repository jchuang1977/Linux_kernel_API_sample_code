/********************************************************************************
* File Name:	get_fs_type_e3.c
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

int get_fs_type_init(void)
{
	const char *name1="ext3",*name2="ext4",*name3="ecryptfs"; 
	struct file_system_type *fs1=get_fs_type(name1); 
	printk("<0>The filesystem's name is :%s\n",fs1->name);

	struct file_system_type *fs2=get_fs_type(name2); 
	printk("<0>The filesystem's name is :%s\n",fs2->name);

	struct file_system_type *fs3=get_fs_type(name3); 
	printk("<0>The filesystem's name is :%s\n",fs3->name);

	return 0;
}

void get_fs_type_exit(void)
{
        printk("<0>Goodbye  get_fs_type_test\n");
}



module_init(get_fs_type_init);
module_exit(get_fs_type_exit);

