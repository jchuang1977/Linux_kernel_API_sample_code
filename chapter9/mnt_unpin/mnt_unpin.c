/********************************************************************************
* File Name:	mnt_unpin.c
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
#include <linux/fdtable.h> 
#include <linux/mount.h> 
#include <linux/seq_file.h>


MODULE_LICENSE("GPL");

int mnt_unpin_init(void) 
{
	struct vfsmount *mnt; 
	mnt = current->fs->pwd.mnt; 

	printk("<0>At first, the field \"mnt->mnt_pinned\" is %d\n",mnt->mnt_pinned); 
	mnt_unpin(mnt); 
	printk("<0>When the mnt_unpin is executed, the field \"mnt->mnt_pinned\" is %d\n",mnt->mnt_pinned); 

	mnt_unpin(mnt); 
	printk("<0>When the mnt_unpin is executed again, the field \"mnt->mnt_pinned\" is %d\n",mnt->mnt_pinned); 




 	return 0; 
}

void mnt_unpin_exit(void)
{
        printk("<0>Goodbye  mnt_unpin_test\n");
}



module_init(mnt_unpin_init);
module_exit(mnt_unpin_exit);

