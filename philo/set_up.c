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

# include "philo.h"

int	valid_args(int ac, char **av)
{
	int	i;

	if (ac < 5 || ac > 6)
		return (0);
	//other cases
	av = NULL;
	i = 0;
	return (1);
}

t_env	parse(char **av)
{
	t_env	env;

	//if (!valide_args(av)) :  1) <= 0 2)isdigit 3)trop grand
	env.num_philo = ft_atoi(av[1]);
	env.timespan_die = ft_atoi(av[2]);
	env.timespan_eat = ft_atoi(av[3]);
	env.timespan_sleep = ft_atoi(av[4]);
	if (av[5])
		env.times_must_eat = ft_atoi(av[5]); //if == 0 ? return
	else
		env.times_must_eat = -1;
	return (env);
}

t_fork	*init_forks(int num_philo)
{
	int				i;
	t_fork			*fork;

	fork = ft_malloc(sizeof(t_fork) * num_philo);
	i = 0;
	while (i < num_philo)
	{
		pthread_mutex_init(&fork[i].lock, NULL);
		fork[i].fid = i + 1;
		fork[i].available = 1;
		i++;
	}
	return (fork);
}

t_ph	*init_ph(t_env	env, t_fork *fork)
{
	int				i;
	t_ph			*ph;

	ph = ft_malloc(sizeof(t_ph) * env.num_philo);
	gettimeofday(&ph->t0, NULL);
	pthread_mutex_init(&ph->print, NULL);
	ph->exit = ft_malloc(sizeof(int));
	*(ph->exit) = 0;
	i = 0;
	while (i < env.num_philo)
	{
		ph[i].phid = i + 1;
		ph[i].env = env;
		ph[i].exit = ph->exit;
		ph[i].fork_left = &fork[i];
		if (i < env.num_philo - 1)
			ph[i].fork_right = &fork[i + 1];
		else
			ph[i].fork_right = &fork[0];
		ph[i].t0 = ph->t0;
		ph[i].print = ph->print;
		i++;
	}
	return (ph);
}
