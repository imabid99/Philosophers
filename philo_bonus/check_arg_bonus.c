/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imabid <imabid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 19:29:26 by imabid            #+#    #+#             */
/*   Updated: 2022/02/26 09:32:19 by imabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_error(char *error)
{
	printf("Error\n%s", error);
	exit(1);
}

void	init1(t_all *all)
{
	int	i;

	i = -1;
	all->first_time = current_timestamp();
	all->philo = malloc(sizeof(t_philo) * (all->ph_nb + 1));
	all->fork = malloc(sizeof(pthread_mutex_t) * (all->ph_nb + 1));
	while (++i < all->ph_nb)
	{
		all->philo[i].index = i;
		all->philo[i].left_fork = i;
		all->philo[i].right_fork = (i + 1) % all->ph_nb;
		all->philo[i].eat_time = current_timestamp();
		all->philo[i].all = all;
		all->dead = 0;
	}
}

void	mutex_init(t_all *all)
{
	int	i;

	i = -1;
	while (++i < all->ph_nb)
	{
		pthread_mutex_init(&all->fork[i], NULL);
	}
	pthread_mutex_init(&all->write, NULL);
	pthread_mutex_init(&all->philo->eat, NULL);
}

void	check_arg(int ac, char **av, t_all *all)
{
	if (ac != 6 && ac != 5)
		print_error(N_ARG);
	ft_check(ac, av);
	all->ph_nb = ft_atoi(av[1]);
	if (all->ph_nb <= 0)
		print_error(PH_NB);
	all->tm_to_die = ft_atoi(av[2]);
	if (all->tm_to_die <= 0)
		print_error(T_DIE);
	all->tm_to_eat = ft_atoi(av[3]);
	if (all->tm_to_eat <= 0)
		print_error(T_EAT);
	all->tm_to_sleep = ft_atoi(av[4]);
	if (all->tm_to_sleep <= 0)
		print_error(T_SLEEP);
	if (ac == 6)
	{
		all->count_of_eating = ft_atoi(av[5]);
		if (all->count_of_eating <= 0)
			print_error(C_EAT);
	}
	else
		all->count_of_eating = -1;
	init1(all);
	mutex_init(all);
}

void	ft_check(int ac, char **av)
{
	int	i;
	int	j;
	i = 0;
	while (++i < ac)
	{
		j = -1;
		while (av[i][++j])
			if (av[i][j] < '0' || av[i][j] > '9')
				print_error(N_NUB);
	}
}
