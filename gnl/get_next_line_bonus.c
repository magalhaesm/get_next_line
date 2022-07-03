/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 16:33:48 by mdias-ma          #+#    #+#             */
/*   Updated: 2022/07/03 17:16:18 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void	read_line(int fd, t_chunk **storage);
void	fill_line(char **line, t_chunk *storage);
void	rewind_storage(t_chunk **storage);
int		no_newline(t_chunk *storage, int bytes_read);

char	*get_next_line(int fd)
{
	char			*line;
	static t_chunk	*storage[FD_MAX] = {NULL};

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = NULL;
	read_line(fd, &storage[fd]);
	if (!storage[fd])
		return (NULL);
	fill_line(&line, storage[fd]);
	rewind_storage(&storage[fd]);
	return (line);
}

void	read_line(int fd, t_chunk **storage)
{
	t_chunk	*node;
	char	*buffer;
	int		bytes_read;

	bytes_read = BUFFER_SIZE;
	while (no_newline(*storage, bytes_read))
	{
		buffer = malloc(sizeof(*buffer) * (BUFFER_SIZE + 1));
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (!bytes_read || bytes_read == -1 || !buffer)
		{
			free(buffer);
			return ;
		}
		buffer[bytes_read] = '\0';
		node = last_chunk(*storage);
		if (!node)
			*storage = new_chunk(buffer);
		else
			node->next = new_chunk(buffer);
	}
}

void	fill_line(char **line, t_chunk *storage)
{
	int		tx_index;
	int		ln_index;
	int		length;

	length = sum_chunks(storage);
	if (!length)
		return ;
	*line = malloc(sizeof(**line) * (length + 1));
	if (!line)
		return ;
	ln_index = 0;
	while (storage)
	{
		tx_index = 0;
		while (ln_index < length && storage->text[tx_index])
			(*line)[ln_index++] = storage->text[tx_index++];
		storage = storage->next;
	}
	(*line)[ln_index] = '\0';
}

void	rewind_storage(t_chunk **storage)
{
	int		begin;
	int		end;
	t_chunk	*last;
	char	*text;

	last = last_chunk(*storage);
	if (!last)
		return ;
	text = last->text;
	end = last->size;
	last->text = NULL;
	free_storage(storage);
	begin = 0;
	if (text[end] != '\0')
	{
		while (text[end])
			text[begin++] = text[end++];
		text[begin] = '\0';
		*storage = new_chunk(text);
		(*storage)->size = begin;
	}
	else
		free(text);
}

int	no_newline(t_chunk *storage, int bytes_read)
{
	int		index;
	int		newline;
	t_chunk	*node;

	newline = 0;
	node = last_chunk(storage);
	if (node)
	{
		index = 0;
		while (node->text[index])
		{
			if (node->text[index++] == '\n')
			{
				newline = 1;
				break ;
			}
		}
		node->size = index;
	}
	return (!newline && bytes_read);
}
