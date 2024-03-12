/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlopez <hlopez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 18:43:10 by hlopez            #+#    #+#             */
/*   Updated: 2024/03/12 17:52:03 by hlopez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_take_fork(t_philo *philo, t_fork *fork)
{
	ft_safe_mutex_handle(&fork->mutex, LOCK);
	ft_write_status(philo, FORK);
}

void	ft_eat(t_philo *philo)
{
	ft_take_fork(philo, philo->left_fork);
	ft_take_fork(philo, philo->right_fork);
	ft_write_status(philo, EAT);
	philo->last_meal = ft_get_utime();
	philo->meals++;
	if (philo->table->number_of_times_philos_must_eat > 0
		&& philo->meals >= philo->table->number_of_times_philos_must_eat)
	{
		ft_write_status(philo, FULL);
		ft_set_bool(&philo->mutex, &philo->full, true);
	}
	ft_usleep(philo->table->time_to_eat, philo->table);
	ft_safe_mutex_handle(&philo->right_fork->mutex, UNLOCK);
	ft_safe_mutex_handle(&philo->left_fork->mutex, UNLOCK);
}

void	ft_sleep(t_philo *philo)
{
	ft_write_status(philo, SLEEP);
	ft_usleep(philo->table->time_to_sleep, philo->table);
}

void	ft_think(t_philo *philo)
{
	ft_write_status(philo, THINK);
}

void	ft_death(t_philo *philo)
{
	ft_write_status(philo, DEATH);
	ft_set_bool(&philo->table->mutex, &philo->table->end, true);
}
