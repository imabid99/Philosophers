/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imabid <imabid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 19:26:48 by imabid            #+#    #+#             */
/*   Updated: 2022/03/02 18:10:40 by imabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	philo_eat(t_philo *philo)
{
	t_all	*all;

	all = philo->all;
	sem_wait(all->fork);
	philo_write(all, philo->index, "has taken a fork");
	sem_wait(all->fork);
	philo_write(all, philo->index, "has taken a fork");
	sem_wait(all->eat);
	philo_write(all, philo->index, "is eating");
	philo->h_eat = 1;
	philo->eat_time = current_timestamp();
	sem_post(all->eat);
	my_sleep(all, philo->eat_time, all->tm_to_eat);
	philo->h_eat = 0;
	philo->nb_of_eat++;
	sem_post(all->fork);
	sem_post(all->fork);
}

void	routine(t_philo *philo)
{
	t_all		*all;
	all = philo->all;
	philo->eat_time = current_timestamp();
	pthread_create(&philo->th_philo, NULL, check_death, philo);
	while (!all->dead)
	{
		philo_eat(philo);
		if (all->must_eat != -1 && philo->nb_of_eat
			>= all->must_eat)
			break;
		// if (all->all_eat)
		// 	exit(0);
		philo_write(all, philo->index, "is sleeping");
		philo->sleep_time = current_timestamp();
		my_sleep(all, philo->sleep_time, all->tm_to_sleep);
		philo_write(all, philo->index, "is thinking");
		usleep(50);
	}
	pthread_join(philo->th_philo,NULL);
	if(all->dead)
		exit(1);
	exit(0);
}

int		go_routine(t_all *all)
{
	int		i;
	t_philo	*philo;

	i = -1;
	philo = all->philo;
	while (++i < all->ph_nb)
	{
		philo[i].pr_philo = fork();
		if(philo[i].pr_philo < 0)
			return 1;
		else if(philo[i].pr_philo == 0)
			routine(&philo[i]);
		if (all->ph_nb == 1)
			one_philo(all, philo->index);
		usleep(50);
	}
	c_all(all);
	return 0;
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
