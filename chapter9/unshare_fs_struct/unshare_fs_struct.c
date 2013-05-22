/********************************************************************************
* File Name:	unshare_fs_struct.c
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

int unshare_fs_struct_init(void)
{
	int data1 = unshare_fs_struct(); 
	printk("<0>the returned value of \"unshare_fs_struct\" is %d.\n",data1); 	

	int data2= unshare_fs_struct(); 
	printk("<0>the returned value of \"unshare_fs_struct\" is %d.\n",data2); 	

	int data3 = unshare_fs_struct(); 
	printk("<0>the returned value of \"unshare_fs_struct\" is %d.\n",data3); 


	return 0;
}

void unshare_fs_struct_exit(void)
{
        printk("<0>Goodbye  unshare_fs_struct_test\n");
}



module_init(unshare_fs_struct_init);
module_exit(unshare_fs_struct_exit);

