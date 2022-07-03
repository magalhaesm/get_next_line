/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 12:46:06 by mdias-ma          #+#    #+#             */
/*   Updated: 2022/07/03 18:36:02 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

typedef struct s_chunk {
	int				size;
	char			*text;
	struct s_chunk	*next;
}	t_chunk;

char	*get_next_line(int fd);
int		sum_chunks(t_chunk *storage);
void	free_storage(t_chunk **storage);
t_chunk	*last_chunk(t_chunk *storage);
t_chunk	*new_chunk(char *text);

#endif
