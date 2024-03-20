/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_pthread.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlopez <hlopez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 14:21:52 by hlopez            #+#    #+#             */
/*   Updated: 2024/03/20 13:32:35 by hlopez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_safe_pthread_create(pthread_t *thread, void *(*f)(void *), void *d)
{
	if (pthread_create(thread, NULL, f, d) != 0)
		return (error_exit("Error while creating a thread.\n"));
	return (1);
}

int	ft_safe_pthread_join(pthread_t thread)
{
	if (pthread_join(thread, NULL) != 0)
		return (error_exit("Error while joining a thread.\n"));
	return (1);
}

int	ft_safe_mutex_handle(pthread_mutex_t *mutex, t_action action)
{
	if (action == INIT)
	{
		if (pthread_mutex_init(mutex, NULL) != 0)
			return (error_exit("Error while initializing a mutex.\n"));
	}
	else if (action == DESTROY)
	{
		if (pthread_mutex_destroy(mutex) != 0)
			return (error_exit("Error while destroying a mutex.\n"));
	}
	else if (action == LOCK)
	{
		if (pthread_mutex_lock(mutex) != 0)
			return (error_exit("Error while locking a mutex.\n"));
	}
	else if (action == UNLOCK)
	{
		if (pthread_mutex_unlock(mutex) != 0)
			return (error_exit("Error while unlocking a mutex.\n"));
	}
	else
		return (error_exit("Wrong code passed as argument.\n"));
	return (1);
}
