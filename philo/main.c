/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imabid <imabid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 19:26:48 by imabid            #+#    #+#             */
/*   Updated: 2022/03/01 16:53:31 by imabid           ###   ########.fr       */
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
	pthread_mutex_lock(&all->eat);
	philo_write(all, philo->index, "is eating");
	philo->h_eat = 1;
	philo->eat_time = current_timestamp();
	pthread_mutex_unlock(&all->eat);
	my_sleep(all, philo->eat_time, all->tm_to_eat);
	philo->h_eat = 0;
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
		if (all->must_eat != -1 && philo->nb_of_eat
			>= all->must_eat)
			break ;
		if (all->all_eat)
			break ;
		philo_write(all, philo->index, "is sleeping");
		philo->sleep_time = current_timestamp();
		my_sleep(all, philo->sleep_time, all->tm_to_sleep);
		philo_write(all, philo->index, "is thinking");
		usleep(50);
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
		philo[i].eat_time = current_timestamp();
		if (all->ph_nb == 1)
			one_philo(all, philo->index);
		usleep(50);
	}
	check_death(all, philo);
	philo_destroy(all);
}

int	main(int ac, char **av)
{
	t_all		all;
	int			i;

	i = 0;
	if (ac != 6 && ac != 5)
		print_error(N_ARG);
	check_arg(ac, av, &all);
	go_routine(&all);
	return (0);
}
