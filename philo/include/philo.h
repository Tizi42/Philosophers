/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyuan <tyuan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 20:10:37 by tyuan             #+#    #+#             */
/*   Updated: 2022/01/16 20:10:42 by tyuan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdlib.h>
# include "libft.h"

# define EAT "is eating"
# define SLEEP "is sleeping"
# define THINK "is thinking"
# define FORK_L "has taken his left fork"
# define FORK_R "has taken his right fork"
# define DEATH "died"

# define STAMP 1
# define UPDATE 2

typedef struct	s_env
{
	int				num_philo;
	unsigned int	timespan_die;
	unsigned int	timespan_eat;
	unsigned int	timespan_sleep;
	int				times_must_eat;
}	t_env;

typedef struct	s_fork
{
	pthread_mutex_t	lock;
	int				fid;
}	t_fork;

typedef struct	s_ph
{
	pthread_t		tid;
	int				phid;
	t_env			env;
	int				meal_taken;
	int				*exit;
	t_fork			*fork_left;
	t_fork			*fork_right;
	pthread_mutex_t	*status_lock;
	pthread_mutex_t	*lastmeal_lock;
	struct timeval	t0;
	struct timeval	lastmeal;
}	t_ph;

long	data_lastmeal(t_ph *ph, int action);

int		eat(t_ph *ph);

int		start_simulation(t_ph *ph);
void	*life_circle(void *arg);
int		get_fork_and_eat(t_ph *ph);
long	get_timestamp(struct timeval t0);
void 	print_status(t_ph *ph, char *status);
int		update_status(t_ph *ph, char *status);

/* set_up.c */
int		valid_args(int ac, char **av);
t_env	parse(char **av);
t_fork	*init_forks(int num_philo);
t_ph	*init_ph(t_env	env, t_fork *fork);


#endif
