/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlopez <hlopez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 11:58:41 by hlopez            #+#    #+#             */
/*   Updated: 2024/02/27 11:46:39 by hlopez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	print_param_error(void)
{
	printf("Incorrect parameters. Command should be as follows:\n");
	printf("./philo <number_of_philosophers> <time_to_die> <time_to_eat> \
			<time_to_sleep> <[number_of_times_each_philosopher_must_eat]>\n");
	printf("(Last one is optional.)\n");
}

int	check_params(int ac, char **av)
{
	int		i;
	size_t	j;

	i = 0;
	while (++i < ac)
	{
		j = 0;
		while (av[i][j])
		{
			if (av[i][j] != ' ' && av[i][j] != '+' && (av[i][j] >= '0' && av[i][j] <= '9'))
				return (0);
			j++;
		}
	}
	return (1);
}
// params : nombre de philos, temps pour mourir, temps pour manger, temps pour dormir (+ nombre de fois ou les philos doivent manger)

int	main(int ac, char **av)
{
	t_diner	*d;
	
	if ((ac == 5 || ac == 6) && check_params(ac, av))
	{
		d = (t_diner *)malloc(sizeof(t_diner));
		if (!d)
			return (1);
		ft_init(d, ac, av);
	}
	else
		print_param_error();
	return (0);
}
