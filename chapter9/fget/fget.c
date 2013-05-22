/********************************************************************************
* File Name:	fget.c
* Description:	第9章实例训练          
* Reference book:《Linux内核API完全参考手册》邱铁，周玉，邓莹莹 ，机械工业出版社.2010.9  
* E_mail:openlinux2100@gmail.com			                
*
********************************************************************************/
#include <linux/module.h> 
#include <linux/init.h> 
#include <linux/file.h> 
#include <linux/fs.h>
#include <linux/fs_struct.h>
#include <linux/path.h>
#include <linux/sched.h>


MODULE_LICENSE("GPL");

int fget_init(void)
{
	struct file *fs1=fget(0); 
	printk("In the first exec: returned value of f_flags is :%d.\n",fs1->f_flags); 
	struct file *fs2=fget(2); 
	printk("In the second exec: returned value of f_flags is :%d.\n",fs2->f_flags); 


	return 0;
}

void fget_exit(void)
{
        printk("<0>Goodbye  fget_test\n");
}



module_init(fget_init);
module_exit(fget_exit);

