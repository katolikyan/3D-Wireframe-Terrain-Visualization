/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkatolik <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/23 14:00:52 by tkatolik          #+#    #+#             */
/*   Updated: 2019/05/15 23:02:27 by tkatolik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <sys/types.h>
# include <sys/uio.h>
# include "libft.h"

int							get_next_line(const int fd, char **line);
char						*ft_read_and_store(int fd, char **thread);
t_list						*find_or_store_fd(int fd, t_list **bgn);
int							ft_check_extra(char **str, char **line);
void						ft_join(char **thread, char *buff);

typedef struct				s_fds
{
	char					*thread;
	int						fd;
}							t_fd;

# define THREAD ((t_fd *)(crnt->content))->thread
# define FD ((t_fd *)(crnt->content))->fd
# define BUFF_SIZE 32

# if BUFF_SIZE <= 0
#  error The buffer must be > 0
# endif

#endif
