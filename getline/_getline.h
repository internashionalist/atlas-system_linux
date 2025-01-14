#ifndef _GETLINE_H
#define _GETLINE_H

#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stddef.h>

#ifndef READ_SIZE
#define READ_SIZE 1024
#endif

/**
 * struct file_desc_st - file descriptor state tracker
 * @fd: file descriptor
 * @buff: buffer to store read data
 * @buff_bytes: bytes read into buffer
 * @i: current index
 * @next_fd: pointer to next file descriptor state
 */
typedef struct file_desc_st
{
    int fd;
    char buff[READ_SIZE];
    ssize_t buff_bytes;
    size_t i;
    struct file_desc_state *next_fd;
} file_desc_st_t;

char *_getline(const int fd);

#endif
