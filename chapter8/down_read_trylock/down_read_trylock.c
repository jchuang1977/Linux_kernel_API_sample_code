/********************************************************************************
* File Name:	down_read_trylock.c
* Description:	第8章实例训练          
* Reference book:《Linux内核API完全参考手册》邱铁，周玉，邓莹莹 ，机械工业出版社.2010.9  
* E_mail:openlinux2100@gmail.com			                
*
********************************************************************************/

#include <linux/rwsem.h> 
#include <linux/init.h> 
#include <linux/module.h> 

MODULE_LICENSE("GPL"); 
static int __init down_read_trylock_init(void); 
static void __exit down_read_trylock_exit(void);

#define EXEC_DOWN_WRITE 1
struct rw_semaphore rwsem ;

int __init down_read_trylock_init(void) 
{
	int ret;
	init_rwsem( &rwsem );   	//读写信号量初始化
	printk("<0>after init_rwsem, count: %ld\n",rwsem.count);

	if( EXEC_DOWN_WRITE )
		down_write( &rwsem );   //写者获取读写信号量

	ret = down_read_trylock( &rwsem ); 	//读者尝试获取读写信号量
	if(ret)
	{
		printk("<0>first down_read_trylock, count: %ld\n",rwsem.count);
		ret = down_read_trylock( &rwsem );   
		printk("<0>second down_read_trylock, count: %ld\n",rwsem.count);

		while( rwsem.count != 0 )
		{
			up_read( &rwsem );     	//读者释放读写信号量
		}
	}	
	else
		printk("<0>down_read_trylock failed!\n");

	return 0;
}

void __exit down_read_trylock_exit(void) 
{ 
	printk("<0>exit!\n");
}

module_init(down_read_trylock_init); 
module_exit(down_read_trylock_exit);
