/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlopez <hlopez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 11:58:41 by hlopez            #+#    #+#             */
/*   Updated: 2024/02/28 17:23:44 by hlopez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	print_param_error(void)
{
	printf("Incorrect parameters. Command should be as follows:\n");
	printf("./philo <number_of_philos> <time_to_die> <time_to_eat> ");
	printf("<time_to_sleep> [<number_of_times_each_philosopher_must_eat>]\n");
	printf("(Last one is optional.)\n");
}

static int	check_params(int ac, char **av)
{
	int		i;
	size_t	j;

	i = 0;
	if (ac != 5 && ac != 6)
		return (0);
	while (++i < ac)
	{
		j = 0;
		while (av[i][j])
		{
			if (!(av[i][j] == ' ' || av[i][j] == '+'
				|| (av[i][j] >= '0' && av[i][j] <= '9')))
				return (0);
			j++;
		}
	}
	return (1);
}

void	test_print(t_diner *d)
{
	int		i;

	printf("Number of philosophers : %d\n", d->number_of_philos);
	printf("Time to die : %d\n", d->time_to_die);
	printf("Time to eat : %d\n", d->time_to_eat);
	printf("Time to sleep : %d\n", d->time_to_sleep);
	i = 0;
	printf("Existing philosophers :\n");
	while (i < d->number_of_philos)
	{
		printf("Philosopher number %d\n", d->ph[i]->number);
		i++;
	}
}

void	ft_free(t_diner *d)
{
	int	i;

	if (d)
	{
		i = 0;
		while (i < d->number_of_philos)
		{
			if (d->ph && d->ph[i])
				free(d->ph[i]);
			if (d->forks && d->forks[i])
				free(d->forks[i]);
			i++;
		}
		if (d->ph)
			free(d->ph);
		if (d->forks)
			free(d->forks);
		free(d);
	}
}

int	main(int ac, char **av)
{
	t_diner	*d;

	if (check_params(ac, av))
	{
		d = (t_diner *)malloc(sizeof(t_diner));
		if (!d)
			return (1);
		if (!ft_init(d, ac, av))
			return (ft_free(d), 1);
		test_print(d);
		ft_free(d);
	}
	else
		print_param_error();
	return (0);
}
