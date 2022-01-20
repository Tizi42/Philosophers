/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyuan <tyuan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/21 20:52:53 by tyuan             #+#    #+#             */
/*   Updated: 2020/06/04 12:33:19 by tyuan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 50
# endif

typedef struct s_fdnl
{
	int				ifd;
	char			*iline;
	struct s_fdnl	*next;
}	t_fdnl;

int				get_next_line(int fd, char **line);
char			*f_strdup(const char *s1);
t_fdnl			*checkfd(t_fdnl *begin, int fd);
t_fdnl			*f_lstnew(int fd);
void			f_lstadd_back(t_fdnl **alst, t_fdnl *new);
void			del_istruct(t_fdnl **begin, t_fdnl **istruct);
void			checknewl(char *buf, int ret, char **line, t_fdnl *istruct);
int				f_strlen(const char *s);
void			append(char **line, char *buf, int start, int end);
int				ft_return(int ret, t_fdnl **istruct, t_fdnl **begin);

#endif
