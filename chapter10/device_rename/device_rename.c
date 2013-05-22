/********************************************************************************
* File Name:	device_rename.c
* Description:	第10章实例训练          
* Reference book:《Linux内核API完全参考手册》邱铁，周玉，邓莹莹 ，机械工业出版社.2010.9  
* E_mail:openlinux2100@gmail.com			                
*
********************************************************************************/
/*Í·ÎÄŒþÒýÓÃ*/
#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/slab.h>
#include <linux/vmalloc.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <asm/uaccess.h>
#include <linux/types.h>
#include <linux/moduleparam.h>
#include <linux/pci.h>
#include <asm/unistd.h>
#include <linux/device.h>
#include <linux/kobject.h>

MODULE_LICENSE("GPL");			

#define MEM_MALLOC_SIZE 	4096	 //»º³åÇøŽóÐ¡
#define MEM_MAJOR      246		 //Ö÷Éè±žºÅ
#define MEM_MINOR    	0	//ŽÎÉè±žºÅ	
char *mem_spvm; 			//»º³åÇøÖžÕë,ÖžÏòÄÚŽæÇø	
struct class *mem_class;          //Éè±žÀàÖžÕë
struct device *dev;			//ÂßŒ­Éè±žÖžÕë

static int  __init  device_rename_init(void);  //Ä£¿éŒÓÔØº¯ÊýÉùÃ÷
static void  __exit device_rename_exit(void);  //Ä£¿éÐ¶ÔØº¯ÊýÉùÃ÷
module_init(device_rename_init);              //Ä£¿éŒÓÔØ
module_exit(device_rename_exit);            //Ä£¿éÐ¶ÔØ


static int mem_open(struct inode *ind, struct file *filp);  //Éè±žŽò¿ªº¯ÊýÉùÃ÷ 
static int mem_release(struct inode *ind, struct file *filp);  //Éè±ž¹Ø±Õº¯ÊýÉùÃ÷
static ssize_t mem_read(struct file *filp, char __user *buf, size_t size, loff_t *fpos);   //Éè±ž¶Áº¯ÊýÉùÃ÷
static ssize_t mem_write(struct file *filp, const char __user *buf, size_t size, loff_t *fpos);  //Éè±žÐŽº¯ÊýÉùÃ÷
static void device_register_release(struct device *dev);       //ÂßŒ­Éè±žÊÍ·ÅŽŠÀíº¯Êý

/*¶šÒåÉè±žÇý¶¯ÎÄŒþœá¹¹Ìå*/
struct file_operations mem_fops = 
{
	.owner=THIS_MODULE,   //Çý¶¯ÎÄŒþÓµÓÐÕß
	.open = mem_open,	 //Éè±žŽò¿ªº¯Êý
	.release = mem_release,	  //Éè±žŽò¿ªº¯Êý
	.read = mem_read,	      //Éè±ž¶Áº¯Êý
	.write = mem_write,      //Éè±žÐŽº¯Êý
};

/*Ä£¿éŒÓÔØº¯Êý¶šÒå*/
int __init device_rename_init(void)
{
	int res;
	printk("<0>into device_rename_init\n");
	mem_spvm = (char *)vmalloc(MEM_MALLOC_SIZE);  //¿ª±ÙÄÚŽæ»º³åÇø
	res=register_chrdev(MEM_MAJOR,"my_char_dev",&mem_fops);  //×¢²á×Ö·ûÉè±ž
	if(res)  //×¢²áÊ§°Ü
	{
		unregister_chrdev(MEM_MAJOR,"my_char_dev");  //ÉŸ³ý×Ö·ûÉè±ž
		printk("<0>register char dev failed\n");
		return -1;
	}
	printk("<0>register char dev success\n");
 	mem_class = class_create(THIS_MODULE, "my_char_dev");  //ŽŽœšÉè±žÀà
  	if(IS_ERR(mem_class))   //ÅÐ¶ÏŽŽœšÊÇ·ñ³É¹Š
       {
  	      printk("<0>failed in creating class.\n");
	      class_destroy(mem_class);   //Ê§°Ü£¬ÔòÏú»ÙÉè±žÀà
 	      return -1;
 	}
	printk("<0>class create success\n");
	dev=kzalloc(sizeof(*dev), GFP_KERNEL);  //ÎªÂßŒ­Éè±ž¿ª±ÙÄÚŽæ¿ÕŒä
	dev->devt=MKDEV(MEM_MAJOR,MEM_MINOR);   //³õÊŒ»¯Éè±žµÄÉè±žºÅ£¬°üÀšÖ÷Éè±žºÅºÍŽÎÉè±žºÅ
	dev->class=mem_class;                  //³õÊŒ»¯Éè±žÀà
	dev->release = device_register_release;  //³õÊŒ»¯Éè±ž×¢ÏúŽŠÀíº¯Êý
	res= kobject_set_name(&dev->kobj,"my_char_dev");  //³õÊŒ»¯Éè±žÒýÓÃŒÆÊýÆ÷
	if(res) 
	{
		printk("<0>kobject_set_name_vargs failed\n");
		kfree(dev);	    //Ê§°Ü£¬ÊÍ·ÅÉè±žÕŒÓÃµÄÄÚŽæ¿ÕŒä
		return -1;
        }
	res=device_register(dev);    //œ«ÂßŒ­Éè±žŒÓÈëLinuxÄÚºËÏµÍ³
	if(res)
	{
		printk("<0>register device failed\n");
		device_unregister(dev);  //×¢²áÊ§°Ü£¬ÊÍ·ÅÂßŒ­Éè±ž
		kfree(dev);	        //ÊÍ·ÅÂßŒ­Éè±žÕŒÓÃµÄÄÚŽæ¿ÕŒä
		return -1;
        }
	printk("<0>register device success\n");
	printk("<0>the name of the device is:%s\n",dev->kobj.name); //ÏÔÊŸÂßŒ­Éè±žÃû
	printk("<0>the name of the class is:%s\n",dev->class->name);  //ÏÔÊŸÂßŒ­ÀàÃû
	res=device_rename(dev,"char_dev");   //ÖØÃüÃûÂßŒ­Éè±ž
	if(res)
	{
		printk("<0>rename device failed\n");		
	}
	printk("<0>the new name of the device is:%s\n",dev->kobj.name);  //ÏÔÊŸº¯Êýµ÷ÓÃÖ®ºóµÄÂßŒ­Éè±žÃû	
	printk("<0>the new name of the class is:%s\n",dev->class->name); //ÏÔÊŸº¯Êýµ÷ÓÃÖ®ºóµÄÂßŒ­ÀàÃû
	printk("<0>out device_rename_init\n");
	return 0;
}

/*Ä£¿éÐ¶ÔØº¯Êý¶šÒå*/
void __exit device_rename_exit (void)
{
	printk("<0>into device_rename_exit\n");	
	unregister_chrdev(MEM_MAJOR,"my_char_dev");  //×¢Ïú×Ö·ûÉè±ž
	if(dev)
	{
		printk("<0>device unregister\n");
		put_device(dev);	 //ÂßŒ­Éè±žÒýÓÃŒÆÊýŒõ1
		device_unregister(dev);  //ÉŸ³ýÂßŒ­Éè±ž
	}
	printk("<0>device unregister success\n");	
	if(mem_class)
	        class_destroy(mem_class);   //ÉŸ³ýÉè±žÀà
	printk("<0>class destroy success\n");
	if (mem_spvm != NULL)
		vfree(mem_spvm);   //ÊÍ·ÅÄÚŽæ»º³åÇø¿ÕŒä
	printk("<0>vfree mem_spvm OK\n");
	printk("<0>out device_rename_exit\n");
}

/*Éè±žŽò¿ªº¯Êý¶šÒå*/
int mem_open(struct inode *ind, struct file *filp)
{	
	printk("<0>open vmalloc space\n");
	try_module_get(THIS_MODULE);  //Ä£¿éÒýÓÃ×ÔŒÓ
	printk("<0>open vmalloc space success\n");
	return 0;
}

/*Éè±ž¶Áº¯Êý¶šÒå£¬ÔÚŽËÃ»ÓÐÊµŒÊÒâÒå£¬ÒòÎª²»ÉæŒ°Éè±žµÄ¶Á*/
ssize_t mem_read(struct file *filp, char *buf, size_t size, loff_t *lofp)
{
	printk("<0>in the function mem_read\n");
	return 0;
}

/*Éè±žÐŽº¯Êý¶šÒå£¬ÔÚŽËÃ»ÓÐÊµŒÊÒâÒå£¬ÒòÎª²»ÉæŒ°Éè±žµÄÐŽ*/
ssize_t mem_write(struct file *filp, const char *buf, size_t size, loff_t *lofp)
{
	printk("<0>in the function mem_write\n");	
	return 0;
}

/*Éè±ž¹Ø±Õº¯Êý¶šÒå*/
int mem_release(struct inode *ind, struct file *filp)
{
	printk("<0>close vmalloc space\n");
	module_put(THIS_MODULE);     //Ä£¿éÒýÓÃ×ÔŒõ
	printk("<0>close vmalloc space success\n");
	return 0;
}

/*ÂßŒ­Éè±žÊÍ·ÅŽŠÀíº¯Êý*/
static void device_register_release(struct device *dev)
{
	pr_debug("device: '%s': %s\n", dev_name(dev), __func__);
	kfree(dev);   //ÊÍ·ÅÉè±žÕŒÓÃµÄÄÚŽæ¿ÕŒä
}

