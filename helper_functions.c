/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zabdulza <zabdulza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 09:49:16 by zabdulza          #+#    #+#             */
/*   Updated: 2024/01/20 10:59:26 by zabdulza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// Convert a string to an integer.
// Handles signs, skips leading whitespace, and prevents integer overflow.
int	ft_atoi(const char *str)
{
	long	nbr;
	int		i;
	int		sign;

	i = 0;
	sign = 1;
	nbr = 0;
	while ((str[i] >= '\t' && str[i] <= '\r') || str[i] == ' ')
		i++;
	if (str[i] == '-')
		sign *= -1;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		nbr = (nbr * 10) + str[i] - '0';
		i++;
		if (nbr * sign > INT_MAX)
			return (-1);
		if (nbr * sign < INT_MIN)
			return (-1);
	}
	return (nbr * sign);
}

// Set a block of memory to zero.
// Useful for initializing memory to zero before use.
void	ft_bzero(void *str, size_t n)
{
	unsigned char	*temp;
	size_t			i;

	temp = (unsigned char *)str;
	i = 0;
	while (i < n)
	{
		temp[i] = 0;
		i++;
	}
	str = temp;
}

// Allocate and zero-initialize memory for an array.
// Provides a convenient way to allocate memory and ensure 
//it is initialized to zero.
void	*ft_calloc(size_t count, size_t n)
{
	void	*ptr;

	ptr = malloc(count * n);
	if (ptr == NULL)
		return (NULL);
	ft_bzero(ptr, (count * n));
	return (ptr);
}

// Print information about a philosopher's state with thread safety.
// Ensures that printing is thread-safe using a mutex and checks 
//if the game is over before printing.
void	print(t_philo *p, char *condition)
{
	if (p->args->game_over == FALSE)
	{
		pthread_mutex_lock(&p->args->cout);
		printf("%lld\t%d\t%s\n", time_stamp(p->args), p->id, condition);
		pthread_mutex_unlock(&p->args->cout);
	}
}
