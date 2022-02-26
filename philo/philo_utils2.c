/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imabid <imabid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 13:29:07 by imabid            #+#    #+#             */
/*   Updated: 2022/02/26 18:37:21 by imabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	check_death(t_all *all, t_philo *philo)
{
	int	i;
	while (!(all->dead))
	{
		i = -1;
		while (++i < all->ph_nb)
		{
			pthread_mutex_lock(&philo->eat);
			if (current_timestamp() - philo[i].eat_time > all->tm_to_die)
			{
				// if (all->must_eat != philo->nb_of_eat)
					philo_write(all, i, "died");
				all->dead = 1;
			}
			pthread_mutex_unlock(&philo->eat);
			usleep(1000);
		}
		if (all->must_eat == philo->nb_of_eat && all->dead)
			break ;
	}
}

void	philo_destroy(t_all *all)
{
	int	i;

	i = -1;
	while (++i < all->ph_nb)
	{
		pthread_join(all->philo[i].th_philo, NULL);
	}
	pthread_mutex_destroy(&all->write);
}

void    my_sleep(t_all *all,long do_time, long time_to)
{
    
	usleep(time_to * 1000 - 20000);
	while (!all->dead)
	{
		if (current_timestamp() - do_time >= time_to)
			break ;
		usleep(50);
	}
}