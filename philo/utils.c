/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krozis <krozis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 15:16:51 by krozis            #+#    #+#             */
/*   Updated: 2022/07/11 23:56:32 by krozis           ###   ########.fr       */
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

TIME_T	get_time(void)
{
	struct timeval	t;

	if (gettimeofday(&t, NULL) == ERROR)
		return (ERROR);
	return ((t.tv_sec * 1000) + (t.tv_usec));
}
