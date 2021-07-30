/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olidon <olidon@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 13:06:49 by olidon            #+#    #+#             */
/*   Updated: 2021/01/19 14:40:48 by olidon           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int					ft_is_last_fork(t_philo *philo)
{
	if (philo->i != philo->args[0])
		return (philo->i);
	else
		return (0);
}

int					ft_isnumber(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

unsigned long long	ft_atoi(char *str)
{
	unsigned int		i;
	unsigned long long	nbr;

	i = 0;
	nbr = 0;
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		nbr = nbr * 10 + (str[i] - 48);
		i++;
	}
	return (nbr);
}

void				ft_putstr(char *s)
{
	unsigned int i;

	i = 0;
	while (s[i] != '\0')
		i++;
	if (s)
		write(1, s, i);
}

void				ft_sleep_time(long int ref_time)
{
	struct timeval	tv;
	long int		start_time;
	long int		end_time;

	gettimeofday(&tv, NULL);
	start_time = tv.tv_sec * 1000000 + tv.tv_usec;
	end_time = start_time;
	while (end_time - start_time <= ref_time)
	{
		gettimeofday(&tv, NULL);
		end_time = tv.tv_sec * 1000000 + tv.tv_usec;
	}
}
