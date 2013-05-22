/********************************************************************************
* File Name:	down_write_trylock.c
* Description:	第8章实例训练          
* Reference book:《Linux内核API完全参考手册》邱铁，周玉，邓莹莹 ，机械工业出版社.2010.9  
* E_mail:openlinux2100@gmail.com			                
*
********************************************************************************/

#include <linux/rwsem.h> 
#include <linux/init.h> 
#include <linux/module.h> 

MODULE_LICENSE("GPL"); 
static int __init down_write_trylock_init(void); 
static void __exit down_write_trylock_exit(void);

#define EXEC_DOWN_READ 0
struct rw_semaphore rwsem ;

int __init down_write_trylock_init(void) 
{	 
	int ret;
	init_rwsem( &rwsem );   	      //读写信号量初始化
	printk("<0>after init_rwsem, count: %ld\n",rwsem.count);
	
	if( EXEC_DOWN_READ )
		down_read( &rwsem );          //读者获取读写信号量

	ret = down_write_trylock( &rwsem );   //写者尝试获取读写信号量
	if( ret )
	{	
		printk("<0>after down_write_trylock, count: 0x%0lx\n",rwsem.count);

		up_write( &rwsem );           //写者释放读写信号量	
		printk("<0>after up_write, count: %ld\n",rwsem.count);
	}
	else
		printk("<0>down_write_trylock failed!\n");

	return 0;
}

void __exit down_write_trylock_exit(void) 
{ 
	printk("<0>exit!\n");
}

module_init(down_write_trylock_init); 
module_exit(down_write_trylock_exit);
