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

int	start_simulation_part2(t_ph *ph)
{
	int	i;
	int	j;

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
	gettimeofday(&ph->lastmeal, NULL);
	ret = 0;
	while (ph->mealtaken != ph->env.times_must_eat)
	{
		ret = get_fork_n_eat(ph);
		if (ret)
			return (NULL);
		ret = sleep_n_think(ph);
		if (ret)
			return (NULL);
	}
	return (NULL);
}

int	get_fork_n_eat(t_ph *ph)
{
	int	ret;

	ret = 0;
	pthread_mutex_lock(&ph->fork_left->lock);
	ret = print_status(ph, FORK_L);
	if (!ret)
	{
		pthread_mutex_lock(&ph->fork_right->lock);
		ret = print_status(ph, FORK_R);
		if (!ret)
			ret = eat(ph);
		pthread_mutex_unlock(&ph->fork_right->lock);
	}
	pthread_mutex_unlock(&ph->fork_left->lock);
	return (ret);
}

int	eat(t_ph *ph)
{
	int	ret;

	pthread_mutex_lock(&ph->lock.eat_or_die);
	ret = print_status(ph, EAT);
	if (ret)
	{
		pthread_mutex_unlock(&ph->lock.eat_or_die);
		return (ret);
	}
	gettimeofday(&ph->lastmeal, NULL);
	ph->mealtaken++;
	pthread_mutex_unlock(&ph->lock.eat_or_die);
	time_pass_by(ph->env.span_eat);
	return (0);
}

int	sleep_n_think(t_ph *ph)
{
	int	ret;

	ret = print_status(ph, SLEEP);
	if (ret)
		return (ret);
	time_pass_by(ph->env.span_sleep);
	ret = print_status(ph, THINK);
	return (ret);
}
