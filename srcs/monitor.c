/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyuan <tyuan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 16:25:13 by tyuan             #+#    #+#             */
/*   Updated: 2022/01/26 16:25:15 by tyuan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	create_monitor(t_ph *ph)
{
	int	i;

	i = 0;
	while (i < ph->env.num_philo)
	{
		pthread_create(&ph[i].monitor_tid, NULL, monitor_on, &ph[i]);
		i++;
	}
	return (0);
}

void	monitor_circle(t_ph *ph, long mealstamp)
{
	while (1)
	{
		while (get_timestamp(*ph->t0, NULL) - mealstamp >= ph->env.span_die - 2)
		{
			pthread_mutex_lock(&ph->lock.eat_or_die);
			if (get_timestamp(ph->lastmeal, NULL) > ph->env.span_die)
			{
				if (ph->mealtaken != ph->env.times_must_eat)
				{
					print_status(ph, DEATH);
					data_exit(ph, SET);
				}
				pthread_mutex_unlock(&ph->lock.eat_or_die);
				return ;
			}
			mealstamp = get_timestamp(*ph->t0, &ph->lastmeal);
			pthread_mutex_unlock(&ph->lock.eat_or_die);
			usleep(1000);
		}
		usleep(2000);
	}
}

void	*monitor_on(void *arg)
{
	long	mealstamp;
	t_ph	*ph;

	ph = (t_ph *)arg;
	pthread_mutex_lock(&ph->lock.eat_or_die);
	mealstamp = get_timestamp(*ph->t0, &ph->lastmeal);
	pthread_mutex_unlock(&ph->lock.eat_or_die);
	monitor_circle(ph, mealstamp);
	return (NULL);
}
