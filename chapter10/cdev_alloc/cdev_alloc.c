/********************************************************************************
* File Name:	cdev_alloc.c
* Description:	第10章实例训练          
* Reference book:《Linux内核API完全参考手册》邱铁，周玉，邓莹莹 ，机械工业出版社.2010.9  
* E_mail:openlinux2100@gmail.com			                
*
********************************************************************************/

/*Í·ÎÄŒþÒýÓÃ*/
#include <linux/module.h>
#include <linux/init.h>
#include <linux/vmalloc.h> 
#include <linux/cdev.h>

MODULE_LICENSE("GPL");			

struct cdev *mem_cdev;	//×Ö·ûÉè±ž¶ÔÏó

/*Ä£¿éŒÓÔØº¯Êý¶šÒå*/
static int __init cdev_alloc_init (void)
{
	printk("<0>into the cdev_alloc_init\n");	
	mem_cdev = cdev_alloc();  //µ÷ÓÃº¯Êý¶¯Ì¬·ÖÅä×Ö·ûÉè±ž
	if (mem_cdev == NULL)  //Œì²âº¯Êýµ÷ÓÃ³É¹ŠÓë·ñ
	{
		printk("<0>cdev_alloc failed!\n");
		return -1;
	}
	printk("<0>cdev_alloc success! addr = 0x%x\n",(unsigned int)mem_cdev); //ÏÔÊŸÉè±žµØÖ·¿ÕŒä
	if(&(mem_cdev->list)!=NULL)  //Œì²âº¯Êýµ÷ÓÃœá¹û£¬¶ÔlistµÄ³õÊŒ»¯Çé¿ö
		printk("<0>the list_head of the mem_cdev has been initialized\n");
	if(&(mem_cdev->kobj)!=NULL)  //Œì²âº¯Êýµ÷ÓÃœá¹û£¬¶Ô×Ö¶ÎkobjµÄ³õÊŒ»¯Çé¿ö
	{
		printk("<0>the kobj of the mem_cdev has been initialized\n");
		printk("<0>the state_in_sysfs of the kobj of the mem_cdev is:%d\n",mem_cdev->kobj.state_in_sysfs);
		printk("<0>the state_initialized of the kobj of the mem_cdev is:%d\n",mem_cdev->kobj.state_initialized);
	}
	printk("<0>out the cdev_alloc_init\n");
	return 0;
}

/*Ä£¿éÐ¶ÔØº¯Êý¶šÒå*/
static void __exit cdev_alloc_exit (void)
{
	printk("<0>into cdev_alloc_exit\n");
	if (mem_cdev != NULL)
		kfree(mem_cdev);  //ÊÍ·ÅÉè±ž¿ÕŒä
	printk("<0>kfree mem_cdev OK!\n");
	printk("<0>out cdev_alloc_exit\n");
}

module_init(cdev_alloc_init);     //Ä£¿éŒÓÔØº¯Êýµ÷ÓÃ       
module_exit(cdev_alloc_exit);     //Ä£¿éÐ¶ÔØº¯Êýµ÷ÓÃ      
