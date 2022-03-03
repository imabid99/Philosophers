/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_arg_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imabid <imabid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 19:29:26 by imabid            #+#    #+#             */
/*   Updated: 2022/03/03 08:58:12 by imabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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
	while (++i < all->ph_nb)
	{
		all->philo[i].index = i;
		all->philo[i].eat_time = 0;
		all->philo[i].all = all;
		all->philo[i].nb_of_eat = 0;
		all->philo[i].all_eat = 0;
	}
}

void	sema_init(t_all *all)
{
	sem_unlink("fork");
	sem_unlink("write");
	sem_unlink("eat");
	all->fork = sem_open("fork", O_CREAT, S_IRWXU,
			all->ph_nb);
	all->write = sem_open("write", O_CREAT, S_IRWXU, 1);
	all->eat = sem_open("eat", O_CREAT, S_IRWXU, 1);
}

void	check_arg(int ac, char **av, t_all *all)
{
	ft_check(ac, av);
	all->ph_nb = ft_atoi(av[1]);
	if (all->ph_nb <= 0 || all->ph_nb > 200)
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
	all->dead = 0;
	if (ac == 6)
	{
		all->must_eat = ft_atoi(av[5]);
		if (all->must_eat <= 0)
			print_error(C_EAT);
	}
	else
		all->must_eat = -1;
	init1(all);
	sema_init(all);
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
			if ((av[i][j] < '0' || av[i][j] > '9'))
				print_error(N_NUB);
	}
}
