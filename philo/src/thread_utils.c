/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlopez <hlopez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 14:10:34 by hlopez            #+#    #+#             */
/*   Updated: 2024/03/20 13:44:22 by hlopez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

inline int	ft_set_bool(pthread_mutex_t *mutex, bool *dest, bool value)
{
	if (!ft_safe_mutex_handle(mutex, LOCK))
		return (0);
	*dest = value;
	if (!ft_safe_mutex_handle(mutex, UNLOCK))
		return (0);
	return (1);
}

int	ft_get_bool(pthread_mutex_t *mutex, bool *dest)
{
	bool	res;

	if (!ft_safe_mutex_handle(mutex, LOCK))
		return (-1);
	res = *dest;
	if (!ft_safe_mutex_handle(mutex, UNLOCK))
		return (-1);
	return (res);
}

inline int	ft_set_long(pthread_mutex_t *mutex, long *dest, long value)
{
	if (!ft_safe_mutex_handle(mutex, LOCK))
		return (0);
	*dest = value;
	if (!ft_safe_mutex_handle(mutex, UNLOCK))
		return (0);
	return (1);
}

long	ft_get_long(pthread_mutex_t *mutex, long *dest)
{
	long	res;

	if (!ft_safe_mutex_handle(mutex, LOCK))
		return (-1);
	res = *dest;
	if (!ft_safe_mutex_handle(mutex, UNLOCK))
		return (-1);
	return (res);
}

inline int	ft_dinner_end(t_dinner *d)
{
	return (ft_get_bool(&d->mutex, &d->end));
}
