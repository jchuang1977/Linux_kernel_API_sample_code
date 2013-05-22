/********************************************************************************
* File Name:	class_create_destroy.c
* Description:	第10章实例训练          
* Reference book:《Linux内核API完全参考手册》邱铁，周玉，邓莹莹 ，机械工业出版社.2010.9  
* E_mail:openlinux2100@gmail.com			                
*
********************************************************************************/
/*Í·ÎÄŒþÒýÓÃ*/
#include <linux/module.h>
#include <linux/init.h>
#include <linux/device.h>

MODULE_LICENSE("GPL");			

/*È«ŸÖ±äÁ¿¶šÒå*/
struct class *mem_class;       //Éè±žÀàÖžÕë

/*Ä£¿éŒÓÔØº¯Êý¶šÒå*/
static int __init class_create_destroy_init (void)
{
	printk("<0>into the class_create_destroy_init\n");
 	mem_class = class_create(THIS_MODULE, "my_char_dev"); //ŽŽœšÉè±žÀà
	
/*
	struct lock_class_key key;
	mem_class=__class_create(THIS_MODULE,"my_char_dev",&key); //ŽŽœšÉè±žÀà
*/

  	if(IS_ERR(mem_class))     //ÅÐ¶ÏŽŽœšÊÇ·ñ³É¹Š
    	{
  	      printk("<0>Err: failed in creating class.\n");
 	      return -1;
 	}
	printk("<0>class create success\n");
	printk("<0>out the class_create_destroy_init\n");
	return 0;
}

/*Ä£¿éÐ¶ÔØº¯Êý¶šÒå*/
void __exit class_create_destroy_exit (void)
{
	printk("<0>into class_create_destroy _exit\n");
    	class_destroy(mem_class);	     //ÉŸ³ýÉè±žÀà
	printk("<0>the mem_class has been destroyed\n");
	printk("<0>out class_create_destroy_exit\n");
}

module_init(class_create_destroy_init);
module_exit(class_create_destroy_exit);
