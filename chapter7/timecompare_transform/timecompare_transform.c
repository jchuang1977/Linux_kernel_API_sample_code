/********************************************************************************
* File Name:	timecompare_transform.c
* Description:	第7章实例训练          
* Reference book:《Linux内核API完全参考手册》邱铁，周玉，邓莹莹 ，机械工业出版社.2010.9  
* E_mail:openlinux2100@gmail.com			                
*
********************************************************************************/

#include <linux/module.h>
#include<linux/timecompare.h>
MODULE_LICENSE("GPL");

int __init time_init(void)
{
	printk("<0> my timecompare transform test begin.\n");	
	struct timecompare sync=
	{
		.source=NULL,
		.target=NULL,
		.num_samples=0,
		.offset=10,
		.skew=(((s64)1)<<30),
		.last_update=10
	};//声明时间转换源对象
	u64 source_tstamp=100;//64位整数变量
        ktime_t kt=timecompare_transform(&sync,source_tstamp); //调用函数实现时间转换
	printk("<0>the tv64 value of the ktime_t is:%lld\n",kt.tv64);//显示转换之后的目标时间
	printk("<0> my timecompare transform test over.\n");
	return 0;
}

void __exit time_exit(void)
{
        printk("<1>Goodbye  timecompare transform test\n");
}
 
module_init(time_init);
module_exit(time_exit);

