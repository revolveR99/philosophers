/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_setup.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zabdulza <zabdulza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 09:45:02 by zabdulza          #+#    #+#             */
/*   Updated: 2024/01/20 11:20:05 by zabdulza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// Purpose: Validates the command-line arguments and ensures they 
// meet specific criteria.
// Checks if the number of arguments is either 5 or 6.
// Validates that each argument (excluding the program name) is a positive 
// integer.
// Checks if the first argument (number of philosophers) is less than 201.
// Returns 0 if the arguments are valid; otherwise, prints an error message 
// and returns -1.
int	arg_validate(int ac, char **av)
{
	int	i;
	int	result;

	if (ac != 5 && ac != 6)
	{
		printf("%s", ERR_CMD);
		return (-1);
	}
	i = 0;
	while (av[++i])
	{
		result = ft_atoi(av[i]);
		if (i == 1 && result >= 201)
		{
			printf(ERR_MAX);
			return (-1);
		}
		if (result <= 0)
		{
			printf(ERR_ARGS);
			return (-1);
		}
	}
	return (0);
}

// Purpose: Initializes the control structure (`t_control`) with values parsed 
// from command-line arguments and sets up necessary resources.
// Parses the command-line arguments and assigns them to the corresponding 
// fields in the `t_control` structure.
// Initializes mutexes for console output (`cout`), the global checker, and 
// forks.
// Allocates memory for arrays of philosophers (`philo`) and forks (`fork`) 
// based on the number of philosophers.
// Initializes each fork with a mutex.
// Calls `philo_setup` to set up individual philosopher structures within the 
// control structure.
// Sets the start time of the simulation using the `start_clock` function.
void	controls_setup(char **av, t_control *input)
{
	int	i;

	i = -1;
	input->error = FALSE;
	input->game_over = FALSE;
	input->end_meal = 0;
	input->nb_philo = ft_atoi(av[1]);
	input->t_to_die = ft_atoi(av[2]);
	input->t_to_eat = ft_atoi(av[3]);
	input->t_to_sleep = ft_atoi(av[4]);
	if (av[5])
		input->max_meals = ft_atoi(av[5]);
	else
		input->max_meals = FALSE;
	input->philo = ft_calloc(input->nb_philo, (sizeof(t_philo)));
	input->fork = ft_calloc(input->nb_philo, (sizeof(pthread_mutex_t)));
	pthread_mutex_init(&input->cout, NULL);
	pthread_mutex_init(&input->checker, NULL);
	while (++i < input->nb_philo)
		pthread_mutex_init(&input->fork[i], NULL);
	philo_setup(input);
	input->t0 = start_clock();
}

// Purpose: Sets up individual philosopher structures within the 
//control structure.
// Assigns each philosopher a unique ID, initializes meal-related 
//variables, and sets the last meal timestamp to 0.
// Assigns left and right fork indices to each philosopher, ensuring
// proper indexing for circular allocation.
// Associates each philosopher with the overall control structure.
// Iterates through the philosophers and initializes their parameters.
void	philo_setup(t_control *input)
{
	int	i;

	i = 0;
	while (i < input->nb_philo)
	{
		input->philo[i].id = i + 1;
		input->philo[i].meals_eaten = 0;
		input->philo[i].t_lastmeal = 0;
		input->philo[i].l_fork = i;
		input->philo[i].r_fork = (i + 1) % input->nb_philo;
		input->philo[i].args = input;
		i++;
	}
}
