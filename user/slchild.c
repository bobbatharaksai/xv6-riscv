#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/fcntl.h"
#include "user/user.h"

#define SLEEPTICKS 10
#define IOCOUNT 5000

int main()
{
	printf("Executing iochild!\n");
	int pid = fork();
	if(pid > 0){
		printf("I'm the parent: my child=%d\n", pid);
		pid = wait((int *) 0);
		printf("I'm the parent. I see my child with pid %d has exited\n", pid);
	} else if(pid == 0){
		printf("iochild forking another child\n");
		int cpid = fork();
		if(cpid > 0)
		{
			printf("I'm child 1: my child = %d\n", cpid);
			pid = wait((int *) 0);
			printf("I'm child 1. I see my child with pid %d is done with I/O and exited\n", cpid);
			printf("Now I'm going to sleep for a while!\n");
			sleep(SLEEPTICKS);
			exit(0);
		}
		else if(cpid == 0)
		{
			printf("I'm child 2: Going to do a heavy file I/O operation\n");
	                // Going to do a heavy I/O operation
	                int fd1 = open("testfile", O_CREATE|O_WRONLY|O_TRUNC);
	                for(int i = 0; i < IOCOUNT; i++)
	                {
	                        write(fd1, "I'm writing into a testfile.", 29);
	                }
	                close(fd1);
	                exit(0);
		}
	} else {
		printf("fork error\n");
	}
	exit(0);
}
