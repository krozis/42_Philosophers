/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krozis <krozis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 15:16:51 by krozis            #+#    #+#             */
/*   Updated: 2022/07/13 21:04:14 by krozis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ph_atoi(char *nb)
{
	long	res;

	res = 0;
	while (*nb == ' ')
		nb++;
	if (*nb == '-')
		return (ERR_NO_NEG);
	else
	{
		while (*nb >= '0' && *nb <= '9')
		{
			res = res * 10 + (*nb - '0');
			nb++;
		}
	}
	if (*nb)
		return (ERR_ONLY_NBR);
	else if (res > INT_MAX)
		return (ERR_TOO_BIG_NBR);
	return (res);
}

void	ph_print(t_ph *ph, int id, char *msg, char *color)
{
	pthread_mutex_lock(&(ph->writing));
	if (ph->death == false)
	{
		printf("%lli Philosopher %i ", get_time() - ph->start_time, id + 1);
		printf("%s", color);
		printf("%s" EOC, msg);
	}
	pthread_mutex_unlock(&(ph->writing));
}

TIME_T	get_time(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

void	ph_sleep(TIME_T time, t_ph *ph)
{
	TIME_T	t;

	t = get_time();
	while (ph->death == false)
	{
		if (get_time() - t >= time)
			break ;
		usleep(50);
	}
}
