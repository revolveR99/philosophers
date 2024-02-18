/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_clock.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zabdulza <zabdulza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 09:48:36 by zabdulza          #+#    #+#             */
/*   Updated: 2024/01/20 11:23:05 by zabdulza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// Purpose: Retrieves the current system time and returns it in milliseconds 
// since the epoch.
// Uses the gettimeofday function to get the current time.
// Converts the time to milliseconds and returns the result.
long long	start_clock(void)
{
	struct timeval	t0;

	gettimeofday(&t0, NULL);
	return ((t0.tv_sec * 1000) + (t0.tv_usec / 1000));
}

// Purpose: Computes the timestamp (in milliseconds) relative to the start 
// time of the dining philosophers simulation.
// Gets the current time using gettimeofday.
// Converts the time to milliseconds and subtracts the start time (input->t0) 
// to obtain the relative timestamp.
// Returns the computed timestamp.
long long	time_stamp(t_control *input)
{
	struct timeval	current;

	gettimeofday(&current, NULL);
	return (((current.tv_sec * 1000) + (current.tv_usec / 1000)) - input->t0);
}

// Purpose: Provides a sleep function with better precision than the standard 
// sleep function.
// Takes a t_philo structure and a waiting time (t_wait in milliseconds).
// Uses a loop to repeatedly check the time difference between the current time 
// and the starting time until it reaches the specified waiting time.
// Sleeps in small increments (1 millisecond) using usleep(1000) within the l
// oop to avoid busy waiting.
void	sleep_time(t_philo *p, int t_wait)
{
	long long	current_time;
	long long	variance;

	current_time = time_stamp(p->args);
	while (1)
	{
		variance = (time_stamp(p->args) - current_time);
		if (variance >= t_wait)
			break ;
		usleep(1000);
	}
}
