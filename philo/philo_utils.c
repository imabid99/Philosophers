/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imabid <imabid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 19:39:20 by imabid            #+#    #+#             */
/*   Updated: 2022/02/24 16:42:07 by imabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	s;
	int	r;

	i = 0;
	r = 0;
	s = 1;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'
		|| str[i] == '\v' || str[i] == '\r' || str[i] == '\f')
		i++;
	if (str[i] == '-')
		s *= -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while ((str[i] >= '0' && str[i] <= '9') && str[i] != '\0')
	{
		r = r * 10 + str[i] - 48;
		i++;
	}
	return (r * s);
}

int	ft_isdigit(int c)
{
	int	i;

	i = -1;
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}

long	current_timestamp(void)
{
	struct timeval	te;

	gettimeofday(&te, NULL);
	return ((te.tv_sec * 1000) + te.tv_usec / 1000);
}

void	philo_write(t_all *all, int i, char *str)
{
	long	t;

	t = current_timestamp() - all->first_time ;
	pthread_mutex_lock(&all->write);
	if (!all->dead)
	{
		printf("%ld ", t);
		printf(" %i ", i + 1);
		printf("%s\n", str);
	}
	pthread_mutex_unlock(&all->write);
}
