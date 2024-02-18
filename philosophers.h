/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zabdulza <zabdulza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 09:39:43 by zabdulza          #+#    #+#             */
/*   Updated: 2024/01/20 10:50:14 by zabdulza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <sys/time.h>
# include <pthread.h>

# define FALSE	0
# define TRUE	1
# define ERR_ARGS "All arguments must be set as greater than zero integers\
 and less than 2147483647.\n"
# define ERR_CMD "CMD error expected and correct is . Ex.: ./philo [nb_de_philo] [time_to_die] [time_to_eat]\
 [time_to_sleep] (NOTE: [nb_time_must_eat] is optional.)\n"
# define ERR_MAX "Number of philos are not correct. Maximum: 200\n"

typedef struct s_control	t_control;
typedef struct s_philo		t_philo;

typedef struct s_philo
{
	pthread_t	tid;
	int			id;
	int			meals_eaten;
	long long	t_lastmeal;
	int			l_fork;
	int			r_fork;
	t_control	*args;
}	t_philo;

typedef struct s_control
{
	int				nb_philo;
	long long		t0;
	long long		t_to_die;
	long long		t_to_eat;
	long long		t_to_sleep;
	int				max_meals;
	t_philo			*philo;
	pthread_mutex_t	*fork;
	pthread_mutex_t	cout;
	pthread_mutex_t	checker;
	int				error;
	int				end_meal;
	int				game_over;
}	t_control;

// helper_functions
int			ft_atoi(const char *str);
void		ft_bzero(void *str, size_t n);
void		*ft_calloc(size_t count, size_t n);
void		print(t_philo *p, char *condition);

// philosopher_actions
void		*single_phil(void *p);
void		start_philos(t_control *input);
void		*task_phil(void *p);
void		end_philos(t_control *input);
void		checker(t_control *c);
void		monitor_dead(t_philo *p);

// philosopher_actions2
void		eat_philo(t_philo *ph);
void		think_philo(t_philo *ph);
void		zzz_philo(t_philo *ph);

// philosopher_clock
long long	start_clock(void);
long long	time_stamp(t_control *input);
void		sleep_time(t_philo *p, int t_wait);

// simulation_setup
int			arg_validate(int argc, char **argv);
void		controls_setup(char **argv, t_control *input);
void		philo_setup(t_control *input);

#endif
