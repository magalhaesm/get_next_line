/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 23:49:28 by mdias-ma          #+#    #+#             */
/*   Updated: 2022/07/02 08:13:47 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void	read_line(int fd, t_list **storage);
void	fill_line(char **line, t_list *storage);
void	free_storage(t_list **storage);
int		no_newline(t_list *storage, int bytes_read);

char	*get_next_line(int fd)
{
	char			*line;
	static t_list	*storage[FD_MAX] = {NULL};

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = NULL;
	read_line(fd, &storage[fd]);
	if (!storage[fd])
		return (NULL);
	fill_line(&line, storage[fd]);
	free_storage(&storage[fd]);
	return (line);
}

void	read_line(int fd, t_list **storage)
{
	t_list	*last;
	t_chunk	*content;
	char	*buffer;
	int		bytes_read;

	bytes_read = BUFFER_SIZE;
	while (no_newline(*storage, bytes_read))
	{
		content = malloc(sizeof(*content));
		buffer = malloc(sizeof(*buffer) * (BUFFER_SIZE + 1));
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (!bytes_read || bytes_read == -1 || !buffer || !content)
		{
			free(buffer);
			free(content);
			return ;
		}
		buffer[bytes_read] = '\0';
		content->text = buffer;
		last = ft_lstlast(*storage);
		if (!last)
			*storage = ft_lstnew(content);
		else
			last->next = ft_lstnew(content);
	}
}

void	fill_line(char **line, t_list *storage)
{
	int		t_index;
	int		l_index;
	int		length;
	t_chunk	*content;

	length = sum_chunk_size(storage);
	if (!length)
		return ;
	*line = malloc(sizeof(**line) * (length + 1));
	if (!line)
		return ;
	l_index = 0;
	while (storage)
	{
		t_index = 0;
		content = storage->content;
		while (l_index < length && content->text[t_index])
			(*line)[l_index++] = content->text[t_index++];
		storage = storage->next;
	}
	(*line)[l_index] = '\0';
}

void	free_storage(t_list **storage)
{
	int		begin;
	int		end;
	t_list	*last;
	t_chunk	*content;

	last = ft_lstlast(*storage);
	if (!last)
		return ;
	content = last->content;
	last->content = NULL;
	ft_lstclear(storage, free_chunk);
	begin = 0;
	end = content->size;
	if (content->text[end])
	{
		while (content->text[end])
			content->text[begin++] = content->text[end++];
		content->text[begin] = '\0';
		content->size = begin;
		*storage = ft_lstnew(content);
	}
	else
		free_chunk(content);
}

int	no_newline(t_list *storage, int bytes_read)
{
	int		newline;
	int		index;
	t_chunk	*content;

	newline = 0;
	if (storage)
	{
		content = ft_lstlast(storage)->content;
		index = 0;
		while (content->text[index])
		{
			if (content->text[index++] == '\n')
			{
				newline = 1;
				break ;
			}
		}
		content->size = index;
	}
	return (!newline && bytes_read);
}
