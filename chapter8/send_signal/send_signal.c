/********************************************************************************
* File Name:	send_signal.c
* Description:	第8章实例训练          
* Reference book:《Linux内核API完全参考手册》邱铁，周玉，邓莹莹 ，机械工业出版社.2010.9  
* E_mail:openlinux2100@gmail.com			                
*
********************************************************************************/

#include <stdlib.h>
#include <signal.h>

int main(int argc, char* argv[])
{
	if( argc == 1 )
		return -1;
	else
	{
		int pid = atoi( argv[1] );
		kill(pid, SIGALRM);
	}
	return 0;
}
