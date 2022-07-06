/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 12:46:06 by mdias-ma          #+#    #+#             */
/*   Updated: 2022/07/05 21:20:51 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

typedef struct s_chunk {
	char			text[BUFFER_SIZE + 1];
	int				size;
	int				newline;
	struct s_chunk	*next;
}	t_chunk;

char	*get_next_line(int fd);
int		newline(t_chunk *storage);
int		sum_chunks(t_chunk *storage);
t_chunk	*new_chunk(void);
t_chunk	*last_chunk(t_chunk *storage);
t_chunk	*writable_node(t_chunk **storage);

#endif
