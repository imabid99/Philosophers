/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imabid <imabid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 19:26:48 by imabid            #+#    #+#             */
/*   Updated: 2022/02/28 08:50:09 by imabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_eat(t_philo *philo)
{
	t_all	*all;

	all = philo->all;
	long i;
	sem_wait(&all->fork[philo->left_fork]);
	philo_write(all, philo->index, "take left fork");
	sem_wait(&all->fork[philo->right_fork]);
	philo_write(all, philo->index, "take right fork");
	sem_wait(&all->eat);
	philo_write(all, philo->index, "is eating 🍗");
	philo->eat_time = current_timestamp();
	sem_post(&all->eat);
	usleep(all->tm_to_eat * 1000 - 20000);
	// if(philo->eat_time - current_timestamp() >= all->tm_to_eat)
	// 	usleep(50);
	while (1)
	{
		if (current_timestamp() - philo->eat_time >= all->tm_to_eat)
			break ;
		usleep(50);
	}
	philo->nb_of_eat++;
	sem_post(&all->fork[philo->left_fork]);
	sem_post(&all->fork[philo->right_fork]);
}

void	check_death(t_all *all, t_philo *philo)
{
    int	i;

	while(!(all->dead))
	{
		i = -1;
		while (++i < all->ph_nb)
		{
			pthread_mutex_lock(&philo->eat);
			if (current_timestamp() - philo[i].eat_time > all->tm_to_die)
			{
				philo_write(all, i, "died");
				all->dead = 1;
			}
			pthread_mutex_unlock(&philo->eat);
			// usleep(1000);
		}
		if(all->count_of_eating == philo->nb_of_eat)
			break;
	}
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
		if(all->count_of_eating == philo->nb_of_eat)
			break;
		philo_write(all, philo->index, "is sleeping");
		philo_write(all, philo->index, "is thinking");
		usleep(all->tm_to_sleep * 1000);
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

int	main(int ac, char **av)
{
	t_all		all;
	pthread_t	*t;
	int			i;

	i = 0;
	check_arg(ac, av, &all);
	go_routine(&all);
	return (0);
}
