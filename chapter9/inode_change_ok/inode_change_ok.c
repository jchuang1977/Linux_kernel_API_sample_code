/********************************************************************************
* File Name:	inode_change_ok.c
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

int inode_change_ok_init(void) 
{
	int data1;	
	struct iattr attr;
	struct inode *inode;
	inode = current->fs->pwd.dentry->d_inode;//从当前进程中获得inode结构体。

//判断要检验的inode结构体是否有权限被修改

	data1=inode_change_ok(inode,&attr);
	if(!data1)
	{
		printk("<0>The returned value of \"inode_change_ok\" is %d.\n",data1);
		printk("<0>The inode has the right to be set attribute.\n");
	}
	else
	{
		printk("<0>The returned value of \"inode_change_ok\" is %d.\n",data1);
		printk("<0>The inode does not have the right to be set attribute.\n");
	}
		printk("<0>The attr.ia_valid is %ud.\n",attr.ia_valid);
	




	return 0; 
}


void inode_change_ok_exit(void)
{
        printk("Goodbye  inode_change_ok_test\n");
}



module_init(inode_change_ok_init);
module_exit(inode_change_ok_exit);

