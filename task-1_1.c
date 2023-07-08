#include "librw.h"
#include <sys/syscall.h>
#include <errno.h>

ssize_t read(int __fd, void *__buf, size_t __nbytes)
{
	int rc;
	if (0 == __nbytes)
		return 0;
	rc = syscall(__NR_read, __fd, __buf, __nbytes);
	if (0 == rc)
		errno = EIO;
	else
		errno = 0;
	return rc;
}

ssize_t write(int __fd, const void *__buf, size_t __n)
{
	int rc;
	if (0 == __n)
		return 0;
	rc = syscall(__NR_write, __fd, __buf, __n);
	if (0 == rc)
		errno = EIO;
	else
		errno = 0;
	return rc;
}
