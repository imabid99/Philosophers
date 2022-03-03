/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imabid <imabid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 13:29:07 by imabid            #+#    #+#             */
/*   Updated: 2022/03/03 12:28:30 by imabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	must_eat(t_all *all, t_philo *philo)
{
	int	i;

	i = 0;
	while ((all->must_eat != -1) && (i < all->ph_nb)
		&& (philo[i].nb_of_eat >= all->must_eat))
		i++;
	if (i == all->ph_nb)
		all->all_eat = 1;
}

void	check_death(t_all *all, t_philo *philo)
{
	int	i;

	while (!(all->all_eat))
	{
		i = -1;
		while (++i < all->ph_nb && !(all->dead))
		{
			pthread_mutex_lock(&all->eat);
			if (current_timestamp() - philo[i].eat_time > all->tm_to_die
				&& !philo[i].h_eat)
			{
				philo_write(all, i, "died");
				all->dead = 1;
			}
			pthread_mutex_unlock(&all->eat);
		}
		if (all->dead)
			break ;
		must_eat(all, philo);
		usleep(1000);
	}
}

void	philo_destroy(t_all *all)
{
	int	i;

	i = -1;
	while (++i < all->ph_nb)
		pthread_mutex_destroy(&(all->fork[i]));
	pthread_mutex_destroy(&(all->eat));
	pthread_mutex_destroy(&(all->write));
}

void	my_sleep(t_all *all, long do_time, long time_to)
{
	usleep(time_to * 1000 - 20000);
	while (!all->dead)
	{
		if (current_timestamp() - do_time >= time_to)
			break ;
		usleep(50);
	}
}

void	one_philo(t_all *all, int i)
{
	my_sleep(all, current_timestamp(), all->tm_to_die);
	philo_write(all, i, "died");
	all->dead = 1;
}
