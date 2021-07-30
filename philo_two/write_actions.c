/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olidon <olidon@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 10:27:34 by olidon            #+#    #+#             */
/*   Updated: 2021/01/19 13:28:57 by olidon           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

static void	ft_putnbr_buff(long int n, int *index, char *buff)
{
	long	a;
	int		nb1;

	a = n;
	if (a > 9)
		ft_putnbr_buff(a / 10, index, buff);
	(*index)++;
	nb1 = a % 10 + 48;
	buff[*index] = nb1;
}

static void	ft_putstr_buff(char *buff, char *str, int index)
{
	int		i;

	i = 0;
	while (str[i])
	{
		buff[index + i] = str[i];
		i++;
	}
	buff[index + i] = '\0';
}

static void	ft_write_action2(int phil_nbr, long int time, int action)
{
	char	buff[13 + 1 + 13 + 18];
	int		index;

	index = -1;
	if (action == 5)
		return ;
	ft_putnbr_buff(time, &index, buff);
	index++;
	buff[index] = ' ';
	ft_putnbr_buff(phil_nbr, &index, buff);
	index++;
	if (action == 0)
		ft_putstr_buff(buff, " has taken a fork\n", index);
	if (action == 1)
		ft_putstr_buff(buff, " is eating\n", index);
	if (action == 2)
		ft_putstr_buff(buff, " is sleeping\n", index);
	if (action == 3)
		ft_putstr_buff(buff, " is thinking\n", index);
	if (action == 4)
		ft_putstr_buff(buff, " died\n", index);
	ft_putstr(buff);
}

int			ft_write_action(int phil_nbr, t_philo *philo, int action)
{
	struct timeval	tv;
	long int		time;

	gettimeofday(&tv, NULL);
	time = (tv.tv_sec * 1000000 + tv.tv_usec - philo->time) / 1000;
	sem_wait(philo->write_mutex);
	sem_wait(philo->death_mutex);
	if (philo->ret[0] == 0)
	{
		sem_post(philo->death_mutex);
		ft_write_action2(phil_nbr, time, action);
	}
	else
	{
		sem_post(philo->death_mutex);
		sem_post(philo->write_mutex);
		return (1);
	}
	sem_post(philo->write_mutex);
	return (0);
}

int			ft_write_death(int phil_nbr, t_last_meal *last_meal)
{
	struct timeval	tv;
	long int		time;

	gettimeofday(&tv, NULL);
	time = (tv.tv_sec * 1000000 + tv.tv_usec - last_meal->init_time) / 1000;
	sem_wait(last_meal->write_mutex);
	sem_wait(last_meal->death_mutex);
	if (last_meal->ret[0] == 0)
	{
		last_meal->ret[0] = 1;
		sem_post(last_meal->death_mutex);
		ft_write_action2(phil_nbr, time, 4);
	}
	else
	{
		sem_post(last_meal->death_mutex);
		sem_post(last_meal->write_mutex);
		return (1);
	}
	sem_post(last_meal->write_mutex);
	return (0);
}
