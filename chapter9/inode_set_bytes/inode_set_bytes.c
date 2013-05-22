/********************************************************************************
* File Name:	inode_set_bytes.c
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

int inode_set_bytes_init(void)
{
	struct dentry *dentry; 
	struct inode *inode; 
	dentry = current->fs->pwd.dentry; 
	inode = dentry->d_inode; 

	unsigned long data6 = inode_get_bytes(inode); 
	printk("<0>The result of \"inode_get_bytes\" is :%ld\n",data6);  
	 
	loff_t num1 = 8192; 
	inode_set_bytes(inode,num1); 
	printk("<0>Exec \"inode_set_bytes\" begins:\n"); 
	printk("<0>After Exec, The result is :%ld\n",inode_get_bytes(inode)); 

	return 0;
}

void inode_set_bytes_exit(void)
{
        printk("<0>Goodbye  inode_set_bytes_test\n");
}



module_init(inode_set_bytes_init);
module_exit(inode_set_bytes_exit);

