/********************************************************************************
* File Name:	__timecompare_update.c
* Description:	第7章实例训练          
* Reference book:《Linux内核API完全参考手册》邱铁，周玉，邓莹莹 ，机械工业出版社.2010.9  
* E_mail:openlinux2100@gmail.com			                
*
********************************************************************************/

#include <linux/module.h> 
#include<linux/timecompare.h>
#include<linux/clocksource.h>
MODULE_LICENSE("GPL");

//自定义函数，为结构体timecompare的字段target赋值，函数相当于ktime_t类型变量的构造函数
static ktime_t nstoktime(void)
{
	static ktime_t ktime_zero = { .tv64 = 0 }; //声明变量
	ktime_zero.tv64+=jiffies;  //为字段tv64赋值
	return ktime_zero;   //返回变量
}

//自定义函数，作为结构体cyclecounter的字段read赋值，作用是获得源时间的时间，在此笔者随意写的
static cycle_t read(const struct cyclecounter *cc)
{
	return cc->mask;//返回字段mask的值
}
 
int __init __timecompare_update_init(void)
{ 	
	printk("<0>__timecompare_update test begin.\n");	
	struct cyclecounter cc=
	{	
		.read=read,
		.mask=0,
		.mult=0,
		.shift=0
	}; //声明结构体cyclecounter变量,为结构体timecounter变量的cc字段赋值
	struct timecounter tc=
	{	
		.cc=&cc,
		.cycle_last=0,
		.nsec=0
	};//声明结构体timecounter变量,为结构体timecompare变量的source字段赋值
	struct timecompare sync=
	{
		.source=&tc,
		.target=nstoktime,
		.num_samples=0,
		.offset=0,
		.skew=1,
		.last_update=1   //当用1初始化时会出现不同的结果
	};//函数调用的第一个参数
	u64 source_tstamp=0;//声明函数的第二个参数，初始化为0
	printk("<0>the old offset is:%lld\n",sync.offset);//显示函数调用之前的offset的值
	printk("<0>the old skew is:%lld\n",sync.skew);//显示函数调用之前的skew的值
	printk("<0>the old last_update is :%lld\n",sync.last_update);//显示函数调用之前的last_update的值
       __timecompare_update(&sync,source_tstamp); //调用函数，更改offset和skew字段的值
	printk("<0>the new offset is:%lld\n",sync.offset);//显示函数调用之后offset的值
	printk("<0>the new skew is:%lld\n",sync.skew);//显示函数调用之后skew的值
	printk("<0>the new last_update is :%lld\n",sync.last_update);//显示函数调用之后的last_update的值 	
	printk("<0>__timecompare_update test over.\n"); 	
	return 0; 
} 

void __exit __timecompare_update_exit(void) 
{   
      printk("<0>Goodbye __timecompare_update\n"); 
} 

module_init(__timecompare_update_init);
module_exit(__timecompare_update_exit); 
