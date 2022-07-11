/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krozis <krozis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 22:51:00 by krozis            #+#    #+#             */
/*   Updated: 2022/07/12 01:03:45 by krozis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdbool.h>
# include <limits.h>

//COLORS
# define EOC "\033[0m"
# define LIGHT "\033[1m"
# define DARK "\033[2m"
# define ITALIC "\033[3m"
# define UNDERLINE "\033[4m"
# define BLACK "\033[30m"
# define RED "\033[31m"
# define GREEN "\033[32m"
# define BLUE "\033[34m"
# define PURPLE "\033[35m"
# define CYAN "\033[36m"
# define WHITE "\033[37m"

//VALUES
# define ERROR -1
# define SUCCESS 0
# define FAILURE 1

//TYPES
# define TIME_T long long

//MESSAGES
# define USAGE_1 "USAGE:\n./philo nbr_of_philosophers"
# define USAGE_2 " time_to_die time_to_eat time_to_sleep"
# define USAGE_3 " [nbr_of_times_each_philosopher_must_eat]\n"
# define NO_NEG "Don't use negative numbers.\n"
# define ONLY_NBR "Parameters must only be positive numbers.\n"
# define TOO_BIG_NBR "Do not use numbers superior to INT_MAX.\n"
# define TOO_MANY "Don't call more than 500 philosophers.\n"
# define FORK BLACK "has taken a fork\n" EOC
# define EAT GREEN "is eating\n" EOC
# define SLEEP CYAN "is sleeping\n" EOC
# define THINK PURPLE "is thinking\n" EOC
# define DIED LIGHT RED "died\n" EOC

enum
{
	NOT_CONFIGURED = -4,
	ERR_NO_NEG,
	ERR_ONLY_NBR,
	ERR_TOO_BIG_NBR
};

typedef	struct s_philo
{
	int			id;
	pthread_t	th_id;
	int			ate;
	int			left_id;
	int			right_id;
	TIME_T		last_time_eat;
}				t_philo;


typedef struct s_ph
{
	int				nb_philo;
	int				time_death;
	int				time_eat;
	int				time_sleep;
	int				nb_eat;
	bool			death;
	TIME_T			start_time;
	pthread_mutex_t	fork[500];
	pthread_mutex_t	eat_check;
	pthread_mutex_t	writing;
	t_philo			philos[500];
}				t_ph;


//	FUNCTIONS
TIME_T	get_time(void);
int		ph_atoi(char *nb);
int		ph_param_error(t_ph *ph);

#endif