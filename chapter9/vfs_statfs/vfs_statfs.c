/********************************************************************************
* File Name:	vfs_statfs.c
* Description:	第9章实例训练          
* Reference book:《Linux内核API完全参考手册》邱铁，周玉，邓莹莹 ，机械工业出版社.2010.9  
* E_mail:openlinux2100@gmail.com			                
*
********************************************************************************/
#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/statfs.h>
#include <linux/sched.h>
#include <linux/fs_struct.h>

MODULE_LICENSE("GPL");	 
 
static int vfs_statfs_init(void)
{
	int result=0,i=0;
	struct dentry *dentry=NULL;	 
       static struct kstatfs buf;
	printk("<0>into vfs_statfs_init\n");
	dentry = current->fs->pwd.dentry; 
	printk("<0>the f_bsize is :%ld\n",buf.f_bsize);
	printk("<0>the f_frsize is :%ld\n",buf.f_frsize);
	printk("<0>the f_type is :%ld\n",buf.f_type);
	printk("<0>the f_blocks is :%lld\n",buf.f_blocks);
	printk("<0>the f_bfree is :%lld\n",buf.f_bfree);
	printk("<0>the f_bavail is :%lld\n",buf.f_bavail);
	printk("<0>the f_files is :%lld\n",buf.f_files);
	printk("<0>the f_ffree is :%lld\n",buf.f_ffree);
	printk("<0>the f_fsid is :%ld\n",buf.f_fsid);
	printk("<0>the f_namelen is :%ld\n",buf.f_namelen);
	for(i=0;i<5;i++)
		printk("<0>the f_spare[%d] is :%ld\n",i,buf.f_spare[i]);	

	result= vfs_statfs(dentry,&buf); 

	printk("<0>The result of function vfs_statfs is :%d\n",result);
	printk("<0>the new value of the buf after vfs_statfs:\n");
	printk("<0>the new f_bsize is :%ld\n",buf.f_bsize);
	printk("<0>the new f_frsize is :%ld\n",buf.f_frsize);
	printk("<0>the new f_type is :%ld\n",buf.f_type);
	printk("<0>the new f_blocks is :%lld\n",buf.f_blocks);
	printk("<0>the new f_bfree is :%lld\n",buf.f_bfree);
	printk("<0>the new f_bavail is :%lld\n",buf.f_bavail);
	printk("<0>the new f_files is :%lld\n",buf.f_files);
	printk("<0>the new f_ffree is :%lld\n",buf.f_ffree);
	printk("<0>the new f_fsid is :%ld\n",buf.f_fsid);
	printk("<0>the new f_namelen is :%ld\n",buf.f_namelen);
	for(i=0;i<5;i++)
		printk("<0>the new f_spare[%d] is :%ld\n",i,buf.f_spare[i]);	
	printk("<0>out vfs_statfs_init\n");
	return 0;
}	 

 
static void vfs_statfs_exit(void)
{
        printk("<0>Goodbye vfs_statfs\n");
}	 

module_init(vfs_statfs_init);
module_exit(vfs_statfs_exit);	 
