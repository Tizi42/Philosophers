/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyuan <tyuan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 22:54:24 by tyuan             #+#    #+#             */
/*   Updated: 2022/01/14 23:08:42 by tyuan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	clean_up(t_ph *ph, t_fork *fork)
{
	int	i;

	i = 0;
	while (i < ph->env.num_philo)
	{
		pthread_mutex_destroy(&fork[i].lock);
		pthread_mutex_destroy(&ph[i++].lock.eat_or_die);
	}
	pthread_mutex_destroy(ph->lock.print);
	pthread_mutex_destroy(ph->lock.exit);
	free(ph->lock.print);
	free(ph->lock.exit);
	free(ph->exit);
	free(ph->t0);
	free(fork);
	free(ph);
}

void	join_threads(t_ph *ph)
{
	int	i;

	i = 0;
	while (i < ph->env.num_philo)
		pthread_join(ph[i++].tid, NULL);
	i = 0;
	while (i < ph->env.num_philo)
		pthread_join(ph[i++].monitor_tid, NULL);
}

int	start_simulation(t_ph *ph)
{
	int	i;
	int	j;

	i = 0;
	if (ph->env.num_philo == 1)
	{
		pthread_create(&ph->tid, NULL, life_circle_uni, ph);
		return (0);
	}
	while (2 * i < 10)
	{
		j = i * 2;
		while (j < ph->env.num_philo)
		{
			pthread_create(&ph[j].tid, NULL, life_circle, &ph[j]);
			j += 10;
		}
		i++;
	}
	usleep(1000);
	start_simulation_part2(ph);
	return (0);
}

int	main(int ac, char **av)
{
	t_env	env;
	t_ph	*ph;
	t_fork	*fork;

	if (!valid_args(ac, av))
	{
		printf("Error: non-valid argument\n");
		return (0);
	}
	env = parse(av);
	if (env.num_philo == 0 || env.times_must_eat == 0)
		return (0);
	fork = init_forks(env.num_philo);
	ph = init_ph(env, fork);
	start_simulation(ph);
	create_monitor(ph);
	join_threads(ph);
	clean_up(ph, fork);
}
