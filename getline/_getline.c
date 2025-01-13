#include "_getline.h"

/**
 * _getline - reads entire line from file descriptor
 * @fd: file descriptor being read
 *
 * Return: null-terminated string (excluding \n) or NULL on EOF or error
 */
char *_getline(const int fd)
{
    static char buff[READ_SIZE];    /* buffer to store read data */
    static size_t i = 0;            /* current index in buffer */
    static ssize_t buff_bytes = 0;  /* bytes read into buffer */
    char *line = NULL;              /* string allocated for line */
    size_t line_len = 0;            /* length of line being read */

if (READ_SIZE <= 0 || fd < 0) /* check for invalid input */
    return (NULL);

