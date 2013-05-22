/********************************************************************************
* File Name:	cdev_init.c
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
#include <linux/fs.h>

MODULE_LICENSE("GPL");			

struct cdev *mem_cdev;	 //×Ö·ûÉè±ž¶ÔÏóÖžÕë

static int mem_open(struct inode *ind, struct file *filp);   //Éè±žŽò¿ªº¯ÊýÉùÃ÷
static int mem_release(struct inode *ind, struct file *filp);   //Éè±ž¹Ø±Õº¯ÊýÉùÃ÷
static ssize_t mem_read(struct file *filp, char __user *buf, size_t size, loff_t *fpos);   //Éè±ž¶Áº¯ÊýÉùÃ÷
static ssize_t mem_write(struct file *filp, const char __user *buf, size_t size, loff_t *fpos);   //Éè±žÐŽº¯ÊýÉùÃ÷

/*¶šÒåÉè±žÇý¶¯ÎÄŒþœá¹¹Ìå*/
struct file_operations mem_fops = 
{
	.open = mem_open,	         //Éè±žŽò¿ªº¯Êý
	.release = mem_release,	 //Éè±žŽò¿ªº¯Êý
	.read = mem_read,	       //Éè±ž¶Áº¯Êý
	.write = mem_write,        //Éè±žÐŽº¯Êý
};

/*Ä£¿éŒÓÔØº¯Êý¶šÒå*/
static int __init cdev_init_init (void)
{
	printk("<0>into the cdev_init_init\n");	
	mem_cdev = cdev_alloc();   //¶¯Ì¬·ÖÅäÒ»žöÐÂµÄ×Ö·ûÉè±ž¶ÔÏó
	if (mem_cdev == NULL)     //Œì²é·ÖÅäœá¹û
	{
		printk("<0>cdev_alloc failed!\n");
		return -1;
	}
	printk("<0>cdev_alloc success! addr = 0x%x\n",(unsigned int)mem_cdev);  //ÏÔÊŸ×Ö·ûÉè±žÄÚŽæ¿ÕŒäµØÖ·
	if(mem_cdev->ops==NULL)          //º¯Êýµ÷ÓÃÖ®Ç°ÅÐ¶Ï×Ö¶ÎopsÊÇ·ñ±»³õÊŒ»¯
	{
		printk("<0>the ops the mem_cdev has not been initialized\n");
	}
	else
	{
		printk("<0>the ops the mem_cdev has been initialized\n");
	}
	cdev_init(mem_cdev,&mem_fops);   //³õÊŒ»¯×Ö·ûÉè±ž¶ÔÏó
	if(mem_cdev->ops==NULL)         //º¯Êýµ÷ÓÃÖ®ºóÅÐ¶Ï×Ö¶ÎopsÊÇ·ñ±»³õÊŒ»¯
	{
		printk("<0>the ops the mem_cdev has not been initialized\n");
	}
	else
	{
		printk("<0>the ops the mem_cdev has been initialized\n");
	}
	printk("<0>out the cdev_init_init\n");
	return 0;
}

/*Ä£¿éÐ¶ÔØº¯Êý¶šÒå*/
static void __exit cdev_init_exit (void)
{
	printk("<0>into cdev_init_exit\n");
	if (mem_cdev != NULL)
		kfree(mem_cdev);   //ÊÍ·Å×Ö·ûÉè±žÄÚŽæ¿ÕŒä
	printk("<0>kfree mem_cdev OK!\n");
	printk("<0>out cdev_init_exit\n");
}

/*Éè±žŽò¿ªº¯Êý¶šÒå*/
int mem_open(struct inode *ind, struct file *filp)
{	
	printk("<0>open vmalloc space\n");
	try_module_get(THIS_MODULE);     //Ä£¿éÒýÓÃ×ÔŒÓ
	printk("<0>open vmalloc space success\n");
	return 0;
}

/*Éè±ž¶Áº¯Êý¶šÒå£¬ÔÚŽËÃ»ÓÐÊµŒÊÒâÒå£¬Ö»ÊÇÎªÁË³õÊŒ»¯mem_fops±äÁ¿*/
ssize_t mem_read(struct file *filp, char *buf, size_t size, loff_t *lofp)
{
	printk("<0>copy data to the user space\n");
	return 0;
}

/*Éè±žÐŽº¯Êý¶šÒå£¬ÔÚŽËÃ»ÓÐÊµŒÊÒâÒå£¬Ö»ÊÇÎªÁË³õÊŒ»¯mem_fops±äÁ¿*/
ssize_t mem_write(struct file *filp, const char *buf, size_t size, loff_t *lofp)
{
	printk("<0>read data from the user space\n");
	return 0;
}

/*Éè±ž¹Ø±Õº¯Êý¶šÒå*/
int mem_release(struct inode *ind, struct file *filp)
{
	printk("<0>close vmalloc space\n");
	module_put(THIS_MODULE);       //Ä£¿éÒýÓÃ×ÔŒõ
	printk("<0>close vmalloc space success\n");
	return 0;
}

module_init(cdev_init_init);    //Ä£¿éŒÓÔØº¯Êýµ÷ÓÃ        
module_exit(cdev_init_exit);    //Ä£¿éÐ¶ÔØº¯Êýµ÷ÓÃ
