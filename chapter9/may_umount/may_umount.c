/********************************************************************************
* File Name:	may_umount.c
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

int may_umount_init(void)
{
	struct vfsmount *mnt; 
	mnt = current->fs->pwd.mnt; 

	int data5 = may_umount(mnt); 
	printk("<0>After \"may_umount\", the returned value is :%d\n",data5);


	return 0;
}

void may_umount_exit(void)
{
        printk("<0>Goodbye  may_umount_test\n");
}



module_init(may_umount_init);
module_exit(may_umount_exit);

