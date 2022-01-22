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
	env.timespan_die = ft_atoi(av[2]);
	env.timespan_eat = ft_atoi(av[3]);
	env.timespan_sleep = ft_atoi(av[4]);
	if (av[5])
		env.times_must_eat = ft_atoi(av[5]);
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
		i++;
	}
	return (fork);
}

void init_control_locks(t_ph *ph)
{
	ph->status_lock = ft_malloc(sizeof(pthread_mutex_t));
	ph->lastmeal_lock = ft_malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(ph->status_lock, NULL);
	pthread_mutex_init(ph->lastmeal_lock, NULL);
}

t_ph	*init_ph(t_env	env, t_fork *fork)
{
	int				i;
	t_ph			*ph;

	ph = ft_malloc(sizeof(t_ph) * env.num_philo);
	gettimeofday(&ph->t0, NULL);
	init_control_locks(ph);
	ph->exit = ft_malloc(sizeof(int));
	*(ph->exit) = 0;
	i = 0;
	while (i < env.num_philo)
	{
		ph[i].phid = i + 1;
		ph[i].env = env;
		ph[i].exit = ph->exit;
		ph[i].meal_taken = 0;
		ph[i].fork_left = &fork[i];
		if (i < env.num_philo - 1)
			ph[i].fork_right = &fork[i + 1];
		else
			ph[i].fork_right = &fork[0];
		ph[i].t0 = ph->t0;
		ph[i].status_lock = ph->status_lock;
		ph[i].lastmeal_lock = ph->lastmeal_lock;
		i++;
	}
	return (ph);
}
