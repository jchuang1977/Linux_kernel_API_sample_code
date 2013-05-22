/********************************************************************************
* File Name:	down_read.c
* Description:	第8章实例训练          
* Reference book:《Linux内核API完全参考手册》邱铁，周玉，邓莹莹 ，机械工业出版社.2010.9  
* E_mail:openlinux2100@gmail.com			                
*
********************************************************************************/

#include <linux/rwsem.h> 
#include <linux/init.h> 
#include <linux/module.h> 

MODULE_LICENSE("GPL"); 
static int __init down_read_init(void); 
static void __exit down_read_exit(void);

#define EXEC_DOWN_WRITE 1
struct rw_semaphore rwsem ;

int __init down_read_init(void) 
{	 
	init_rwsem( &rwsem );   	//读写信号量初始化
	printk("<0>after init_rwsem, count: %ld\n",rwsem.count);

	if( EXEC_DOWN_WRITE )
		down_write( &rwsem );   //写者获取读写信号量

	down_read( &rwsem );   		//读者获取读写信号量
	printk("<0>first down_read, count: %ld\n",rwsem.count);

	down_read( &rwsem );   
	printk("<0>second down_read, count: %ld\n",rwsem.count);

	while( rwsem.count != 0 )
	{
		up_read( &rwsem );     	//读者释放读写信号量
	}
	return 0;
}

void __exit down_read_exit(void) 
{ 
	printk("<0>exit!\n");
}

module_init(down_read_init); 
module_exit(down_read_exit);
