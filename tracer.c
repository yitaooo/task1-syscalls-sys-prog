#include<stdio.h>
#include<signal.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>
#include <sys/ptrace.h>
#include <sys/user.h>
#include <sys/syscall.h>

int main(int argc, char *argv[])
{
	pid_t child;
	int status;
	struct user_regs_struct regs;
	int orig_rax;

	child = fork();
	if (child == 0) {
		ptrace(PTRACE_TRACEME, 0, NULL, NULL);
		if (argc < 2)
			execl("/bin/ls", "/bin/ls", NULL);
		else
			execv(argv[1], (argv + 1));
		exit(0);
	}
	else {
		wait(&status);

		while (1) {
			ptrace(PTRACE_SYSCALL, child, NULL, NULL);
			wait(&status);
			if (WIFEXITED(status)) {
				break;
			}
			
			ptrace(PTRACE_SYSCALL, child, NULL, NULL);
			wait(&status);
			if (WIFEXITED(status)) {
				break;
			}

			ptrace(PTRACE_GETREGS, child, 0, &regs);
			orig_rax = regs.orig_rax;
			if (__NR_read == orig_rax) {
				printf("read(%lld, 0x%p, %lld) = %lld\n", 
					regs.rdi, (void *)(regs.rsi), regs.rdx, regs.rax);
			}
			else if (__NR_write == orig_rax) {
				printf("write(%lld, 0x%p, %lld) = %lld\n",
					regs.rdi, (void *)(regs.rsi), regs.rdx, regs.rax);
			}
		}
	}

	return 0;
}

void sig_handler(int num){
	printf("\nChild Sent a signal to parent:%d\n",num);
	signal(SIGALRM,SIG_DFL);
}

int test_main()
{
	int status;
	system("clear");
	printf("\n--------Signal Handling Across Processes----------\n");
	switch(fork())
	{
		case -1:
			perror("\nFork Failed...\n");
			exit(1);
			break;
		case 0:
			alarm(3);
			kill(getppid(),SIGALRM);
			// signal(SIGALRM,sig_handler);
			printf("\nIts Child Process\n");
			sleep(5);
			break;
		default:
			signal(SIGALRM,sig_handler);
			wait(&status);
			printf("\nIts Parent Process\n");	
	}
}
