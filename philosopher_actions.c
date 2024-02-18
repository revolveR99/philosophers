/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_actions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zabdulza <zabdulza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 09:46:13 by zabdulza          #+#    #+#             */
/*   Updated: 2024/01/20 11:26:09 by zabdulza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// Purpose: Initiates the philosopher threads and handles the main flow of the
// dining philosophers problem.
// If there is only one philosopher, it calls single_phil function for a 
// single philosopher.
// Otherwise, it creates threads for each philosopher using pthread_create and 
// starts the dining process by calling checker function until the game is over.

void	start_philos(t_control *input)
{
	int		i;

	if (input->nb_philo == 1)
	{
		single_phil(input->philo);
	}
	else
	{
		i = -1;
		while (++i < input->nb_philo)
			pthread_create(&input->philo[i].tid, NULL, \
			&task_phil, (void *) &input->philo[i]);
		while (input->game_over == FALSE)
			checker(input);
	}
}

// Purpose: Represents the behavior of a philosopher.
// Sleeps for a short duration if the philosopher's ID 
//is odd (to stagger their actions).
// Enters a loop where the philosopher repeatedly eats, sleeps,and thinks 
//until the specified number of meals is reached or the game is over.
void	*task_phil(void *p)
{
	t_philo		*ph;
	t_control	*input;

	ph = (t_philo *)p;
	input = ph->args;
	if (ph->id % 2)
		usleep(1500);
	while (input->game_over == FALSE)
	{
		if (input->max_meals > 0 && ph->meals_eaten == input->max_meals)
			break ;
		eat_philo(ph);
		zzz_philo(ph);
		think_philo(ph);
	}
	return (NULL);
}

// Purpose: Monitors the state of the dining philosophers.
// Checks for philosopher deaths and updates the game state accordingly.
// If the maximum number of meals is specified, it checks if all philosophers 
// have eaten that number of meals, marking the game as over if true.
// Sleeps for a short duration to avoid excessive checking.
void	checker(t_control *c)
{
	int	meal_i;
	int	death_i;

	meal_i = 0;
	death_i = 0;
	while (c->game_over == FALSE)
	{
		monitor_dead(&c->philo[death_i]);
		if (c->max_meals > 0)
		{
			while (meal_i < c->nb_philo)
			{
				if (c->philo[meal_i].meals_eaten < c->max_meals)
					break ;
				meal_i++;
			}
			if (meal_i == c->nb_philo)
				c->game_over = TRUE;
		}
		usleep(5000);
		if (death_i == c->nb_philo -1)
			death_i = -1;
		death_i++;
	}
}

// Purpose: Monitors an individual philosopher for a potential death scenario.
// If the time elapsed since the philosopher's last meal is greater than or 
//equal to the time allowed to die (t_to_die), it prints a death message, 
//sets the game state to over, and releases a mutex.
void	monitor_dead(t_philo *p)
{
	pthread_mutex_lock(&p->args->checker);
	if ((time_stamp(p->args) - p->t_lastmeal) >= p->args->t_to_die)
	{
		print(p, "died \xF0\x9F\x92\x80");
		p->args->game_over = TRUE;
	}
	pthread_mutex_unlock(&p->args->checker);
}

// Purpose: Cleans up resources and waits for all philosopher threads to finish.
// Joins all philosopher threads to ensure they complete before 
//releasing resources.
// Destroys mutexes used for forks, console output, and the global checker.
// Frees allocated memory for philosopher and fork structures, as well as the 
//control structure.
void	end_philos(t_control *input)
{
	int	i;

	i = input->nb_philo;
	while (--i >= 0)
		pthread_join(input->philo[i].tid, NULL);
	while (++i < input->nb_philo)
		pthread_mutex_destroy(&input->fork[i]);
	pthread_mutex_destroy(&input->cout);
	pthread_mutex_destroy(&input->checker);
	free(input->philo);
	free(input->fork);
	free(input);
}
