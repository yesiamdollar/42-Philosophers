/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboutahr <aboutahr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 18:31:25 by aboutahr          #+#    #+#             */
/*   Updated: 2021/05/24 18:38:20 by aboutahr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	ft_exit(t_state *state)
{
	int	i;

	if (state->forks_m)
	{
		i = 0;
		while (i < state->n)
		{
			pthread_mutex_destroy(&state->forks_m[i]);
			i++;
		}
		free(state->forks_m);
	}
	if (state->philo)
	{
		i = 0;
		while (i < state->n)
		{
			pthread_mutex_destroy(&state->philo[i].mutex);
			pthread_mutex_destroy(&state->philo[i++].eat_m);
		}
		free(state->philo);
	}
	pthread_mutex_destroy(&state->write_m);
	pthread_mutex_destroy(&state->somebody_dead_m);
}