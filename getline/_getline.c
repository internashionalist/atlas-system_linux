#include "_getline.h"

/**
 * newline_check - checks for \n in string
 * @buffer: buffer to check
 * @size: size of buffer
 * 
 * Return: updated buffer or NULL if no newline found
 */
char *newline_check(char buffer[], int size)
{
	int i = 0; /* index for buffer */
	char *new_buffer = NULL; /* new buffer to store data */

	while (i < size) /* loop through buffer */
	{
		if (buffer[i] == '\n') /* check for newline */
		{
			new_buffer = malloc(i + 1); /* allocate memory */
			strncpy(new_buffer, buffer, i); /* copy data */
			new_buffer[i] = '\0'; /* null-terminate string */
			return (new_buffer);
		}
		i++; /* increment index */
	}
	return (NULL); /* no newline */
}

/**
 * _getline - reads entire line from file descriptor
 * @fd: file descriptor being read
 *
 * Return: null-terminated string (excluding \n) or NULL on EOF or error
 */
char *_getline(const int fd)
{
	static char buff[READ_SIZE];   	/* buffer to store read data */
	static size_t i;		   		/* current index in buffer */
	static ssize_t buff_bytes; 		/* bytes read into buffer */
	char *line = NULL;			   	/* string allocated for line */
	size_t line_len = 0;		   	/* length of line being read */
	char *partial_line;		   		/* partial line from buffer */

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
				line[line_len] = '\0'; /* null-terminate line */
				return (line);		   /* return line */
			}
			line = realloc(line, line_len + 1); /* reallocate memory */
			line[line_len++] = current_char; /* add character to line */
		}
	}
}
