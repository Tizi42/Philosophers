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

# define GET 1
# define SET 2
# define SPAN 3

typedef struct s_env
{
	int				num_philo;
	unsigned int	span_die;
	unsigned int	span_eat;
	unsigned int	span_sleep;
	int				times_must_eat;
}	t_env;

typedef struct s_fork
{
	pthread_mutex_t	lock;
	int				fid;
}	t_fork;

typedef struct s_control_lock
{
	pthread_mutex_t	*exit;
	pthread_mutex_t	*print;
	pthread_mutex_t	eat_or_die;
}	t_control_lock;

typedef struct s_ph
{
	pthread_t		tid;
	pthread_t		monitor_tid;
	int				phid;
	t_env			env;
	int				mealtaken;
	int				*exit;
	t_fork			*fork_left;
	t_fork			*fork_right;
	t_control_lock	lock;
	struct timeval	*t0;
	struct timeval	lastmeal;
}	t_ph;

/* main.c */
void	clean_up(t_ph *ph, t_fork *fork);
void	join_threads(t_ph *ph);
int		start_simulation(t_ph *ph);

/* parse.c */
int		valid_args(int ac, char **av);
t_env	parse(char **av);

/* init.c */
t_fork	*init_forks(int num_philo);
void	init_control_locks(t_ph *ph);
t_ph	*init_ph(t_env	env, t_fork *fork);
void	*life_circle_uni(void *arg);

/* simulation.c */
int		start_simulation_part2(t_ph *ph);
void	*life_circle(void *arg);
int		get_fork_n_eat(t_ph *ph);
int		eat(t_ph *ph);
int		sleep_n_think(t_ph *ph);

/* monitor.c */
int		create_monitor(t_ph *ph);
void	monitor_circle(t_ph *ph, long mealstamp);
void	*monitor_on(void *arg);

/* shared.c */
int		data_exit(t_ph *ph, int action);
int		print_status(t_ph *ph, char *status);
long	get_timestamp(struct timeval t0, struct timeval *t1);
void	time_pass_by(long ms);

#endif
