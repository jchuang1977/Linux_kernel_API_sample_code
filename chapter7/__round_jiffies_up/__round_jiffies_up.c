/********************************************************************************
* File Name:	__round_jiffies_up.c
* Description:	第7章实例训练          
* Reference book:《Linux内核API完全参考手册》邱铁，周玉，邓莹莹 ，机械工业出版社.2010.9  
* E_mail:openlinux2100@gmail.com			                
*
********************************************************************************/

#include <linux/module.h> 
#include<linux/timer.h>
MODULE_LICENSE("GPL");

int __init __round_jiffies_up_init(void) 
{
	printk("<0>into __round_jiffies_up_init\n");
	unsigned long j=jiffies;//获取当前节拍数	
	unsigned long __result1=__round_jiffies_up(j,0);//参数j当前节拍，0代表cpu编号
	unsigned long __result2=__round_jiffies_up(j,1);//参数j当前节拍，1代表cpu编号
	printk("the current jiffies is :%ld\n",j);//显示当前节拍
	//显示函数调用结果
	printk("the __result1 of the __round_jiffies_up(j,0) is :%ld\n",__result1);
	printk("the __result2 of the __round_jiffies_up(j,1) is :%ld\n",__result2);
	printk("<0>out __round_jiffies_up_init\n"); 	
	return 0;
} 

void __exit __round_jiffies_up_exit(void) 
{         
	printk("<0>Goodbye __round_jiffies_up\n"); 
} 

module_init(__round_jiffies_up_init);
module_exit(__round_jiffies_up_exit); 
