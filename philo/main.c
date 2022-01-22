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

void clean_up(t_ph *ph, t_fork *fork)
{
	int	i;

	i = 0;
	while (i < ph->env.num_philo)
		pthread_mutex_destroy(&fork[i++].lock);
	pthread_mutex_destroy(ph->status_lock);
	pthread_mutex_destroy(ph->lastmeal_lock);
	free(ph->status_lock);
	free(ph->lastmeal_lock);
	free(ph->exit);
	free(fork);
	free(ph);
}

long	data_lastmeal(t_ph *ph, int action)
{
	long	timestamp;

	timestamp = 0;
	pthread_mutex_lock(ph->lastmeal_lock);
	if (action == STAMP)
		timestamp = get_timestamp(ph->lastmeal);
	if (action == UPDATE)
		gettimeofday(&ph->lastmeal, NULL);
	pthread_mutex_unlock(ph->lastmeal_lock);
	return (timestamp);
}

int	everyone_is_full(t_ph *ph)
{
	int	i;

	i = 0;
	while (i < ph->env.num_philo)
	{
		if (ph[i].meal_taken != ph->env.times_must_eat)
			return (0);
		i++;
	}
	return (1);
}

int	death_of_a_ph(t_ph *ph)
{
	int i;
	int	ret;

	i = 0;
	ret = 0;
	while (i < (int)ph->env.num_philo)
	{
		pthread_mutex_lock(ph->status_lock);
		if (data_lastmeal(&ph[i], STAMP) > ph->env.timespan_die)
		{
			
			if (ph[i].meal_taken != ph->env.times_must_eat)
			{
				*(ph->exit) = 1;
				print_status(&ph[i], DEATH);
				ret = 1;
			}
			else if (everyone_is_full(ph))
				ret = 1;
		}
		pthread_mutex_unlock(ph->status_lock);
			if (ret)
				return (ret);
		i++;
	}
	return (0);
}

int	monitor(t_ph *ph)
{
	int n;

	while (1)
	{
		n = death_of_a_ph(ph);
		if (n)
			return (n);
		usleep(1000); // ?x
	}
}

int main(int ac, char **av)
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
	monitor(ph);
	int i = 0;
	while (i < env.num_philo)
		pthread_join(ph[i++].tid, NULL);
	clean_up(ph, fork);
}
