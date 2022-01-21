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

long int	get_timestamp(struct timeval t0)
{
	struct timeval	t1;

	gettimeofday(&t1, NULL);
	return ((t1.tv_sec - t0.tv_sec) * 1000 + (t1.tv_usec - t0.tv_usec) / 1000);
}

int	get_fork_and_eat(t_ph *ph)
{
	pthread_mutex_lock(&ph->fork_left->lock);
	print_status(ph, FORK_L);
	pthread_mutex_lock(&ph->fork_right->lock);
	print_status(ph, FORK_R);
	gettimeofday(&ph->lastmeal, NULL);
	print_status(ph, EAT);
	usleep(ph->env.timespan_eat * 1000);
	pthread_mutex_unlock(&ph->fork_right->lock);
	pthread_mutex_unlock(&ph->fork_left->lock);
	return (0);
}

int	print_status(t_ph *ph, char *status)
{
	int	ret;

	ret = 0;
	pthread_mutex_lock(&ph->print);
	if (*(ph->exit))
		ret = 1;
	else
		printf("%ld %i %s exit:%i\n", get_timestamp(ph->t0), ph->phid, status, *ph->exit);
	pthread_mutex_unlock(&ph->print);
	return (ret);
}

void	*life_circle(void *arg)
{
	t_ph	*ph;

	ph = (t_ph *)arg;
	pthread_detach(ph->tid);
	gettimeofday(&ph->lastmeal, NULL);
	while (ph->env.times_must_eat != 0)
	{
		get_fork_and_eat(ph);
		ph->env.times_must_eat--;
		print_status(ph, SLEEP);
		usleep(ph->env.timespan_sleep * 1000);
		print_status(ph, THINK);
	}
	return (0);
}

int	death_of_a_ph(t_ph *ph)
{
	int i;

	i = 0;
	while (i < (int)ph->env.num_philo)
	{
		if (get_timestamp(ph[i].lastmeal) > ph->env.timespan_die
			&& ph->env.times_must_eat != 0)
			return (ph[i].phid);
		i++;
	}
	return (0);
}

int	death_monitor(t_ph *ph)
{
	int n;

	while (1)
	{
		n = death_of_a_ph(ph);
		if (n)
		{
			pthread_mutex_lock(&ph->print);
			*(ph->exit) = 1;
			printf("%ld %i %s exit:%i\n", get_timestamp(ph->t0), n, DEATH, *ph->exit);
			pthread_mutex_unlock(&ph->print);
			//print_status(&ph->print, ph->t0, n, DEATH);
			return (n);
		}
		usleep(2000);
	}
}

int	start_simulation(t_ph *ph)
{
	int	i;

	i = 0;
	while (2 * i < ph->env.num_philo)
	{
		pthread_create(&ph[i].tid, NULL, life_circle, &ph[2 * i]);
		usleep(1000);
		i++;
	}
	i = 1;
	while (2 * i - 1 < ph->env.num_philo)
	{
		pthread_create(&ph[i].tid, NULL, life_circle, &ph[2 * i - 1]);
		usleep(1000);
		i++;
	}
	return (0);
}

void clean_up(t_ph *ph, t_fork *fork)
{
	int	i;

	i = 0;
	while (i < ph->env.num_philo)
		pthread_mutex_destroy(&fork[i++].lock);
	pthread_mutex_destroy(&ph->print);
	free(fork);
	free(ph);
}

int main(int ac, char **av)
{
	t_env	env;
	t_ph	*ph;
	t_fork	*fork;

	if (!valid_args(ac, av))
		return (0);
	env = parse(av);
	fork = init_forks(env.num_philo);
	ph = init_ph(env, fork);
	start_simulation(ph);
	death_monitor(ph);
	clean_up(ph, fork);
	//while (i < env.num_philo)
	//	pthread_join(ph[i++].tid, NULL);
}
