/********************************************************************************
* File Name:	vfs_fstat.c
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
MODULE_LICENSE("GPL");

int vfs_fstat_init(void)
{
	int fd = 1,result;
	struct kstat stat;
	printk("<0>into vfs_fstat_init\n");
	result = vfs_fstat(fd,&stat); 
	printk("<0>the result of function vfs_fstat is :%d\n",result);
	printk("<0>the new value of the stat after function vfs_fstat:\n");
	printk("<0>the nlink value :%d\n",stat.nlink);
	printk("<0>the uid value :%d\n",stat.uid);
	printk("<0>the gid value :%d\n",stat.gid);
	printk("<0>the dev value :%d\n",stat.dev); 
        printk("<0>out vfs_fstat_init\n");
	return 0;
}

void vfs_fstat_exit(void)
{
        printk("<0>Goodbye  vfs_fstat\n");
}

module_init(vfs_fstat_init);
module_exit(vfs_fstat_exit);

