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
	/*int	miam;

	miam = 0;
	if (ph->fork_left->available && ph->fork_right->available)
	{*/
		pthread_mutex_lock(&ph->fork_left->lock);
	//	ph->fork_left->available = 0;
		printf("%ld %i has taken his left fork\n", get_timestamp(ph->t0), ph->phid);
	//	if (ph->fork_right->available)
	//	{
			pthread_mutex_lock(&ph->fork_right->lock);
		//	ph->fork_right->available = 0;
			printf("%ld %i has taken his right fork\n", get_timestamp(ph->t0), ph->phid);
			gettimeofday(&ph->lastmeal, NULL);
			printf("%ld %i is eating\n", get_timestamp(ph->t0), ph->phid);
			usleep(ph->env.timespan_eat * 1000);
		//	ph->fork_right->available = 1;
			pthread_mutex_unlock(&ph->fork_right->lock);
		//	miam = 1;
		//}
		//ph->fork_left->available = 1;
		pthread_mutex_unlock(&ph->fork_left->lock);
	//m}
	return (0);
}

void	*simulation(void *arg)
{
	t_ph	*ph;

	ph = (t_ph *)arg;
	gettimeofday(&ph->lastmeal, NULL);
	while (1)
	{
		//while(!get_fork_and_eat(ph))
		//	;
		get_fork_and_eat(ph);
		printf("%ld %i is sleeping\n", get_timestamp(ph->t0), ph->phid);
		usleep(ph->env.timespan_sleep * 1000);
		printf("%ld %i is thinking\n", get_timestamp(ph->t0), ph->phid);
	}
	return (0);
}

int	death_of_a_ph(t_ph *ph)
{
	int i;

	i = 0;
	while (i < (int)ph->env.num_philo)
	{
		if (get_timestamp(ph[i].lastmeal) > ph->env.timespan_die)
			return (ph[i].phid);
		i++;
	}
	return (0);
}

int	start(t_env env)
{
	int				i;
	t_ph			*ph;
	t_fork			*fork;
	struct timeval	t0;

	fork = init_forks((int)env.num_philo);
	gettimeofday(&t0, NULL);
	ph = init_ph(env, fork, t0);
	i = 0;
	while (2 * i < (int)env.num_philo)
	{
		pthread_create(&ph[i].tid, NULL, simulation, &ph[2 * i]);
		usleep(3000);
		i++;
	}
	i = 1;
	while (2 * i - 1 < (int)env.num_philo)
	{
		pthread_create(&ph[i].tid, NULL, simulation, &ph[2 * i - 1]);
		usleep(3000);
		i++;
	}
	int n;
	while (1)
	{
		n = death_of_a_ph(ph);
		if (n)
		{
			printf("%ld %i died\n", get_timestamp(t0), n);
			return (n);
		}
		usleep(1000);
	}
	i = 0;
	while (i < (int)env.num_philo)
		pthread_join(ph[i++].tid, NULL);
	return (0);
}

int main(int ac, char **av)
{
	t_env	*env;

	if (!valid_args(ac, av))
		return (0);
	env = parse(av);
	start(*env);
	//printf("%u %u %u %u %u\n", env->num_philo, env->timespan_die, env->timespan_eat, env->timespan_sleep, env->times_must_eat);
}
