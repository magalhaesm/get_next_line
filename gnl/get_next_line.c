/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 12:42:38 by mdias-ma          #+#    #+#             */
/*   Updated: 2022/06/28 14:49:42 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char		*get_line(int fd, t_list *line_storage, int line_length);
static char		*line_join(t_list *line_storage, int line_len);
static int		line_complete(char *chunk, int bytes_read, int *line_length);

char	*get_next_line(int fd)
{
	int				line_length;
	static t_list	*line_storage = NULL;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!line_storage)
		line_length = 0;
	else
		line_length = ft_strlen(line_storage->content);
	return (get_line(fd, line_storage, line_length));
}

// TODO: criar função para apagar toda a lista
// TODO: criar função preparar a lista para próxima chamada
// NOTA: se usar a struct chunk para armazenar quanto foi lido,
// ao final só preciso iterar o último nó para saber o tamanho da linha
// static char	*get_line(int fd, t_list *line_storage)
static char	*get_line(int fd, t_list *line_storage, int line_length)
{
	char		*chunk;
	int			bytes_read;

	bytes_read = BUFFER_SIZE;
	while (bytes_read)
	{
		chunk = malloc(sizeof(*chunk) * (BUFFER_SIZE + 1));
		if (!chunk)
			return (NULL);
		bytes_read = read(fd, chunk, BUFFER_SIZE);
		if (bytes_read == -1)
			return (NULL);
		chunk[BUFFER_SIZE] = '\0';
		ft_lstadd_back(&line_storage, ft_lstnew(chunk));
		if (line_complete(chunk, bytes_read, &line_length))
			break ;
	}
	return (line_join(line_storage, line_length));
}

static char	*line_join(t_list *line_storage, int line_length)
{
	int		i;
	char	*line;
	char	*string;
	t_list	*exclude;

	line = malloc(sizeof(*line) * (line_length + 1));
	if (!line)
		return (NULL);
	i = 0;
	while (line_storage)
	{
		string = line_storage->content;
		while (i < line_length && *string)
			line[i++] = *(string++);
		exclude = line_storage;
		line_storage = line_storage->next;
		ft_lstdelone(exclude, free);
	}
	line[i] = '\0';
	return (line);
}

static int	line_complete(char *chunk, int bytes_read, int *line_length)
{
	int	i;

	i = 0;
	while (i < bytes_read)
	{
		if (chunk[i++] == '\n')
		{
			*line_length += i;
			return (1);
		}
	}
	*line_length += bytes_read;
	return (0);
}
