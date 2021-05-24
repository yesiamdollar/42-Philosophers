/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboutahr <aboutahr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 18:09:40 by aboutahr          #+#    #+#             */
/*   Updated: 2021/05/24 18:09:41 by aboutahr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	init_mutexes(t_state *state)
{
	int	i;

	pthread_mutex_init(&state->write_m, NULL);
	pthread_mutex_init(&state->somebody_dead_m, NULL);
	pthread_mutex_lock(&state->somebody_dead_m);
	state->forks_m = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* state->n);
	if (!state->forks_m)
		return (1);
	i = 0;
	while (i < state->n)
		pthread_mutex_init(&state->forks_m[i++], NULL);
	return (0);
}
