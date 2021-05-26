/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semaphore.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboutahr <aboutahr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 18:09:40 by aboutahr          #+#    #+#             */
/*   Updated: 2021/05/26 20:57:48 by aboutahr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

sem_t	*ft_sem_open(char const *name, int value)
{
	sem_unlink(name);
	return (sem_open(name, O_CREAT | O_EXCL, 0644, value));
}

int	init_semaphores(t_state *state)
{
	state->forks_m = ft_sem_open(FORKSEM, state->n);
	state->write_m = ft_sem_open(WRITESEM, 1);
	state->somebody_dead_m = ft_sem_open(DEADSEM, 0);
	state->dead_write_m = ft_sem_open(DEADWRITESEM, 1);
	if (state->forks_m < 0 || state->write_m < 0
		|| state->somebody_dead_m < 0 || state->dead_write_m < 0)
		return (1);
	return (0);
}
