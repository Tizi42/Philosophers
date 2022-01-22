/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyuan <tyuan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 16:33:26 by tyuan             #+#    #+#             */
/*   Updated: 2022/01/21 16:33:35 by tyuan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	start_simulation(t_ph *ph)
{
	int	i;
	int	j;

	i = 0;
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
	usleep(2000);
	i = 1;
	while (2 * i - 1 < 10)
	{
		j = i * 2 - 1;
		while (j < ph->env.num_philo)
		{
			pthread_create(&ph[j].tid, NULL, life_circle, &ph[j]);
			j += 10;
		}
		i++;
	}
	usleep(500);
	return (0);
}

void	*life_circle(void *arg)
{
	t_ph	*ph;
	int		ret;

	ph = (t_ph *)arg;
	//pthread_detach(ph->tid);
	//gettimeofday(&ph->lastmeal, NULL);
	data_lastmeal(ph, UPDATE);
	ret = 0;
	while (!ret)
	{
		ret = get_fork_and_eat(ph);
		ret = update_status(ph, SLEEP);
		usleep(ph->env.timespan_sleep * 1000);
		ret = update_status(ph, THINK);
	}
	return (NULL);
}

int	get_fork_and_eat(t_ph *ph)
{
	int	ret;

	ret = 0;
	pthread_mutex_lock(&ph->fork_left->lock);
	update_status(ph, FORK_L);
	pthread_mutex_lock(&ph->fork_right->lock);
	update_status(ph, FORK_R);

	ret = eat(ph);
	/*print_status(ph, EAT);
	gettimeofday(&ph->lastmeal, NULL);
	usleep(ph->env.timespan_eat * 1000);*/

	pthread_mutex_unlock(&ph->fork_right->lock);
	pthread_mutex_unlock(&ph->fork_left->lock);
	return (ret);
}

int	eat(t_ph *ph)
{
	int	ret;

	ret = 0;
	pthread_mutex_lock(ph->status_lock);
	if (*(ph->exit) >= ph->env.num_philo)
		ret = 1;
	else
		print_status(ph, EAT);
	ph->meal_taken++;
	if (ph->meal_taken == ph->env.times_must_eat)
	{
		ret = 1;
		(*ph->exit)++;
	}
	pthread_mutex_unlock(ph->status_lock);
	data_lastmeal(ph, UPDATE); // is it a good location ?
	usleep(ph->env.timespan_eat * 1000);
	return (ret);
}

long	get_timestamp(struct timeval t0)
{
	struct timeval	t1;

	gettimeofday(&t1, NULL);
	return ((t1.tv_sec - t0.tv_sec) * 1000 + (t1.tv_usec - t0.tv_usec) / 1000);
}

void	print_status(t_ph *ph, char *status)
{
	printf("%ld %i %s exit:%i\n", get_timestamp(ph->t0),
		ph->phid, status, *ph->exit);
}

int	update_status(t_ph *ph, char *status)
{
	int	ret;

	ret = 0;
	pthread_mutex_lock(ph->status_lock);
	if (*(ph->exit) >= ph->env.num_philo)
		ret = 1;
	else
		print_status(ph, status);
	pthread_mutex_unlock(ph->status_lock);
	return (ret);
}
