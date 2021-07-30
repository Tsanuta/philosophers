/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olidon <olidon@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 10:39:39 by olidon            #+#    #+#             */
/*   Updated: 2021/01/21 14:20:18 by olidon           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

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
	if (argc < 5 || argc > 6)
		return (ft_error_free(2, 1, philo));
	if (!ft_argv_to_int(&philo->args, argc, argv))
		return (ft_error_free(2, 1, philo));
	if (!(philo->philo_nbr = malloc(sizeof(pid_t) * philo->args[0])))
		return (ft_error_free(1, 1, philo));
	if (!(philo->last_meal_sem = malloc(sizeof(sem_t *) * philo->args[0])))
		return (ft_error_free(1, 2, philo));
	if (!(philo->last_meal_name = malloc(sizeof(char *) * philo->args[0])))
		return (ft_error_free(1, 3, philo));
	if (!(philo->enough_eat_sem = malloc(sizeof(sem_t *) * philo->args[0])))
		return (ft_error_free(1, 4, philo));
	if (!(philo->enough_eat_name = malloc(sizeof(char *) * philo->args[0])))
		return (ft_error_free(1, 5, philo));
	if (!(philo->ate_enough_sem = malloc(sizeof(sem_t *) * philo->args[0])))
		return (ft_error_free(1, 6, philo));
	if (!(philo->ate_enough_name = malloc(sizeof(char *) * philo->args[0])))
		return (ft_error_free(1, 7, philo));
	philo->argc = argc;
	return (1);
}

int			ft_create_last_meal(t_phi *philo)
{
	if (pthread_create(&philo->death_check,
						NULL, ft_check_death, (void *)philo))
	{
		write(1, "Death check thread creation failed\n", 35);
		return (1);
	}
	return (0);
}
