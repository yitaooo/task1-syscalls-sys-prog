#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include "librw.h"

int main(int argc, char **argv)
{
	int fd;
	int rd;
	int cb = (1 << 10);
	char *buf = (void *)malloc(cb);
	//memset(buf, 0, cb);

	fd = open("git_pwd.txt", O_RDONLY);
	if (fd < 0)
		perror("cannot open git_pwd.txt");

	rd = read(fd, buf, cb);
	if (rd <= 0)
		perror("cannot read git_pwd.txt");
	else
		buf[rd] = 0;

	printf("git_pwd.txt:%s\n", buf);

	close(fd);
    exit(0);
}
