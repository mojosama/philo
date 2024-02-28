/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlopez <hlopez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 11:55:02 by hlopez            #+#    #+#             */
/*   Updated: 2024/02/28 16:51:58 by hlopez           ###   ########.fr       */
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

typedef struct s_fork
{
	pthread_mutex_t	mutex;
	int				id;
}				t_fork;

typedef struct s_philo
{
	int			number;
	bool		alive;
	int			meals;
	pthread_t	thread;
	t_fork		*left_fork;
	t_fork		*right_fork;
	long		last_meal;
}				t_philo;

typedef struct s_diner
{
	t_philo	**ph;
	t_fork	**forks;
	int		number_of_philos;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		number_of_times_philos_must_eat;
	long	start_time;
	bool	end;
}				t_diner;

/*		lib_utils.c		*/
int		ft_atoi(const char *str);

/*		init.c		*/
int		ft_init(t_diner *d, int ac, char **av);

/*		diner.c		*/
void	*ft_dining(t_diner *d);

#endif