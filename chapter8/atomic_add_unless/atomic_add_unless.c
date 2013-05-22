/********************************************************************************
* File Name:	atomic_add_unless.c
* Description:	第8章实例训练          
* Reference book:《Linux内核API完全参考手册》邱铁，周玉，邓莹莹 ，机械工业出版社.2010.9  
* E_mail:openlinux2100@gmail.com			                
*
********************************************************************************/

#include <linux/types.h> 
#include <linux/init.h> 
#include <linux/module.h> 
MODULE_LICENSE("GPL"); 
static int __init atomic_add_unless_init(void); 
static void __exit atomic_add_unless_exit(void);

atomic_t my_atomic ;

int __init atomic_add_unless_init(void) 
{	 
	int ret, a;
	atomic_set( &my_atomic, 10 );	
	a = 2;
	ret = atomic_add_unless( &my_atomic, a, 10 );  //如果原子类型的变量my_atomic不为10,则将其原子地增加a
	printk("<0>first atomic_add_unless, my_atomic.counter = %d\n", atomic_read( &my_atomic));
	printk("<0>return ret = %d\n", ret);

	atomic_set( &my_atomic, 4 );	
	a = 2;
	ret = atomic_add_unless( &my_atomic, a, 10 );  
	printk("<0>first atomic_add_unless, my_atomic.counter = %d\n", atomic_read( &my_atomic));
	printk("<0>return ret = %d\n", ret);
	
	return 0;	
}

void __exit atomic_add_unless_exit(void) 
{ 
	printk("<0>exit!\n");
}

module_init(atomic_add_unless_init); 
module_exit(atomic_add_unless_exit);
