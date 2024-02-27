/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlopez <hlopez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 11:55:02 by hlopez            #+#    #+#             */
/*   Updated: 2024/02/27 14:27:54 by hlopez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <time.h>
# include <pthread.h>
# include <stdbool.h>

typedef struct s_philo
{
	int		number;
	bool	alive;
}				t_philo;

typedef struct s_diner
{
	t_philo	**ph;
	int		number_of_philosophers;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		number_of_times_each_philosopher_must_eat;
}				t_diner;

/*		lib_utils.c		*/
int		ft_atoi(const char *str);

/*		init.c		*/
void	ft_init(t_diner *d, int ac, char **av);

#endif