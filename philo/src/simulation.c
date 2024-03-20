/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlopez <hlopez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 18:43:10 by hlopez            #+#    #+#             */
/*   Updated: 2024/03/20 14:12:56 by hlopez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_take_fork(t_philo *philo, t_fork *fork)
{
	if (philo->left_fork != philo->right_fork)
	{
		while (!ft_get_bool(&fork->mutex, &fork->free))
			;
		if (!ft_set_bool(&fork->mutex, &fork->free, false))
			return (0);
		if (!ft_write_status(philo, FORK))
			return (0);
	}
	else
		return (error_exit("Error on forks assignment.\n"));
	return (1);
}

static int	ft_forks_handling(t_philo *philo)
{
	if (philo->number % 2 != 0)
	{
		if (!ft_take_fork(philo, philo->left_fork))
			return (0);
		if (!ft_take_fork(philo, philo->right_fork))
			return (0);
	}
	else
	{
		if (!ft_take_fork(philo, philo->right_fork))
			return (0);
		if (!ft_take_fork(philo, philo->left_fork))
			return (0);
	}
	return (1);
}

int	ft_eat(t_philo *philo)
{
	long	meals;

	if (!ft_forks_handling(philo))
		return (0);
	if (!ft_write_status(philo, EAT))
		return (0);
	if (!ft_set_long(&philo->mutex, &philo->last_meal, ft_get_utime())
		|| !ft_set_long(&philo->mutex, &philo->meals, philo->meals + 1))
		return (0);
	meals = ft_get_long(&philo->mutex, &philo->meals);
	if (meals < 0)
		return (0);
	if (philo->table->max_meals > 0 && meals >= philo->table->max_meals)
	{
		if (!ft_write_status(philo, FULL)
			|| !ft_set_bool(&philo->mutex, &philo->full, true))
			return (0);
	}
	ft_usleep(philo->table->time_to_eat, philo->table);
	if (!ft_set_bool(&philo->right_fork->mutex, &philo->right_fork->free, true)
		|| !ft_set_bool(&philo->left_fork->mutex, &philo->left_fork->free, 1))
		return (0);
	return (1);
}

inline int	ft_sleep(t_philo *philo)
{
	if (!ft_write_status(philo, SLEEP))
		return (0);
	ft_usleep(philo->table->time_to_sleep, philo->table);
	return (1);
}

inline int	ft_think(t_philo *philo)
{
	return (ft_write_status(philo, THINK));
}
