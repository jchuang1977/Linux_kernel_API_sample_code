/********************************************************************************
* File Name:	device_register_unregister.c
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

MODULE_LICENSE("GPL");			

/*ºê¶šÒåŒ°È«ŸÖ±äÁ¿¶šÒå*/
#define MEM_MALLOC_SIZE 	4096	 //»º³åÇøŽóÐ¡
#define MEM_MAJOR      246		//Ö÷Éè±žºÅ
#define MEM_MINOR    	0     //ŽÎÉè±žºÅ	
char *mem_spvm; 	            //»º³åÇøÖžÕë,ÖžÏòÄÚŽæÇø
struct class *mem_class;       //Éè±žÀàÖžÕë
struct device *dev;            //ÂßŒ­Éè±žÀàÖžÕë

static int  __init  device_register_unregister_init(void);   //Ä£¿éŒÓÔØº¯ÊýÉùÃ÷
static void  __exit device_register_unregister_exit(void);   //Ä£¿éÐ¶ÔØº¯ÊýÉùÃ÷
module_init(device_register_unregister_init);                //Ä£¿éŒÓÔØ
module_exit(device_register_unregister_exit);                //Ä£¿éÐ¶ÔØ


static int mem_open(struct inode *ind, struct file *filp);        //Éè±žŽò¿ªº¯ÊýÉùÃ÷
static int mem_release(struct inode *ind, struct file *filp);    //Éè±ž¹Ø±Õº¯ÊýÉùÃ÷
static ssize_t mem_read(struct file *filp, char __user *buf, size_t size, loff_t *fpos);        //Éè±ž¶Áº¯ÊýÉùÃ÷
static ssize_t mem_write(struct file *filp, const char __user *buf, size_t size, loff_t *fpos);  //Éè±žÐŽº¯ÊýÉùÃ÷
static void device_register_release(struct device *dev);        //ÂßŒ­Éè±žÊÍ·ÅŽŠÀíº¯Êý

/*¶šÒåÉè±žÇý¶¯ÎÄŒþœá¹¹Ìå*/
struct file_operations mem_fops = 
{
	.owner=THIS_MODULE,   //Éè±žÎÄŒþÓµÓÐÕß
	.open = mem_open,	//Éè±žŽò¿ªº¯Êý
	.release = mem_release,	 //Éè±žŽò¿ªº¯Êý
	.read = mem_read,	  //Éè±ž¶Áº¯Êý
	.write = mem_write,   //Éè±žÐŽº¯Êý
};


/*Ä£¿éŒÓÔØº¯Êý¶šÒå*/
int __init device_register_unregister_init(void)
{
	int res;
	printk("<0>into device_initialize_add_del_init\n");
	mem_spvm = (char *)vmalloc(MEM_MALLOC_SIZE);     //¿ª±ÙÄÚŽæ»º³åÇø
	res=register_chrdev(MEM_MAJOR,"my_char_dev",&mem_fops);  //×¢²á×Ö·ûÉè±ž 
	if(res)    //×¢²áÊ§°Ü
	{
		unregister_chrdev(MEM_MAJOR,"my_char_dev");   //ÉŸ³ý×Ö·ûÉè±ž
		printk("<0>register char dev failed\n");
		return -1;
	}
	printk("<0>register char dev success\n");
 	mem_class = class_create(THIS_MODULE, "my_char_dev");   //ŽŽœšÉè±žÀà
  	if(IS_ERR(mem_class))       //ÅÐ¶ÏŽŽœšÊÇ·ñ³É¹Š
       {
  	      printk("<0>failed in creating class.\n");
	      class_destroy(mem_class);         //Ê§°Ü£¬ÔòÏú»ÙÉè±žÀà
 	      return -1;
 	}
	printk("<0>class create success\n");
	dev=kzalloc(sizeof(*dev), GFP_KERNEL);    //ÎªÂßŒ­Éè±ž¿ª±ÙÄÚŽæ¿ÕŒä
	dev->devt=MKDEV(MEM_MAJOR,MEM_MINOR);     //³õÊŒ»¯ÂßŒ­Éè±žÉè±žºÅ
	dev->class=mem_class;                      //³õÊŒ»¯Éè±žÀà
	dev->release = device_register_release;    //³õÊŒ»¯Éè±ž×¢ÏúŽŠÀíº¯Êý
	res= kobject_set_name(&dev->kobj,"my_char_dev");   //³õÊŒ»¯Éè±žÒýÓÃŒÆÊýÆ÷
	if(res)
	{
		printk("<0>kobject_set_name_vargs failed\n");
		kfree(dev);	   //Ê§°Ü£¬ÊÍ·ÅÉè±žÕŒÓÃµÄÄÚŽæ¿ÕŒä
		return -1;
        }
	res=device_register(dev);     //×¢²áÉè±žÎÄŒþÏµÍ³£¬²¢œšÁ¢Éè±žœÚµã
	if(res)
	{
		printk("<0>register device failed\n");
		device_unregister(dev);   //Ê§°Ü£¬Ôò×¢ÏúÂßŒ­Éè±ž
		kfree(dev);	            //Ê§°Ü£¬ÊÍ·ÅÂßŒ­Éè±žµÄÄÚŽæ¿ÕŒä
		return -1;
        }
	printk("<0>register device success\n");
	printk("<0>out device_register_unregister_init\n");
	return 0;
}

/*Ä£¿éÐ¶ÔØº¯Êý¶šÒå*/
void __exit device_register_unregister_exit (void)
{
	printk("<0>into device_register_unregister_exit\n");	
	unregister_chrdev(MEM_MAJOR,"my_char_dev");    //×¢Ïú×Ö·ûÉè±ž
	if(dev)
	{
		put_device(dev);	    //ÂßŒ­Éè±žÒýÓÃŒÆÊýŒõ1
		device_unregister(dev);  //ÉŸ³ýÂßŒ­Éè±ž
	}
	printk("<0>device unregister success\n");	
	if(mem_class)
	        class_destroy(mem_class);    //ÉŸ³ýÉè±žÀà
	printk("<0>class destroy success\n");
	if (mem_spvm != NULL)
		vfree(mem_spvm);            //ÊÍ·ÅÄÚŽæ»º³åÇø¿ÕŒä
	printk("<0>vfree mem_spvm OK\n");
	printk("<0>out device_register_unregister_exit\n");
}


/*Éè±žŽò¿ªº¯Êý¶šÒå*/
int mem_open(struct inode *ind, struct file *filp)
{	
	printk("<0>open vmalloc space\n");
	try_module_get(THIS_MODULE);   //Ä£¿éÒýÓÃ×ÔŒÓ
	printk("<0>open vmalloc space success\n");
	return 0;
}

/*Éè±ž¶Áº¯Êý¶šÒå*/
ssize_t mem_read(struct file *filp, char *buf, size_t size, loff_t *lofp)
{
	int res = -1;
	char *tmp;
	printk("<0>copy data to the user space\n");
	tmp = mem_spvm;
	if (size > MEM_MALLOC_SIZE)       //ÅÐ¶Ï¶ÁÈ¡ÊýŸÝµÄŽóÐ¡
		size = MEM_MALLOC_SIZE;
	if (tmp != NULL)
		res = copy_to_user(buf, tmp, size);  //œ«ÄÚºËÊäÈëÐŽÈëÓÃ»§¿ÕŒä
	if (res == 0)
	{
		printk("<0>copy data success and the data is:%s\n",tmp); //ÏÔÊŸ¶ÁÈ¡µÄÊýŸÝ
		return size;
	}
	else
	{
		printk("<0>copy data fail to the user space\n");
		return 0;
	}
}

/*Éè±žÐŽº¯Êý¶šÒå*/
ssize_t mem_write(struct file *filp, const char *buf, size_t size, loff_t *lofp)
{
	int res = -1;
	char *tmp;
	printk("<0>read data from the user space\n");
	tmp = mem_spvm;
	if (size > MEM_MALLOC_SIZE)         //ÅÐ¶ÏÊäÈëÊýŸÝµÄŽóÐ¡
		size = MEM_MALLOC_SIZE;
	if (tmp != NULL)
		res = copy_from_user(tmp, buf, size);	//œ«ÓÃ»§ÊäÈëÊýŸÝÐŽÈëÄÚºË¿ÕŒä
	if (res == 0)
	{
		printk("<0>read data success and the data is:%s\n",tmp); //ÏÔÊŸÐŽÈëµÄÊýŸÝ
		return size;
	}
	else
	{
		printk("<0>read data from user space fail\n");
		return 0;
	}
}

/*Éè±ž¹Ø±Õº¯Êý¶šÒå*/
int mem_release(struct inode *ind, struct file *filp)
{
	printk("<0>close vmalloc space\n");
	module_put(THIS_MODULE);  //Ä£¿éÒýÓÃ×ÔŒõ
	printk("<0>close vmalloc space success\n");
	return 0;
}

/*ÂßŒ­Éè±žÊÍ·ÅŽŠÀíº¯Êý*/
static void device_register_release(struct device *dev)
{
	pr_debug("device: '%s': %s\n", dev_name(dev), __func__);
	kfree(dev);   //ÊÍ·ÅÉè±žÕŒÓÃµÄÄÚŽæ¿ÕŒä
}

