/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 16:34:00 by mdias-ma          #+#    #+#             */
/*   Updated: 2022/07/05 10:28:36 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

# ifndef FD_MAX
#  define FD_MAX 1024
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
