#include "_getline.h"

/**
 * _getline - reads entire line from file descriptor
 * @fd: file descriptor being read
 *
 * Return: text from file descriptor or NULL if none
 */
char *_getline(const int fd)
{
    static char buff[READ_SIZE];  /* buffer */
    static char *entire = NULL;  /* entire text */
    
