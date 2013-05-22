/********************************************************************************
* File Name:	do_exit.c
* Description:	第4章实例训练          
* Reference book:《Linux内核API完全参考手册》邱铁，周玉，邓莹莹 ，机械工业出版社.2010.9  
* E_mail:openlinux2100@gmail.com			                
*
********************************************************************************/
#include <linux/module.h>
#include <linux/sched.h>
#include <linux/pid.h>
#include <linux/kernel.h>
MODULE_LICENSE("GPL");
//子线程函数定义
int my_function(void * argc)
{
	do_exit(0);  //退出线程
	printk("<0>in the kernel thread function!\n");	
	printk("the current pid is:%d\n",current->pid);	 //显示当前进程的PID号
	printk("out the kernel thread function\n");
	return 0;
}

//模块加载函数定义
static int __init do_exit_init(void)
{	
	int result;	
	printk("<0>into do_exit_init.\n");		
	result=kernel_thread(my_function,NULL,CLONE_KERNEL);	 //创建子线程
	struct pid * kpid=find_get_pid(result);		 //获取其新进程的描述符信息

/*显示新进程的PID号*/
	printk("<0>the pid of the find_get_pid is :%d\n",kpid->numbers[kpid->level].nr); 

    /* 显示函数kernel_thread( )函数的调用结果*/
	printk("<0>the result of the kernel_thread is :%d\n",result);
	printk("<0>out do_exit_init.\n");
	return 0;
}

//模块卸载函数定义
static void __exit do_exit_exit(void)
{
        printk("<0>Goodbye  do_exit\n");	
}

module_init(do_exit_init);
module_exit(do_exit_exit);

