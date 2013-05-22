/********************************************************************************
* File Name:	put_unused_fd.c
* Description:	第9章实例训练          
* Reference book:《Linux内核API完全参考手册》邱铁，周玉，邓莹莹 ，机械工业出版社.2010.9  
* E_mail:openlinux2100@gmail.com			                
*
********************************************************************************/
#include <linux/init.h> 
#include <linux/module.h> 
#include <linux/fs.h> 
#include <linux/path.h> 
#include <linux/mount.h> 
#include <linux/dcache.h> 
#include <linux/sched.h> 
#include <linux/fs_struct.h> 
#include <linux/file.h> 
#include <linux/fdtable.h>

MODULE_LICENSE("GPL");


int put_unused_fd_init(void)
{
	struct files_struct *fs = current->files; 
	printk("Current  \"next_fd\" is :%d\n",fs->next_fd); 
	put_unused_fd(2); 
	printk("After setting \"fd=2\", \"next_fd\" is :%d\n",fs->next_fd); 
	put_unused_fd(4); 
	printk("After setting \"fd=4\", \"next_fd\" is :%d\n",fs->next_fd); 

	return 0;
}

void put_unused_fd_exit(void)
{
        printk("<0>Goodbye  put_unused_fd_test\n");
}



module_init(put_unused_fd_init);
module_exit(put_unused_fd_exit);

