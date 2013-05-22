/********************************************************************************
* File Name:	__mnt_is_readonly.c
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

int __mnt_is_readonly_init(void)
{
	int data1,data2;
	struct vfsmount *mnt; 
	mnt = current->fs->pwd.mnt; 
	data1=__mnt_is_readonly(mnt);
	if(data1)
		printk("<0> Current mntfs is read only. \n"); 
	else
		printk("<0> Current mntfs is not read only. \n"); 

  	data2=mnt_want_write(mnt);
	if(data2)
		printk("<0> Current mntfs is en_write. \n"); 
	else
		printk("<0> Current mntfs is not en_write. \n"); 

 	return 0;
}


void __mnt_is_readonly_exit(void)
{
        printk("<0>Goodbye  __mnt_is_readonly_test\n");
}



module_init(__mnt_is_readonly_init);
module_exit(__mnt_is_readonly_exit);

