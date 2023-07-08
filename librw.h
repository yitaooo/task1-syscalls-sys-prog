#pragma once
#include <sys/types.h> 
#include <unistd.h> 

ssize_t read(int __fd, void *__buf, size_t __nbytes);
ssize_t write(int __fd, const void *__buf, size_t __n);
