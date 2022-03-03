/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imabid <imabid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 19:39:20 by imabid            #+#    #+#             */
/*   Updated: 2022/03/03 11:45:29 by imabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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
	sem_wait(all->write);
	ft_putnbr_fd(t, 1);
	ft_putchar_fd(' ', 1);
	ft_putnbr_fd(i + 1, 1);
	ft_putchar_fd(' ', 1);
	ft_putendl_fd(str, 1);
	sem_post(all->write);
}
