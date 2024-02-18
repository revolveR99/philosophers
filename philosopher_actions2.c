/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_actions2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zabdulza <zabdulza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 09:56:04 by zabdulza          #+#    #+#             */
/*   Updated: 2024/01/20 11:22:43 by zabdulza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// Purpose: Represents the behavior of a philosopher when there is only one 
// philosopher in the system.
// Locks the left fork.
// Prints a message indicating that the philosopher has taken a fork.
// Sets the last meal timestamp and sleeps for the specified time to 
//simulate the philosopher eating.
// Prints a death message, sets the game state to over, and releases 
//the left fork.
void	*single_phil(void *p)
{
	t_philo	*ph;

	ph = (t_philo *)p;
	pthread_mutex_lock(&ph->args->fork[ph->l_fork]);
	print(ph, "has taken a fork 🍽️");
	ph->t_lastmeal = time_stamp(ph->args);
	sleep_time(ph, ph->args->t_to_die);
	print(ph, "died ☠️");
	ph->args->game_over = TRUE;
	return (NULL);
}

// Purpose: Simulates a philosopher's behavior during the eating phase.
// If the game is not over, locks both the left and right forks.
// Prints messages indicating that the philosopher has taken both forks 
//and is currently eating.
// Updates the last meal timestamp, increments the number of meals eaten, 
//and sleeps for the specified eating time.
// Releases both forks.
void	eat_philo(t_philo *ph)
{
	if (ph->args->game_over == FALSE)
	{
		pthread_mutex_lock(&ph->args->fork[ph->l_fork]);
		print(ph, "has taken a fork 🍽️");
		pthread_mutex_lock(&ph->args->fork[ph->r_fork]);
		print(ph, "has taken a fork 🍽️");
		print(ph, "is eating 🧆");
		ph->t_lastmeal = time_stamp(ph->args);
		ph->meals_eaten += 1;
		sleep_time(ph, ph->args->t_to_eat);
		pthread_mutex_unlock(&ph->args->fork[ph->l_fork]);
		pthread_mutex_unlock(&ph->args->fork[ph->r_fork]);
	}
}

// Purpose: Simulates a philosopher's behavior during the thinking phase.
// Prints a message indicating that the philosopher is thinking.
// Note: This function does not involve any mutex locking or unlocking since 
//thinking does not require shared resources.
void	think_philo(t_philo *ph)
{
	if (ph->args->game_over == FALSE)
		print(ph, "is thinking 🤔");
}

// Purpose: Simulates a philosopher's behavior during the sleeping phase.
// If the game is not over, prints a message indicating that the philosopher
// is sleeping.
// Sleeps for the specified sleeping time.
void	zzz_philo(t_philo *ph)
{
	if (ph->args->game_over == FALSE)
	{
		print(ph, "is sleeping 🥱");
		sleep_time(ph, ph->args->t_to_sleep);
	}
}
