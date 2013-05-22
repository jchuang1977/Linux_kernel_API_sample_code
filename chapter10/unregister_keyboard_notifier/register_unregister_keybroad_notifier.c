/********************************************************************************
* File Name:	register_unregister_keybroad_notifier.c
* Description:	�?0章实例训�?         
* Reference book:《Linux内核API完全参考手册》邱铁，周玉，邓莹莹 ，机械工业出版社.2010.9  
* E_mail:openlinux2100@gmail.com			                
*
********************************************************************************/
/*Í·ÎÄŒþÒýÓÃ*/
#include <linux/module.h>
#include <linux/init.h>
#include <linux/notifier.h>
#include <linux/keyboard.h> 

MODULE_LICENSE("GPL");			


const unsigned char unicode2ascii[256] =
{ 
	'@','@','1','2','3','4','5','6','7','8','9',
	'0','-','=','@','@','q','w','e','r','t','y',
	'u','i','o','p','[',']','@','@','a','s','d',
	'f','g','h','j','k','l',';','@','@','@','@',
	'z','x','c','v','b','n','m',',','.','/','@',
	'@','@',' '
};

/*×Ô¶šÒåŒüÅÌÍšÖªÆ÷ŽŠÀíº¯Êý*/
int key_notify(struct notifier_block *nblock, unsigned long code, void *_param) 
{  
	struct keyboard_notifier_param *param = _param;    
	if (code == KBD_KEYCODE) 
	{    	
		printk("<0>Key %c  %s \n",unicode2ascii[param->value],(param->down ? "down" : "up")); //ÏÔÊŸ°ŽŒüÐÅÏ¢
	}  
}

/*¶šÒåÍšÖªÆ÷œá¹¹Ìå*/
static struct notifier_block nb = 
{
	.notifier_call = key_notify, //³õÊŒ»¯ÍšÖªÆ÷ŽŠÀíº¯Êý
};


/*Ä£¿éŒÓÔØº¯Êý¶šÒå*/
static int __init register_unregister_keyboard_notifier_init(void)
{
	int res=-1;
	printk("<0>into register_unregister_keyboard_notifier_init\n");	
	res=register_keyboard_notifier(&nb);  //ÏòLinuxÄÚºË×¢²áŒüÅÌ²Ù×÷ÍšÖªÆ÷
	if(res)  //ÅÐ¶ÏÌíŒÓœá¹û
	{
		printk("<0>register keyboard notifier failed\n");
		return -1;
	}
	printk("register keyboard notifier success\n");
	printk("<0>out register_unregister_keyboard_notifier_init\n");
	return 0;
}

/*Ä£¿éÐ¶ÔØº¯Êý¶šÒå*/
static void __exit register_unregister_keyboard_notifier_exit(void)
{
	int res=-1;
	printk("<0>into register_unregister_keyboard_notifier_exit\n");	
	res=unregister_keyboard_notifier(&nb);  //ÉŸ³ýŒüÅÌÍ¬ÖŸÆ÷
	if(res)  //ÅÐ¶ÏÐ¶ÔØœá¹û
	{
		printk("<0>unregister keyboard notifier failed\n");
		return ;
	}
	printk("<0>unregister keyboard notifier success\n");
	printk("<0>out register_unregister_keyboard_notifier_exit\n");
}

/*Ä£¿éŒÓÔØŒ°Ð¶ÔØº¯Êýµ÷ÓÃ*/
module_init(register_unregister_keyboard_notifier_init);
module_exit(register_unregister_keyboard_notifier_exit); 
