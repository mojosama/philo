/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlopez <hlopez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 11:55:02 by hlopez            #+#    #+#             */
/*   Updated: 2024/03/25 19:00:36 by hlopez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdbool.h>
# include <limits.h>

typedef enum e_status
{
	EAT,
	SLEEP,
	THINK,
	FORK,
	DEATH,
	FULL,
}	t_status;

typedef enum e_action
{
	INIT,
	DESTROY,
	LOCK,
	UNLOCK,
}	t_action;

typedef struct s_fork
{
	bool			free;
	pthread_mutex_t	mutex;
}				t_fork;

typedef struct s_philo
{
	int				number;
	bool			full;
	long			meals;
	pthread_t		thread;
	t_fork			*left_fork;
	t_fork			*right_fork;
	long			last_meal;
	pthread_mutex_t	mutex;
	struct s_dinner	*table;
}				t_philo;

typedef struct s_dinner
{
	t_philo			**ph;
	t_fork			**forks;
	int				number_of_philos;
	long			time_to_eat;
	long			time_to_sleep;
	long			max_meals;
	long			time_to_die;
	long			start_time;
	bool			end;
	bool			threads_ready;
	pthread_t		monitor;
	pthread_mutex_t	mutex;
	pthread_mutex_t	print_mutex;
}				t_dinner;

/*		lib_utils.c		*/
long	ft_atol(const char *str);
int		error_exit(const char *error);

/*		init.c		*/
int		ft_init(t_dinner *d, int ac, char **av);

/*		dinner.c		*/
void	wait_all_threads(t_dinner *d);
int		ft_start_dinner(t_dinner *d);

/*		time.c		*/
long	ft_get_time(void);
long	ft_get_utime(void);
void	ft_usleep(long usec, t_dinner *d);

/*		thread_utils.c		*/
int		ft_set_bool(pthread_mutex_t *mutex, bool *dest, bool value);
int		ft_get_bool(pthread_mutex_t *mutex, bool *dest);
int		ft_set_long(pthread_mutex_t *mutex, long *dest, long value);
long	ft_get_long(pthread_mutex_t *mutex, long *dest);
int		ft_dinner_end(t_dinner *d);

/*		monitoring.c	*/
void	*ft_monitoring(void *data);
int		ft_write_status(t_philo *philo, t_status status);

/*		simulation.c	*/
int		ft_eat(t_philo *philo);
int		ft_sleep(t_philo *philo);
int		ft_think(t_philo *philo);

/*		safe_pthread.c		*/
int		ft_safe_pthread_create(pthread_t *thread, void *(*f)(void *), void *d);
int		ft_safe_pthread_join(pthread_t thread);
int		ft_safe_mutex_handle(pthread_mutex_t *mutex, t_action action);

#endif