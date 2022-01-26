/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyuan <tyuan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 13:56:07 by tyuan             #+#    #+#             */
/*   Updated: 2022/01/26 13:56:10 by tyuan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_fork	*init_forks(int num_philo)
{
	int				i;
	t_fork			*fork;

	fork = ft_malloc(sizeof(t_fork) * (num_philo + 1));
	i = 0;
	while (i < num_philo)
	{
		pthread_mutex_init(&fork[i].lock, NULL);
		fork[i].fid = i + 1;
		i++;
	}
	return (fork);
}

void	init_control_locks(t_ph *ph)
{
	int	i;

	ph->lock.print = ft_malloc(sizeof(pthread_mutex_t));
	ph->lock.exit = ft_malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(ph->lock.print, NULL);
	pthread_mutex_init(ph->lock.exit, NULL);
	i = 0;
	while (i < ph->env.num_philo)
	{
		ph[i].lock.print = ph->lock.print;
		ph[i].lock.exit = ph->lock.exit;
		pthread_mutex_init(&ph[i].lock.eat_or_die, NULL);
		i++;
	}
}

t_ph	*init_ph(t_env	env, t_fork *fork)
{
	int				i;
	t_ph			*ph;

	ph = ft_malloc(sizeof(t_ph) * env.num_philo);
	ph->t0 = ft_malloc(sizeof(struct timeval));
	ph->exit = ft_malloc(sizeof(int));
	*(ph->exit) = 0;
	i = 0;
	while (i < env.num_philo)
	{
		ph[i].phid = i + 1;
		ph[i].env = env;
		ph[i].exit = ph->exit;
		ph[i].mealtaken = 0;
		ph[i].fork_left = &fork[i];
		if (i < env.num_philo - 1)
			ph[i].fork_right = &fork[i + 1];
		else
			ph[i].fork_right = &fork[0];
		ph[i].t0 = ph->t0;
		i++;
	}
	init_control_locks(ph);
	gettimeofday(ph->t0, NULL);
	return (ph);
}

void	*life_circle_uni(void *arg)
{
	t_ph	*ph;
	int		ret;

	ph = (t_ph *)arg;
	gettimeofday(&ph->lastmeal, NULL);
	ret = 0;
	if (ph->mealtaken != ph->env.times_must_eat)
	{
		print_status(ph, FORK_L);
		while (!data_exit(ph, GET))
			usleep(2000);
	}
	return (NULL);
}
