/********************************************************************************
* File Name:	vfs_getattr.c
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
struct kstat stat= 
{ 
	.nlink = 10, 
};
int vfs_getattr_init(void)
{
	struct dentry *dentry; 
	struct vfsmount *vfs; 
	struct inode *inode; 
	 
	dentry = current->fs->pwd.dentry; 
	vfs = current->fs->pwd.mnt; 
	inode = dentry->d_inode; 

	printk("<0>Current \"vfs_getattr\",stat.dev = %d\n",stat.dev);
	printk("<0>Current \"vfs_getattr\",stat.ino = %d\n",stat.ino);
	printk("<0>Current\"vfs_getattr\",stat.mode = %d\n",stat.mode);
	printk("<0>Current \"vfs_getattr\",stat.nlink = %d\n",stat.nlink);
	printk("<0>Current \"vfs_getattr\",stat.uid = %d\n",stat.uid);
	printk("<0>Current \"vfs_getattr\",stat.gid = %d\n",stat.gid);
	
	
	printk("<0>inode->i_sb->s_dev = %d\n",inode->i_sb->s_dev);
	printk("<0>inode->i_ino = %d\n",inode->i_ino);
	printk("<0>inode->i_mode = %d\n",inode->i_mode);
	printk("<0>inode->i_nlink = %d\n",inode->i_nlink);
	printk("<0>inode->i_uid = %d\n",inode->i_uid);
	printk("<0>inode->i_gid = %d\n",inode->i_gid);
 
	printk("<0>The returned result of  \"vfs_getattr\" is :%d\n",vfs_getattr(vfs,dentry,&stat));

	printk("<0>After \"vfs_getattr\",stat.dev = %d\n",stat.dev);
	printk("<0>After \"vfs_getattr\",stat.ino = %d\n",stat.ino);
	printk("<0>After \"vfs_getattr\",stat.mode = %d\n",stat.mode);
	printk("<0>After \"vfs_getattr\",stat.nlink = %d\n",stat.nlink);
	printk("<0>After \"vfs_getattr\",stat.uid = %d\n",stat.uid);
	printk("<0>After \"vfs_getattr\",stat.gid = %d\n",stat.gid);

	return 0;
}


void vfs_getattr_exit(void)
{
        printk("<0>Goodbye  vfs_getattr_test\n");
}



module_init(vfs_getattr_init);
module_exit(vfs_getattr_exit);

