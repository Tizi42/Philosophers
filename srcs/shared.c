/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shared.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyuan <tyuan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 22:34:23 by tyuan             #+#    #+#             */
/*   Updated: 2022/01/26 22:34:25 by tyuan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	data_exit(t_ph *ph, int action)
{
	int	exit;

	pthread_mutex_lock(ph->lock.exit);
	if (action == SET)
		*ph->exit = 1;
	exit = *ph->exit;
	pthread_mutex_unlock(ph->lock.exit);
	return (exit);
}

int	print_status(t_ph *ph, char *status)
{
	pthread_mutex_lock(ph->lock.print);
	if (data_exit(ph, GET))
	{
		pthread_mutex_unlock(ph->lock.print);
		return (1);
	}
	printf("%ld %i %s\n", get_timestamp(*ph->t0, NULL),
		ph->phid, status);
	pthread_mutex_unlock(ph->lock.print);
	return (0);
}

long	get_timestamp(struct timeval start, struct timeval *end)
{
	struct timeval	now;

	if (end == NULL)
	{
		gettimeofday(&now, NULL);
		return ((now.tv_sec - start.tv_sec) * 1000
			+ (now.tv_usec - start.tv_usec) / 1000);
	}
	return ((end->tv_sec - start.tv_sec) * 1000
		+ (end->tv_usec - start.tv_usec) / 1000);
}

void	time_pass_by(long ms)
{
	struct timeval	t0;

	gettimeofday(&t0, NULL);
	while (get_timestamp(t0, NULL) < ms)
		usleep(500);
}
