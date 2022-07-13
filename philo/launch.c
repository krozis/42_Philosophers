/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krozis <krozis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 01:21:03 by krozis            #+#    #+#             */
/*   Updated: 2022/07/14 00:25:28 by krozis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	eating(t_philo *philo)
{
	t_ph	*ph;

	ph = philo->ph;
	if (philo->ate >= ph->nb_eat)
		return ;
	pthread_mutex_lock(&(ph->fork[philo->left_id]));
	ph_print(ph, philo->id, FORK, BLACK);
	if (philo->left_id != philo->right_id)
	{
		pthread_mutex_lock(&(ph->fork[philo->right_id]));
		ph_print(ph, philo->id, FORK, BLACK);
		pthread_mutex_lock(&(ph->eat_check));
		ph_print(ph, philo->id, EAT, GREEN);
		philo->last_time_eat = get_time();
		pthread_mutex_unlock(&(ph->eat_check));
		ph_sleep(ph->time_eat, ph);
		(philo->ate)++;
		pthread_mutex_unlock(&(ph->fork[philo->right_id]));
	}
	pthread_mutex_unlock(&(ph->fork[philo->left_id]));
}

static void	exit_philo(t_ph *ph, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < ph->nb_philo)
	{
		pthread_join(philos[i].th_id, NULL);
		i++;
	}
	i = 0;
	while (i < ph->nb_philo)
	{
		pthread_mutex_destroy(&(ph->fork[i]));
		i++;
	}
	pthread_mutex_destroy(&(ph->writing));
}

static void	ph_check(t_ph *ph, t_philo *philo)
{
	int	i;

	while (ph->all_ate == false)
	{
		i = -1;
		while (++i < ph->nb_philo && ph->death == false)
		{
			pthread_mutex_lock(&(ph->eat_check));
			if (get_time() - philo[i].last_time_eat > ph->time_death)
			{
				ph_print(ph, i, DIED, LIGHT RED);
				ph->death = true;
			}
			pthread_mutex_unlock(&(ph->eat_check));
			usleep(100);
		}
		if (ph->death == true)
			break ;
		i = 0;
		while (ph->nb_eat != NOT_CONFIGURED && i < ph->nb_philo
			&& philo[i].ate >= ph->nb_eat)
			i++;
		if (i == ph->nb_philo)
			ph->all_ate = true;
	}
}

static void	*ph_thread(void *ptr)
{
	t_philo	*philo;
	t_ph	*ph;

	philo = (t_philo *)ptr;
	ph = philo->ph;
	if (philo->id % 2)
		usleep(15000);
	while (ph->death == false)
	{
		eating(philo);
		if (ph->all_ate == true)
			break ;
		ph_print(ph, philo->id, SLEEP, CYAN);
		ph_sleep(ph->time_sleep, ph);
		ph_print(ph, philo->id, THINK, PURPLE);
	}
	return (NULL);
}

int	launch(t_ph *ph)
{
	int		i;
	t_philo	*philo;

	i = 0;
	philo = ph->philos;
	ph->start_time = get_time();
	while (i < ph->nb_philo)
	{
		if (pthread_create(&(philo[i].th_id), NULL, ph_thread, &(philo[i])))
			return (EXIT_FAILURE);
		philo[i].last_time_eat = get_time();
		i++;
	}
	ph_check(ph, ph->philos);
	exit_philo(ph, philo);
	return (EXIT_SUCCESS);
}
