/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_up.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyuan <tyuan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 14:50:15 by tyuan             #+#    #+#             */
/*   Updated: 2022/01/17 14:50:17 by tyuan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	valid_args(int ac, char **av)
{
	int	i;
	int	j;

	if (ac < 5 || ac > 6)
		return (0);
	i = 1;
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if (!ft_isdigit(av[i][j]))
				return (0);
			j++;
		}
		if (!within_int_limit(av[i], j))
			return (0);
		i++;
	}
	return (1);
}

t_env	parse(char **av)
{
	t_env	env;

	env.num_philo = ft_atoi(av[1]);
	env.span_die = ft_atoi(av[2]);
	env.span_eat = ft_atoi(av[3]);
	env.span_sleep = ft_atoi(av[4]);
	if (av[5])
		env.times_must_eat = ft_atoi(av[5]);
	else
		env.times_must_eat = -1;
	return (env);
}
