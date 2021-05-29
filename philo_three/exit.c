/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboutahr <aboutahr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 18:31:25 by aboutahr          #+#    #+#             */
/*   Updated: 2021/05/28 18:01:57 by aboutahr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include <stdio.h>

static void	ft_sem_close(char const *name, sem_t *sem)
{
	sem_close(sem);
	sem_unlink(name);
}

void	ft_exit(t_state *state)
{
	int	i;

	if (state->forks_m)
		ft_sem_close(FORKSEM, state->forks_m);
	if (state->philo)
	{
		i = 0;
		while (i < state->n)
		{
			sem_close(state->philo[i].eat_m);
			sem_close(state->philo[i++].mutex);
		}
		sem_unlink(PHILOSEM);
		sem_unlink(EATSEM);
		free(state->philo);
	}
	if (state->write_m)
		ft_sem_close(WRITESEM, state->write_m);
	if (state->dead_write_m)
		ft_sem_close(DEADWRITESEM, state->dead_write_m);
	if (state->somebody_dead_m)
		ft_sem_close(DEADSEM, state->somebody_dead_m);
}
