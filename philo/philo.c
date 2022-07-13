/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krozis <krozis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 15:16:11 by krozis            #+#    #+#             */
/*   Updated: 2022/07/14 00:35:44 by krozis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ph_init_philos(t_ph *ph)
{
	int	i;

	i = ph->nb_philo;
	while (--i >= 0)
	{
		ph->philos[i].id = i;
		ph->philos[i].ate = 0;
		ph->philos[i].left_id = i;
		ph->philos[i].right_id = (i + 1) % ph->nb_philo;
		ph->philos[i].last_time_eat = 0;
		ph->philos[i].ph = ph;
	}
}

static int	ph_init_mutex(t_ph *ph)
{
	int	i;

	i = ph->nb_philo;
	while (--i >= 0)
	{
		if (pthread_mutex_init(&(ph->fork[i]), NULL) == FAILURE)
			return (EXIT_FAILURE);
	}
	if (pthread_mutex_init(&(ph->eat_check), NULL) == FAILURE)
		return (EXIT_FAILURE);
	if (pthread_mutex_init(&(ph->writing), NULL) == FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int	ph_init(t_ph *ph, int ac, char **av)
{
	ph->death = false;
	ph->all_ate = false;
	ph->nb_philo = ph_atoi(av[1]);
	ph->time_death = ph_atoi(av[2]);
	ph->time_eat = ph_atoi(av[3]);
	ph->time_sleep = ph_atoi(av[4]);
	if (ac == 6)
		ph->nb_eat = ph_atoi(av[5]);
	else
		ph->nb_eat = NOT_CONFIGURED;
	if (ph_param_error(ph) == FAILURE)
		return (EXIT_FAILURE);
	if (ph_init_mutex(ph) == FAILURE)
		return (EXIT_FAILURE);
	ph_init_philos(ph);
	return (EXIT_SUCCESS);
}

int	main(int ac, char **av)
{
	t_ph	ph;

	if (ac != 5 && ac != 6)
	{
		printf(LIGHT "%s%s%s" EOC, USAGE_1, USAGE_2, USAGE_3);
		return (EXIT_FAILURE);
	}
	if (ph_init(&ph, ac, av) == FAILURE)
		return (EXIT_FAILURE);
	if (launch(&ph) == FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
