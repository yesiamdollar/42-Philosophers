/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboutahr <aboutahr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 18:31:25 by aboutahr          #+#    #+#             */
/*   Updated: 2021/05/25 16:17:32 by aboutahr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include <stdio.h>
void	ft_exit(t_state *state)
{
	int	i;

	if (state->forks_m)
	{
		sem_unlink(ForkSem);
		// ft_putnbr_fd(sem_unlink(ForkSem), 1);
	}
	if (state->philo)
	{
		i = 0;
		// while (i < state->n)
		// {
		// 	/* pthread_mutex_destroy(&state->philo[i].mutex);
		// 	pthread_mutex_destroy(&state->philo[i++].eat_m); */
		// 	sem_close(state->philo[i].mutex);
		// 	sem_close(state->philo[i].eat_m);	
		// 	i++;
		// }
		sem_unlink(PhiloSem);
		sem_unlink(EatSem);
		free(state->philo);
	}
	// sem_close(state->write_m);
	// sem_close(state->somebody_dead_m);
	// sem_unlink(WriteSem);
	sem_unlink(DeadSem);
}