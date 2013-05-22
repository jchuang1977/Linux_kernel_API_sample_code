/********************************************************************************
* File Name:	mnt_pin.c
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

int mnt_pin_init(void)
{
	struct vfsmount *mnt; 
	mnt = current->fs->pwd.mnt; 

	printk("<0>At first, the field \"mnt->mnt_pinned\" is %d\n",mnt->mnt_pinned); 
	mnt_pin(mnt); 
	printk("<0>When the mnt_pin is executed, the field \"mnt->mnt_pinned\" is %d\n",mnt->mnt_pinned); 

	mnt_pin(mnt); 
	printk("<0>When the mnt_pin is executed again, the field \"mnt->mnt_pinned\" is %d\n",mnt->mnt_pinned); 

	return 0;
}

void mnt_pin_exit(void)
{
        printk("<0>Goodbye  mnt_pin_test\n");
}



module_init(mnt_pin_init);
module_exit(mnt_pin_exit);

