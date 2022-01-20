/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyuan <tyuan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/21 20:51:50 by tyuan             #+#    #+#             */
/*   Updated: 2020/06/04 13:59:45 by tyuan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	checknewl(char *buf, int ret, char **line, t_fdnl *istruct)
{
	int	i;

	i = -1;
	while (++i < ret)
	{
		if (buf[i] == '\n')
		{
			if (istruct->iline)
				free(istruct->iline);
			istruct->iline = f_strdup("");
			append(&istruct->iline, buf, i + 1, ret);
			return (append(line, buf, 0, i));
		}
	}
	append(line, buf, 0, ret);
}

void	append(char **line, char *buf, int start, int end)
{
	char	*tmp;
	int		i;

	tmp = ft_malloc(sizeof(char) * (ft_strlen(*line) + (end - start) + 1));
	i = 0;
	if (*line && **line)
	{
		while (line[0][i])
		{
			tmp[i] = line[0][i];
			i++;
		}
	}
	while ((start < end))
		tmp[i++] = buf[start++];
	tmp[i] = '\0';
	if (*line)
		free(*line);
	*line = tmp;
}

int	ft_return(int ret, t_fdnl **istruct, t_fdnl **begin)
{
	if (ret > 0)
		return (1);
	else
	{
		free((*istruct)->iline);
		del_istruct(begin, istruct);
		if (ret == 0)
			return (0);
		else
			return (-1);
	}
}

int	get_next_line(int fd, char **line)
{
	int				ret;
	char			buf[BUFFER_SIZE + 1];
	static t_fdnl	*begin;
	t_fdnl			*istruct;
	char			*tmp;

	if (!line || BUFFER_SIZE <= 0 || fd < 0 || read(fd, buf, 0) < 0)
		return (-1);
	*line = f_strdup("");
	istruct = checkfd(begin, fd);
	if (istruct)
	{
		tmp = f_strdup(istruct->iline);
		checknewl(tmp, ft_strlen(istruct->iline), line, istruct);
		free(tmp);
	}
	else
		f_lstadd_back(&begin, istruct = f_lstnew(fd));
	ret = read(fd, buf, BUFFER_SIZE);
	while (ret > 0)
	{
		checknewl(buf, ret, line, istruct);
		ret = read(fd, buf, BUFFER_SIZE);
	}
	return (ft_return(ret, &istruct, &begin));
}
