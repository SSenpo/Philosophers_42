/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmago <mmago@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 16:54:07 by mmago             #+#    #+#             */
/*   Updated: 2022/05/23 20:22:39 by mmago            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <sys/time.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <string.h>

# define YELLOW		"\x1b[33m"
# define BLUE		"\x1b[34m"
# define MAGENTA	"\x1b[35m"
# define CYAN		"\x1b[36m"
# define RESET		"\x1b[0m"
# define RED		"\033[31m"

# define ERROR_NUM_ARG	"Error: wrong number of arguments\n"
# define ERROR_INP_ARG	"Error: invalid argument(-s)\n"
# define ERROR_MALLOC	"Error: memory allocation error\n"
# define ERROR_MUTEX	"Error: mutex(-es) couldn't be init"
# define ERROR_THREAD	"Error: thread can't be created"
# define ERROR_THRJOIN	"Error: thread can't be joined"
# define ERROR_NUM_ARG_INT	2
# define ERROR_INP_ARG_INT	3
# define ERROR_MALLOC_INT	4
# define ERROR_MUTEX_INT	5
# define ERROR_THREAD_INT	6
# define ERROR_THRJOIN_INT	7
# define SUCCESS			0
# define FAIL				1
# define ERROR				-1

typedef struct s_philo
{
	pthread_t			thread_id;
	long				last_eat_time;
	pthread_mutex_t		*left_id;
	pthread_mutex_t		*right_id;
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
	int		flag;
	long	start_time;
}				t_args;

typedef struct s_mutex
{
	pthread_mutex_t	*fork;
	pthread_mutex_t	output;
	pthread_mutex_t	data_race;
	pthread_mutex_t	death_race;
}				t_mutex;

typedef struct s_all
{
	t_args			*args;
	t_mutex			*mutex;
	t_philo			*philo;
	pthread_t		end;
}				t_all;

// * Main function's *
int			main(int ac, char **av);
int			ft_parse_arg(int ac, char **av);
int			ft_check_arg(char **av);

// * Utils function's *
int			ft_error(int c);
long		ft_get_cur_time(void);
int			ft_atoi(const char *str);
int			ft_free(t_all *all);
int			death_checker(t_philo *philo);

// * Thread functiom's *
int			ft_init_philos(t_all *all);
int			ft_mutex_init(t_all *all);
void		ft_thread_init(t_all *all);
void		*ft_try(void *data);
void		*ft_check_end(void *data);

// * Action function's *
void		print_message(char *str, t_philo *philo);
void		my_sleep(long time_to_wait, t_philo *philo);
void		get_last_meal(t_philo *philo);
void		check_end_two(t_all *all);
int			eating(t_philo *philo);

#endif
