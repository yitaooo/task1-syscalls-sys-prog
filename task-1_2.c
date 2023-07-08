#include "librw.h"
#include <sys/syscall.h>
#include <errno.h>

ssize_t read(int __fd, void *__buf, size_t __nbytes)
{
	ssize_t rc = 0;
	if (0 == __nbytes)
		return 0;
	int sys_idx = __NR_read;
	__asm__ __volatile__(
		"movl %1, %%edi \n"
		"movq %2, %%rsi \n"
		"movq %3, %%rdx \n"
		"movl %4, %%eax \n"
		"syscall        \n"
		"movq %%rax, %0 \n"
		:
		"=r"(rc)
		:
		"r"(__fd), "r"(__buf), "r"(__nbytes), "r"(sys_idx)
		:
		"%rdi", "%rsi", "%rdx", "%rax"
	);
	if (0 == rc)
		errno = EIO;
	else
		errno = 0;
	return rc;
}

ssize_t write(int __fd, const void *__buf, size_t __n)
{
	ssize_t rc = 0;
	if (0 == __n)
		return 0;
	int sys_idx = __NR_write;
	__asm__ __volatile__(
		"movl %1, %%edi \n"
		"movq %2, %%rsi \n"
		"movq %3, %%rdx \n"
		"movl %4, %%eax \n"
		"syscall        \n"
		"movq %%rax, %0 \n"
		:
		"=r"(rc)
		:
		"r"(__fd), "r"(__buf), "r"(__n), "r"(sys_idx)
		:
		"%rdi", "%rsi", "%rdx", "%rax"
	);
	if (0 == rc)
		errno = EIO;
	else
		errno = 0;
	return rc;
}

