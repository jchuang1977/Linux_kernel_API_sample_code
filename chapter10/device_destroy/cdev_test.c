/********************************************************************************
* File Name:	cdev_test.c
* Description:	第10章实例训练          
* Reference book:《Linux内核API完全参考手册》邱铁，周玉，邓莹莹 ，机械工业出版社.2010.9  
* E_mail:openlinux2100@gmail.com			                
*
********************************************************************************/
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <linux/fcntl.h>
int main(int argc, char **argv)
{
	int fd, cnt;
	char buf[256];
	printf("char device testing.\n");
	fd = open("/dev/my_char_dev", O_RDWR);	 //Žò¿ª×Ö·ûÉè±ž
	if (fd == 0)
	{
		printf("the char dev file cannot be opened.\n");
		return 1;
	}
	printf("input the data for kernel: ");
	scanf("%s", buf);  //ÊäÈëÊýŸÝ
	cnt = write(fd, buf, 256);   //œ«ÊäÈëÊýŸÝÐŽÈëÉè±ž
	if (cnt == 0)
		printf("Write Error!\n");
	cnt = read(fd, buf, 256);	 //ŽÓÉè±žÖÐ¶ÁÈ¡ÊýŸÝ
	if (cnt > 0)
		printf("read data from kernel is: %s\n", buf);
	else
		printf("read data error\n");
	close(fd);  //¹Ø±ÕÉè±ž
	printf("close the char dev file and test over\n");
	return 0;
}
