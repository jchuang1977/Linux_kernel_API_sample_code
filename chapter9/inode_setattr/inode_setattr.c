/********************************************************************************
* File Name:	inode_setattr.c
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
	.ia_valid = ATTR_UID|ATTR_GID,
	.ia_uid=1000,
	.ia_gid=1000
};
int inode_setattr_init(void)
{
	struct super_block *sb; 
	sb = current->fs->pwd.dentry->d_sb; 
	struct inode *inode1; 
	inode1 = new_inode(sb); 

	int res = inode_setattr(inode1,&attr);
	printk("The returned value of \"inode_setattr\" is %d.\n",res);

	printk("The UID of new node file is %d.\n",inode1->i_uid);
	printk("The GID of new node file is %d.\n",inode1->i_gid);


	return 0;
}

void inode_setattr_exit(void)
{
        printk("Goodbye  inode_setattr_test\n");
}



module_init(inode_setattr_init);
module_exit(inode_setattr_exit);

