/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fork_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olidon <olidon@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 11:42:32 by olidon            #+#    #+#             */
/*   Updated: 2021/01/15 11:44:31 by olidon           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

int		ft_fork_error(t_philo *philo, unsigned int index)
{
	unsigned int	j;

	j = 0;
	write(1, "Fork error\n", 11);
	while (j < index)
	{
		kill(philo->philo_nbr[j], EXIT_SUCCESS);
		j++;
	}
	return (1);
}
