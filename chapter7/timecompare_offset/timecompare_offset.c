/********************************************************************************
* File Name:	timecompare_offset.c
* Description:	第7章实例训练          
* Reference book:《Linux内核API完全参考手册》邱铁，周玉，邓莹莹 ，机械工业出版社.2010.9  
* E_mail:openlinux2100@gmail.com			                
*
********************************************************************************/

#include <linux/module.h>
#include<linux/timecompare.h>
MODULE_LICENSE("GPL");

//自定义函数，为结构体timecompare的字段target赋值，函数相当于ktime_t类型变量的构造函数
static ktime_t nstoktime(void)
{
	static ktime_t ktime_zero = { .tv64 = 0 };//声明变量	
	ktime_zero.tv64+=jiffies;//为字段tv64赋值
	return ktime_zero;//返回变量
}
//自定义函数，作为结构体cyclecounter的字段read赋值，作用是获得源时间的时间，在此笔者随意写的
static cycle_t read(const struct cyclecounter *cc)
{
	return cc->mask;//返回字段mask的值
}

int __init time_init(void)
{
	printk("<0> my timecompare_offset test begin.\n");	
	struct cyclecounter cc=
	{	
		.read=read,
		.mask=100,
		.mult=0,
		.shift=0
	};//声明结构体cyclecounter变量,为结构体timecounter变量的cc字段赋值
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
		.num_samples=3,
		.offset=0,
		.skew=1,
		.last_update=0
	};//函数调用的第一个参数
	s64 offset=0;//函数调用的第二个参数
	u64 source_tstamp=0;//函数调用的第三个参数
        int result=timecompare_offset(&sync,&offset,&source_tstamp);//调用函数测试当前的时间偏差
	printk("<0>the timecompare_offset result is:%d\n",result);//显示函数调用的返回值，即测试用例数
	printk("<0>the value of the source_tstamp:%lld\n",source_tstamp);//显示平均源时间
	printk("<0>the value of the offset is:%lld\n",offset);//显示时间平均偏差
	printk("<0> my timecompare_offset test over.\n");
	return 0;
}

void __exit time_exit(void)
{
        printk("<1>Goodbye  timecompare_offset test\n");
}

module_init(time_init);
module_exit(time_exit);

