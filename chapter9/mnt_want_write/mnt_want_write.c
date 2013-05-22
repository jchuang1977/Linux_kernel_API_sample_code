/********************************************************************************
* File Name:	mnt_want_write.c
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

int mnt_want_write_init(void)
{
	struct vfsmount *mnt; 
	mnt = current->fs->pwd.mnt; 

	int data2 = mnt_want_write(mnt); 
	printk("After \"mnt_want_write\", the returned value is :%d\n",data2);
 

	return 0;
}

void mnt_want_write_exit(void)
{
        printk("<0>Goodbye  mnt_want_write_test\n");
}



module_init(mnt_want_write_init);
module_exit(mnt_want_write_exit);

