#include "_getline.h"

static file_desc_st_t *fd_list = NULL; /* pointer to head of list */

/**
 * get_fd_state - finds file descriptor state (or creates it)
 * @fd: file descriptor to get state for
 * 
 * Return: pointer to file descriptor state, or NULL on error
 */
file_desc_st_t *get_fd_state(int fd)
{
	file_desc_st_t *current = fd_list, *new_state; /* for traversal */

	while (current) /* traverse list for existing state */
	{
		if (current->fd == fd) /* check for match */
			return (current); /* return state if found */
		current = current->next_fd; /* move to next state */
	}

	new_state = malloc(sizeof(file_desc_st_t)); /* memory for a new state */
	if (!new_state) /* failure */
		return (NULL);
	new_state->fd = fd; /* set file descriptor */
	new_state->buff_bytes = 0; /* init size of bytes read */
	new_state->i = 0; /* init index */
	new_state->next_fd = fd_list; /* set next to current head */
	fd_list = new_state; /* make new state as head */

	return (new_state); /* shiny new state */
}

/**
 * free_states - frees memory for file descriptor states
 * 
 * Return: void
 */
void free_states(void)
{
	file_desc_st_t *current = fd_list, *next; /* for traversal */

	while (current) /* traverse state list */
	{
		next = current->next_fd; /* save next state in list */
		free(current); /* free current state */
		current = next; /* on to the next one */
	}
	fd_list = NULL; /* reset once all states freed */
}

/**
 * _getline - reads entire line from file descriptor
 * @fd: file descriptor being read
 *
 * Return: null-terminated string (excluding \n) or NULL on EOF, error, or -1
 */
char *_getline(const int fd)
{
	file_desc_st_t *state; /* file descriptor state */
	char *line = NULL;			 /* string allocated for line */
	size_t line_len = 0;		 /* length of line being read */

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
					line[line_len] = '\0';				/* null-terminate line */
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
				line[line_len] = '\0';				/* null-terminate line */
				return (line);						/* return line */
			}
			line = realloc(line, line_len + 1); /* reallocate memory */
			line[line_len++] = current_char;	/* add character to line */
		}
	}
}
