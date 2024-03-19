/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlopez <hlopez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 18:43:10 by hlopez            #+#    #+#             */
/*   Updated: 2024/03/19 14:52:54 by hlopez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_take_fork(t_philo *philo, t_fork *fork)
{
	if (philo->left_fork != philo->right_fork)
	{
		while (!ft_get_bool(&fork->mutex, &fork->free))
			;
		ft_set_bool(&fork->mutex, &fork->free, false);
		ft_write_status(philo, FORK);
	}
	else
		error_exit("Error on forks assignment.\n");
}

void	ft_eat(t_philo *philo)
{
	if (philo->number % 2 != 0)
	{
		ft_take_fork(philo, philo->left_fork);
		ft_take_fork(philo, philo->right_fork);
	}
	else
	{
		ft_take_fork(philo, philo->right_fork);
		ft_take_fork(philo, philo->left_fork);
	}
	ft_write_status(philo, EAT);
	ft_set_long(&philo->mutex, &philo->last_meal, ft_get_utime());
	ft_set_long(&philo->mutex, &philo->meals, philo->meals + 1);
	if (philo->table->max_meals > 0
		&& ft_get_long(&philo->mutex, &philo->meals) >= philo->table->max_meals)
	{
		ft_write_status(philo, FULL);
		ft_set_bool(&philo->mutex, &philo->full, true);
	}
	ft_usleep(philo->table->time_to_eat, philo->table);
	ft_set_bool(&philo->right_fork->mutex, &philo->right_fork->free, true);
	ft_set_bool(&philo->left_fork->mutex, &philo->left_fork->free, true);
}

inline void	ft_sleep(t_philo *philo)
{
	ft_write_status(philo, SLEEP);
	ft_usleep(philo->table->time_to_sleep, philo->table);
}

inline void	ft_think(t_philo *philo)
{
	ft_write_status(philo, THINK);
}

inline void	ft_death(t_philo *philo)
{
	ft_write_status(philo, DEATH);
	// ft_set_bool(&philo->table->mutex, &philo->table->end, true);
}
