/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olidon <olidon@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 10:39:39 by olidon            #+#    #+#             */
/*   Updated: 2021/01/19 14:42:03 by olidon           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

static int	ft_argv_to_int(unsigned int **args, int argc, char **argv)
{
	int					i;
	unsigned long long	nbr;

	i = 1;
	while (i < argc)
	{
		if (!argv[i] || (argv[i] && !argv[i][0]) ||
				ft_isnumber(argv[i]) == 0 || ft_strlen(argv[i]) > 19)
			return (0);
		nbr = ft_atoi(argv[i]);
		if (nbr > UINT_MAX)
			return (0);
		(*args)[i - 1] = nbr;
		i++;
	}
	return (1);
}

int			ft_init_struct(int argc, char **argv, t_philo *philo)
{
	if (!(philo->args = malloc(sizeof(unsigned int) * argc)))
		return (ft_error_free(1, 0, philo));
	philo->args[argc - 1] = 0;
	if (!(philo->write_mutex = malloc(sizeof(pthread_mutex_t))))
		return (ft_error_free(1, 1, philo));
	if (!(philo->death_mutex = malloc(sizeof(pthread_mutex_t))))
		return (ft_error_free(1, 2, philo));
	if (!(philo->ret = malloc(sizeof(int))))
		return (ft_error_free(1, 3, philo));
	philo->ret[0] = 0;
	if (argc < 5 || argc > 6)
		return (ft_error_free(2, 4, philo));
	if (!ft_argv_to_int(&philo->args, argc, argv))
		return (ft_error_free(2, 4, philo));
	if (!(philo->philo_nbr = malloc(sizeof(pthread_t) * philo->args[0])))
		return (ft_error_free(1, 4, philo));
	if (!(philo->forks_mutex =
						malloc(sizeof(pthread_mutex_t) * philo->args[0])))
		return (ft_error_free(1, 5, philo));
	philo->argc = argc;
	return (1);
}

int			ft_mutexs_init(t_philo *philo)
{
	unsigned int	i;

	if (pthread_mutex_init(&philo->write_mutex[0], NULL))
		return (ft_destroy_mutexes(philo, 1, 0, 0));
	if (pthread_mutex_init(&philo->death_mutex[0], NULL))
		return (ft_destroy_mutexes(philo, 1, 1, 0));
	i = 0;
	while (i < philo->args[0])
	{
		if (pthread_mutex_init(&philo->forks_mutex[i], NULL))
			return (ft_destroy_mutexes(philo, 1, 3, i));
		i++;
	}
	return (1);
}

t_last_meal	*ft_create_last_meal(t_philo *philo)
{
	t_last_meal	*last_meal;

	if (!(last_meal = malloc(sizeof(t_last_meal))))
		return (ft_error_last_meal_free(1, 0, last_meal, philo));
	if (pthread_mutex_init(&last_meal->last_meal_mutex[0], NULL))
		return (ft_error_last_meal_free(2, 1, last_meal, philo));
	if (pthread_mutex_init(&last_meal->enough_eat_mutex[0], NULL))
		return (ft_error_last_meal_free(2, 2, last_meal, philo));
	last_meal->time = philo->time;
	last_meal->init_time = philo->time;
	last_meal->i = philo->i;
	last_meal->ret = philo->ret;
	pthread_mutex_lock(&philo->death_mutex[0]);
	last_meal->death_mutex = philo->death_mutex;
	pthread_mutex_unlock(&philo->death_mutex[0]);
	pthread_mutex_lock(&philo->write_mutex[0]);
	last_meal->write_mutex = philo->write_mutex;
	pthread_mutex_unlock(&philo->write_mutex[0]);
	last_meal->death_time = philo->death_time;
	last_meal->enough_eat = 0;
	if (pthread_create(&last_meal->death_check,
						NULL, ft_check_death, (void *)last_meal))
		return (ft_error_last_meal_free(3, 3, last_meal, philo));
	return (last_meal);
}
