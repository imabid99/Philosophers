/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imabid <imabid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 19:29:03 by imabid            #+#    #+#             */
/*   Updated: 2022/02/28 15:06:12 by imabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <semaphore.h>
# include <fcntl.h>
# include <signal.h>


# define  PH_NB "ERROR : Number of philo\n"
# define  T_DIE "ERROR : Time to die\n"
# define  T_EAT "ERROR : Time to eat\n"
# define  T_SLEEP "ERROR : Time to sleep\n"
# define  C_EAT "ERROR : Number of times each philosopher must eat\n"
# define  N_ARG "ERROR : Number of args\n"
# define  N_NUB "ERROR : Digit numbers\n"

typedef struct s_philo
{
	int				left_fork;
	int				right_fork;
	int				index;
	long			eat_time;
	long			sleep_time;
	int				nb_of_eat;
	int				h_eat;
	sem_t		th_philo;
	struct s_all	*all;
}	t_philo;

typedef struct s_all
{
	int				ph_nb;
	int				tm_to_die;
	int				tm_to_eat;
	int				tm_to_sleep;
	int				must_eat;
	int				dead;
	int				all_eat;
	long			first_time;
	sem_t	*fork;
	sem_t	write;
	sem_t	eat;
	t_philo			*philo;
}		t_all;

int		ft_atoi(const char *str);
int		ft_isdigit(int c);
void	check_arg(int ac, char **av, t_all *all);
long	current_timestamp(void);
void	philo_eat(t_philo *philo);
void	philo_write(t_all *all, int i, char *str);
void	philo_destroy(t_all *all);
void	ft_check(int ac, char **av);
void	check_death(t_all *all, t_philo *philo);
void	my_sleep(t_all *all, long do_time, long time_to);
void	print_error(char *error);

#endif