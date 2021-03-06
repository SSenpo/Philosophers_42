/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmago <mmago@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 16:54:07 by mmago             #+#    #+#             */
/*   Updated: 2022/06/13 17:29:49 by mmago            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <semaphore.h>
# include <signal.h>
# include <sys/time.h>

# define YELLOW		"\x1b[33m"
# define BLUE		"\x1b[34m"
# define MAGENTA	"\x1b[35m"
# define CYAN		"\x1b[36m"
# define RESET		"\x1b[0m"
# define RED		"\033[31m"

# define ERROR_NUM_ARG		"Error: wrong number of arguments\n"
# define ERROR_INP_ARG		"Error: invalid argument(-s)\n"
# define ERROR_MALLOC		"Error: memory allocation error\n"
# define ERROR_SEMOPEN		"Error: failed to open semaphore\n"
# define ERROR_PID			"Error: failed to create process\n"
# define ERROR_NUM_ARG_INT	2
# define ERROR_INP_ARG_INT	3
# define ERROR_MALLOC_INT	4
# define ERROR_SEMOPEN_INT	8
# define ERROR_PID_INT		9
# define SUCCESS			0
# define FAIL				1
# define ERROR				-1

typedef struct s_philo
{
	pid_t				*pid;
	long				last_eat_time;
	int					philo_id;
	int					count_eat;
	int					dead_flag;
	struct s_all		*all;
}				t_philo;

typedef struct s_args
{
	int		num_ph;
	int		time_die;
	int		time_eat;
	int		time_sleep;
	int		must_eat;
	long	start_time;
}				t_args;

typedef struct s_sema
{
	sem_t	*fork;
	sem_t	*output;
}				t_sema;

typedef struct s_all
{
	t_args			*args;
	t_sema			*sems;
	t_philo			*philo;
	pthread_t		end;
}				t_all;

void		ft_wait(t_all *all);
int			ft_init_procces(t_all *all);
int			ft_sem_init(t_all *all);
void		ft_create_check_thread(t_philo *philo);

// * Main function's *
int			main(int ac, char **av);
int			ft_parse_arg(int ac, char **av);
int			ft_check_arg(char **av);

// * Utils function's *
int			ft_error(int c);
long		ft_get_cur_time(void);
int			ft_atoi(const char *str);
int			ft_free(t_all *all);

// * Thread functiom's *
int			ft_init_philos(t_all *all);
void		ft_try(t_philo *philo);
void		*ft_check_end(void *data);

// * Action function's *
void		print_message(char *str, t_philo *philo);
void		my_sleep(long time_to_wait, t_philo *philo);
void		get_last_meal(t_philo *philo);
int			eating(t_philo *philo);

#endif
