/********************************************************************************
* File Name:	get_super.c
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

int get_super_init(void)
{
	struct super_block *sb; 
	sb =current->fs->pwd.dentry->d_sb; 
	//int data = fsync_super(sb); 
	//printk("<0>After \"fsync_super\", the returned value is :%d.\n",data); 

	struct block_device *bdev = sb->s_bdev;	 
	printk("<0>the Superblock's dev number is %d.\n",sb->s_dev); 
	struct  super_block *sb1; 
	sb1 = get_super(bdev); 
	printk("<0>After the \"get_super\",the superblock's dev number is %d.\n",sb->s_dev); 	
 

	return 0;
}

void get_super_exit(void)
{
        printk("<0>Goodbye  get_super_test\n");
}



module_init(get_super_init);
module_exit(get_super_exit);

