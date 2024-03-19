/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlopez <hlopez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 14:10:34 by hlopez            #+#    #+#             */
/*   Updated: 2024/03/19 13:38:18 by hlopez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

inline void	ft_set_bool(pthread_mutex_t *mutex, bool *dest, bool value)
{
	ft_safe_mutex_handle(mutex, LOCK);
	*dest = value;
	ft_safe_mutex_handle(mutex, UNLOCK);
}

bool	ft_get_bool(pthread_mutex_t *mutex, bool *dest)
{
	bool	res;

	ft_safe_mutex_handle(mutex, LOCK);
	res = *dest;
	ft_safe_mutex_handle(mutex, UNLOCK);
	return (res);
}

inline void	ft_set_long(pthread_mutex_t *mutex, long *dest, long value)
{
	ft_safe_mutex_handle(mutex, LOCK);
	*dest = value;
	ft_safe_mutex_handle(mutex, UNLOCK);
}

long	ft_get_long(pthread_mutex_t *mutex, long *dest)
{
	long	res;

	ft_safe_mutex_handle(mutex, LOCK);
	res = *dest;
	ft_safe_mutex_handle(mutex, UNLOCK);
	return (res);
}

inline bool	ft_dinner_end(t_dinner *d)
{
	return (ft_get_bool(&d->mutex, &d->end));
}
