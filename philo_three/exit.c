/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboutahr <aboutahr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 18:31:25 by aboutahr          #+#    #+#             */
/*   Updated: 2021/05/26 20:57:01 by aboutahr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include <stdio.h>
void	ft_exit(t_state *state)
{
	if (state->forks_m)
	{
		sem_unlink(FORKSEM);
	}
	if (state->philo)
	{
		sem_unlink(PHILOSEM);
		sem_unlink(EATSEM);
		free(state->philo);
	}
	sem_unlink(DEADSEM);
}
