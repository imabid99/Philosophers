/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils2_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imabid <imabid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 13:29:07 by imabid            #+#    #+#             */
/*   Updated: 2022/03/02 18:11:30 by imabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*check_death(void *v_philo)
{
	t_philo		*philo;
	t_all		*all;

	philo = (t_philo *)v_philo;
	all = philo->all;
	// int	i;

	// while (!(all->all_eat))
	// {
	// 	i = -1;
	while (1)
	{
		sem_wait(all->eat);
		if (current_timestamp() - philo->eat_time > all->tm_to_die
			&& !philo->h_eat)
		{
			philo_write(all, philo->index, "died");
			all->dead = 1;
		}
		sem_post(all->eat);
	}
		exit(1);
	// 	i = 0;
	// 	while ((all->must_eat != -1) && (i < all->ph_nb)
	// 		&& (philo[i].nb_of_eat >= all->must_eat))
	// 		i++;
	// 	if (i == all->ph_nb)
	// 		all->all_eat = 1;
	// }
	return NULL;
}

void	c_all(t_all *all)
{
	int	i;
	// while (++i < all->ph_nb)
	// 	pthread_mutex_destroy(&(all->fork[i]));
	waitpid(-1, NULL, 0);
	i = 0;
	while(i++ < all->ph_nb)
	{
		kill(all->philo[i].pr_philo, SIGKILL);
	}
	sem_close(all->fork);
	sem_unlink("fork");
	sem_close(all->eat);
	sem_unlink("fork");
	sem_close(all->write);
	sem_unlink("fork");
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
