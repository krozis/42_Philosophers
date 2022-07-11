/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krozis <krozis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 23:39:57 by krozis            #+#    #+#             */
/*   Updated: 2022/07/12 01:04:05 by krozis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ph_error_write(char	*msg)
{
	int	len;

	len = 0;
	while (msg[len])
		len++;
	write(2, msg, len);
	return (EXIT_FAILURE);
}

int	ph_param_error(t_ph *ph)
{
	int	ret;

	ret = EXIT_SUCCESS;
	if (ph->nb_eat == ERR_NO_NEG || ph->time_death == ERR_NO_NEG
		|| ph->time_eat == ERR_NO_NEG || ph->time_sleep == ERR_NO_NEG
		|| ph->nb_eat == ERR_NO_NEG)
		ret = ph_error_write(LIGHT NO_NEG EOC);
	if (ph->nb_eat == ERR_ONLY_NBR || ph->time_death == ERR_ONLY_NBR
		|| ph->time_eat == ERR_ONLY_NBR || ph->time_sleep == ERR_ONLY_NBR
		|| ph->nb_eat == ERR_ONLY_NBR)
		ret = ph_error_write(LIGHT ONLY_NBR EOC);
	if (ph->nb_eat == ERR_TOO_BIG_NBR || ph->time_death == ERR_TOO_BIG_NBR
		|| ph->time_eat == ERR_TOO_BIG_NBR || ph->time_sleep == ERR_TOO_BIG_NBR
		|| ph->nb_eat == ERR_TOO_BIG_NBR)
		ret = ph_error_write(LIGHT TOO_BIG_NBR EOC);
	if (ph->nb_philo > 500)
		ret = ph_error_write(LIGHT TOO_MANY EOC);
	return (ret);
}
