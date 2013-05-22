/********************************************************************************
* File Name:	atomic_cmpxchg.c
* Description:	第8章实例训练          
* Reference book:《Linux内核API完全参考手册》邱铁，周玉，邓莹莹 ，机械工业出版社.2010.9  
* E_mail:openlinux2100@gmail.com			                
*
********************************************************************************/

#include <linux/types.h> 
#include <linux/init.h> 
#include <linux/module.h> 
MODULE_LICENSE("GPL"); 
static int __init atomic_cmpxchg_init(void); 
static void __exit atomic_cmpxchg_exit(void);

atomic_t my_atomic ;

int __init atomic_cmpxchg_init(void) 
{	 
	int ret, old, new;	
	atomic_set( &my_atomic, 4 );	
	old = 3;
	new = 2;
	ret = atomic_cmpxchg( &my_atomic, old, new );  //比较并替换
	printk("<0>first atomic_cmpxchg, my_atomic.counter = %d\n", atomic_read( &my_atomic));
	printk("<0>return ret = %d\n", ret);

	old = 4;
	new = 2;
	ret = atomic_cmpxchg( &my_atomic, old, new );  
	printk("<0>second atomic_cmpxchg, my_atomic.counter = %d\n", atomic_read( &my_atomic));
	printk("<0>return ret = %d\n", ret);
	
	return 0;	
}

void __exit atomic_cmpxchg_exit(void) 
{ 
	printk("<0>exit!\n");
}

module_init(atomic_cmpxchg_init); 
module_exit(atomic_cmpxchg_exit);
