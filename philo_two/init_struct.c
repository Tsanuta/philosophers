/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olidon <olidon@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 10:39:39 by olidon            #+#    #+#             */
/*   Updated: 2021/01/19 14:39:48 by olidon           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

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
	if (!(philo->ret = malloc(sizeof(int))))
		return (ft_error_free(1, 3, philo));
	philo->ret[0] = 0;
	if (argc < 5 || argc > 6)
		return (ft_error_free(2, 4, philo));
	if (!ft_argv_to_int(&philo->args, argc, argv))
		return (ft_error_free(2, 4, philo));
	if (!(philo->philo_nbr = malloc(sizeof(pthread_t) * philo->args[0])))
		return (ft_error_free(1, 4, philo));
	philo->argc = argc;
	return (1);
}

int			ft_mutexs_init(t_philo *philo)
{
	sem_unlink("/writesem");
	if ((SEM_FAILED ==
		(philo->write_mutex = sem_open("/writesem", O_CREAT, S_IRWXU, 1))))
		return (ft_destroy_mutexes(philo, 1, 0));
	sem_unlink("/deathsem");
	if (SEM_FAILED ==
		(philo->death_mutex = sem_open("/deathsem", O_CREAT, S_IRWXU, 1)))
		return (ft_destroy_mutexes(philo, 1, 1));
	sem_unlink("/forkssem");
	if (SEM_FAILED == (philo->forks_mutex =
	sem_open("/forkssem", O_CREAT, S_IRWXU, philo->args[0])))
		return (ft_destroy_mutexes(philo, 1, 2));
	return (1);
}

static void	*ft_init_last_meal(t_last_meal *last_meal, t_philo *philo)
{
	if (!(last_meal->last_meal_name =
							ft_strjoin("/lastmeal", ft_itoa(last_meal->i))))
		return (ft_error_last_meal_free(1, 1, last_meal, philo));
	if (!(last_meal->enough_eat_name =
							ft_strjoin("/enougheat", ft_itoa(last_meal->i))))
		return (ft_error_last_meal_free(1, 2, last_meal, philo));
	sem_unlink(last_meal->last_meal_name);
	if (SEM_FAILED == (last_meal->last_meal_mutex =
	sem_open(last_meal->last_meal_name, O_CREAT, S_IRWXU, 1)))
		return (ft_error_last_meal_free(2, 3, last_meal, philo));
	sem_unlink(last_meal->enough_eat_name);
	if (SEM_FAILED == (last_meal->enough_eat_mutex =
	sem_open(last_meal->enough_eat_name, O_CREAT, S_IRWXU, 1)))
		return (ft_error_last_meal_free(2, 4, last_meal, philo));
	return ((void *)1);
}

t_last_meal	*ft_create_last_meal(t_philo *philo)
{
	t_last_meal	*last_meal;

	if (!(last_meal = malloc(sizeof(t_last_meal))))
		return (ft_error_last_meal_free(1, 0, last_meal, philo));
	last_meal->i = philo->i;
	sem_wait(philo->death_mutex);
	last_meal->death_mutex = philo->death_mutex;
	sem_post(philo->death_mutex);
	last_meal->ret = philo->ret;
	if (!ft_init_last_meal(last_meal, philo))
		return (NULL);
	last_meal->time = philo->time;
	last_meal->init_time = philo->time;
	sem_wait(philo->write_mutex);
	last_meal->write_mutex = philo->write_mutex;
	sem_post(philo->write_mutex);
	last_meal->death_time = philo->death_time;
	last_meal->enough_eat = 0;
	if (pthread_create(&last_meal->death_check,
						NULL, ft_check_death, (void *)last_meal))
		return (ft_error_last_meal_free(3, 5, last_meal, philo));
	return (last_meal);
}
