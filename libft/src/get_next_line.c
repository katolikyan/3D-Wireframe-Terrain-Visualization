/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkatolik <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 16:30:00 by tkatolik          #+#    #+#             */
/*   Updated: 2019/05/15 23:28:02 by tkatolik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/get_next_line.h"

int					get_next_line(const int fd, char **line)
{
	static t_list	*list;
	t_list			*crnt;
	char			*extra;

	if (!line || fd < 0)
		return (-1);
	crnt = find_or_store_fd(fd, &list);
	if (ft_check_extra(&(THREAD), line) > 0)
		return (1);
	if (!(extra = ft_read_and_store(fd, &(THREAD))))
		return (-1);
	*line = ft_strdup(THREAD);
	if (extra == (THREAD))
	{
		if (*(THREAD) == 0)
			return (0);
		ft_bzero(THREAD, 1);
		return (1);
	}
	free(THREAD);
	THREAD = extra;
	return (1);
}

char				*ft_read_and_store(int fd, char **thread)
{
	char			*buf;
	char			*newline;
	char			*extra;
	int				nbit;

	extra = NULL;
	if (!(buf = ft_memalloc(BUFF_SIZE + 1)))
		return (NULL);
	while ((nbit = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[nbit] = '\0';
		if ((newline = ft_strchr(buf, '\n')) != NULL)
		{
			*newline = '\0';
			ft_join(thread, buf);
			extra = ft_strdup((newline + 1));
			free(buf);
			return (extra);
		}
		ft_join(thread, buf);
	}
	free(buf);
	return (nbit == 0 ? (*thread) : (NULL));
}

t_list				*find_or_store_fd(int fd, t_list **bgn)
{
	t_list			*crnt;
	t_fd			fds;

	fds.fd = fd;
	fds.thread = 0;
	if (!*bgn)
	{
		*bgn = ft_lstnew(&fds, sizeof(t_fd));
		((t_fd *)((*bgn)->content))->fd = fd;
		((t_fd *)((*bgn)->content))->thread = ft_strnew(1);
		return (*bgn);
	}
	crnt = *bgn;
	while (fd != FD && crnt->next)
		crnt = crnt->next;
	if ((fd != FD) && !(crnt->next))
	{
		crnt->next = ft_lstnew(&fds, sizeof(t_fd));
		crnt = crnt->next;
		FD = fd;
		THREAD = ft_strnew(1);
	}
	return (crnt);
}

int					ft_check_extra(char **str, char **line)
{
	char			*newline;
	char			*tmp;

	if ((newline = ft_strchr(*str, '\n')) != NULL)
	{
		*newline = '\0';
		*line = ft_strdup(*str);
		tmp = ft_strdup((newline + 1));
		free(*str);
		*str = tmp;
		return (1);
	}
	return (0);
}

void				ft_join(char **thread, char *buff)
{
	char			*tmp;

	tmp = ft_strjoin(*thread, buff);
	free(*thread);
	*thread = tmp;
}
