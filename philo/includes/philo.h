/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlopez <hlopez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 11:55:02 by hlopez            #+#    #+#             */
/*   Updated: 2024/03/08 11:39:00 by hlopez           ###   ########.fr       */
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
}	t_status;

typedef struct s_fork
{
	pthread_mutex_t	mutex;
	int				id;
}				t_fork;

typedef struct s_philo
{
	int				number;
	bool			full;
	int				meals;
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
	int				number_of_times_philos_must_eat;
	long			time_to_die;
	long			start_time;
	bool			end;
	bool			threads_ready;
	pthread_t		monitor;
	pthread_mutex_t	mutex;
}				t_dinner;

/*		lib_utils.c		*/
long	ft_atol(const char *str);

/*		init.c		*/
int		ft_init(t_dinner *d, int ac, char **av);

/*		dinner.c		*/
void	wait_all_threads(t_dinner *d);
void	*ft_dining(void *data);
int		ft_start_dinner(t_dinner *d);

/*		time.c		*/
long	ft_get_time(void);
long	ft_get_utime(void);
void	ft_usleep(long usec, t_dinner *d);

/*		thread_utils.c		*/
void	ft_set_bool(pthread_mutex_t *mutex, bool *dest, bool value);
bool	ft_get_bool(pthread_mutex_t *mutex, bool *dest);
void	ft_set_long(pthread_mutex_t *mutex, long *dest, long value);
long	ft_get_long(pthread_mutex_t *mutex, long *dest);
bool	ft_dinner_end(t_dinner *d);

/*		monitoring.c	*/
void	*ft_monitoring(void *data);
void	ft_write_status(t_philo *philo, t_status status);

/*		simulation.c	*/
void	ft_eat(t_philo *philo);
void	ft_sleep(t_philo *philo);
void	ft_think(t_philo *philo);
void	ft_death(t_philo *philo);

#endif