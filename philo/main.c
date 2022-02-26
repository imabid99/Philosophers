/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imabid <imabid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 19:26:48 by imabid            #+#    #+#             */
/*   Updated: 2022/02/26 18:34:13 by imabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_eat(t_philo *philo)
{
	t_all	*all;

	all = philo->all;
	pthread_mutex_lock(&all->fork[philo->left_fork]);
	philo_write(all, philo->index, "has taken a fork");
	pthread_mutex_lock(&all->fork[philo->right_fork]);
	philo_write(all, philo->index, "has taken a fork");
	pthread_mutex_lock(&all->philo->eat);
	philo_write(all, philo->index, "is eating");
	philo->eat_time = current_timestamp();
	pthread_mutex_unlock(&all->philo->eat);
	my_sleep(all, philo->eat_time, all->tm_to_eat);
	philo->nb_of_eat++;
	pthread_mutex_unlock(&all->fork[philo->left_fork]);
	pthread_mutex_unlock(&all->fork[philo->right_fork]);
}

void	*routine(void *v_philo)
{
	t_philo		*philo;
	t_all		*all;

	philo = (t_philo *)v_philo;
	all = philo->all;
	while (!all->dead)
	{
		philo_eat(philo);
		philo_write(all, philo->index, "is sleeping");
		if (all->must_eat == philo->nb_of_eat)
			break ;
		philo->sleep_time = current_timestamp();
		my_sleep(all, philo->sleep_time, all->tm_to_sleep);
		philo_write(all, philo->index, "is thinking");
	}
	return (NULL);
}

void	go_routine(t_all *all)
{
	int		i;
	t_philo	*philo;

	i = -1;
	philo = all->philo;
	while (++i < all->ph_nb)
	{
		pthread_create(&all->philo[i].th_philo, NULL, &routine, &all->philo[i]);
		usleep(50);
	}
	check_death(all, philo);
	// philo_destroy(all);
}

int	main(int ac, char **av)
{
	t_all		all;
	int			i;

	i = 0;
	check_arg(ac, av, &all);
	go_routine(&all);
	return (0);
}
