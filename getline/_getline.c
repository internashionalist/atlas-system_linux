#include "_getline.h"

/**
 * _getline - reads entire line from file descriptor
 * @fd: file descriptor being read
 *
 * Return: null-terminated string (excluding \n) or NULL on EOF or error
 */
char *_getline(const int fd)
{
    static char buff[READ_SIZE];    /* buffer */
    static size_t i = 0;            /* current index */
    static ssize_t buff_bytes = 0;  /* bytes read */
    char *line = NULL;              /* line to return */
    size_t line_len = 0;            /* length of line */

