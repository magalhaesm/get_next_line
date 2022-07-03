/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 16:34:30 by mdias-ma          #+#    #+#             */
/*   Updated: 2022/07/03 18:47:01 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

t_chunk	*last_chunk(t_chunk *storage)
{
	if (!storage)
		return (NULL);
	while (storage->next)
		storage = storage->next;
	return (storage);
}

int	sum_chunks(t_chunk *storage)
{
	int		length;

	length = 0;
	while (storage)
	{
		length += storage->size;
		storage = storage->next;
	}
	return (length);
}

t_chunk	*new_chunk(char *text)
{
	t_chunk	*new_node;

	new_node = malloc(sizeof(*new_node));
	if (!new_node)
		return (NULL);
	new_node->text = text;
	new_node->next = NULL;
	new_node->size = 0;
	return (new_node);
}

void	free_storage(t_chunk **storage)
{
	t_chunk	*node;

	while (*storage != NULL)
	{
		node = *storage;
		*storage = (*storage)->next;
		free(node->text);
		free(node);
	}
}
