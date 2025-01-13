#include "_getline.h"

/**
 * _getline - reads entire line from file descriptor
 * @fd: file descriptor being read
 *
 * Return: null-terminated string (excluding \n) or NULL on EOF or error
 */
char *_getline(const int fd)
{
	static char buff[READ_SIZE];   /* buffer to store read data */
	static size_t i;		   /* current index in buffer */
	static ssize_t buff_bytes; /* bytes read into buffer */
	char *line = NULL;			   /* string allocated for line */
	size_t line_len = 0;		   /* length of line being read */

	if (READ_SIZE <= 0 || fd < 0) /* check for invalid input */
		return (NULL);

	while (1) /* valid input */
	{
		if (i >= (size_t)buff_bytes) /* check if buffer is empty */
		{
			i = 0;
			buff_bytes = read(fd, buff, READ_SIZE); /* read into buffer */
			if (buff_bytes <= 0)					/* check for EOF or error */
			{
				if (line) /* if line has data before EOF */
				{
					line = realloc(line, line_len + 1); /* reallocate memory */
					if (!line)							/* if realloc fails */
						return (NULL);
					line[line_len] = '\0'; /* null-terminate line */
				}
				return (line); /* once no more data, return line */
			}
		}

		while (i < (size_t)buff_bytes) /* loop through buffer */
		{
			char current_char = buff[i++]; /* iterate current character */

			if (current_char == '\n') /* check for newline */
			{
				line = realloc(line, line_len + 1); /* reallocate memory */
				if (!line)							/* if realloc fails */
					return (NULL);
				line[line_len] = '\0'; /* null-terminate line */
				return (line);		   /* return line */
			}

			line = realloc(line, line_len + 1); /* reallocate memory */
			if (!line)							/* if realloc fails */
				return (NULL);
			line[line_len] = current_char; /* add character to line */
			line_len++;					   /* increment line length */
		}
	}
}
