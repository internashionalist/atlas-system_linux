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
 * proc_part_line - processes partial line from buffer up to newline
 * @line: pointer to current line
 * @line_len: pointer to length of current line
 * @buff: buffer to read from
 * @i: pointer to current index in buffer
 * @buff_bytes: number of bytes read into buffer
 * 
 * Return: updated line or NULL on error
 */
char *proc_part_line(
	char *line, size_t *line_len, char buff[], size_t *i, ssize_t buff_bytes)
{
	char *partial_line = newline_check(buff + *i, buff_bytes - *i);

	if (partial_line) /* if newline found */
	{
		size_t partial_len = strlen(partial_line); /* get length */

		line = realloc(line, *line_len + partial_len + 1); /* reallocate memory */
		strncpy(line + *line_len, partial_line, partial_len); /* copy data */
		*line_len += partial_len; /* update length */
		line[*line_len] = '\0'; /* null-terminate string */
		free(partial_line); /* free that memory */

		*i += partial_len + 1; /* update index */
		return (line); /* return updated line */
	}
	return (NULL); /* or not */
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

		line = proc_part_line(line, &line_len, buff, &i, buff_bytes);
		if (line) /* if newline found */
			return (line); /* that's it */

