/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olidon <olidon@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 15:07:34 by olidon            #+#    #+#             */
/*   Updated: 2021/01/19 14:18:59 by olidon           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

size_t			ft_strlen(const char *s)
{
	unsigned int i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

static unsigned	ft_checknsize(long a)
{
	unsigned int nsize;

	nsize = 0;
	if (a < 0)
		nsize++;
	while (a > 9 || a < -9)
	{
		a = a / 10;
		nsize++;
	}
	return (nsize);
}

static char		*ft_fillstr(char *str, long a, unsigned int nsize)
{
	while (a > 9)
	{
		str[nsize] = a % 10 + 48;
		a = a / 10;
		nsize--;
	}
	str[nsize] = a % 10 + 48;
	return (str);
}

char			*ft_itoa(int n)
{
	long long		a;
	char			*str;
	unsigned int	nsize;

	a = n;
	nsize = ft_checknsize(a);
	if (!(str = (char *)malloc(sizeof(char) * (nsize + 2))))
		return (NULL);
	if (a < 0)
	{
		a = a * -1;
		str[0] = '-';
	}
	str[nsize + 1] = '\0';
	str = ft_fillstr(str, a, nsize);
	return (str);
}

char			*ft_strjoin(char *s1, char *s2)
{
	char	*str;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!s1 || !s2 ||
!(str = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1))))
		return (NULL);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		str[i] = s2[j];
		i++;
		j++;
	}
	str[i] = '\0';
	if (s2)
		free(s2);
	return (str);
}
