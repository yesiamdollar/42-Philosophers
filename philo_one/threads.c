/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboutahr <aboutahr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 18:09:43 by aboutahr          #+#    #+#             */
/*   Updated: 2021/05/26 20:46:09 by aboutahr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static void	*shenigami(void *philo_v)
{
	t_philo	*philo;

	philo = (t_philo *)philo_v;
	while (philo->state->loop)
	{
		pthread_mutex_lock(&philo->mutex);
		if (!philo->is_eating && get_time() > philo->limit)
		{
			message(philo->state, philo, DEAD);
			pthread_mutex_unlock(&philo->mutex);
			pthread_mutex_unlock(&philo->state->somebody_dead_m);
			return (NULL);
		}
		pthread_mutex_unlock(&philo->mutex);
		usleep(100);
	}
	return (NULL);
}

static void	*xcounter(void *state_v)
{
	t_state	*state;
	int		i;
	int		total;

	state = (t_state *)state_v;
	total = 0;
	while (total < state->must_eat)
	{
		i = 0;
		while (i < state->n)
			pthread_mutex_lock(&state->philo[i++].eat_m);
		total++;
	}
	message(state, &state->philo[0], DONE);
	pthread_mutex_unlock(&state->somebody_dead_m);
	return ((void *)0);
}

static void	*cycle(void *philo_v)
{
	t_philo		*philo;
	pthread_t	tid;
	t_state		*state;

	philo = (t_philo *)philo_v;
	state = philo->state;
	philo->last_eat = get_time();
	philo->limit = philo->last_eat + philo->state->time_to_die;
	if (pthread_create(&tid, NULL, &shenigami, philo_v))
		return (NULL);
	while (state->loop)
	{
		message(state, philo, THINK);
		take_forks(state, philo);
		eat(state, philo);
		drop_forks(state, philo);
	}
	return ((void *)0);
}

int	start_thread(t_state *state)
{
	int			i;
	pthread_t	tid;
	void		*philo;

	state->start = get_time();
	if (state->must_eat != -1)
	{
		if (pthread_create(&tid, NULL, &xcounter, (void *)state))
			return (1);
	}
	i = 0;
	while (i < state->n)
	{
		philo = (void *)(&state->philo[i]);
		if (pthread_create(&tid, NULL, &cycle, philo))
			return (1);
		usleep(100);
		i++;
	}
	return (0);
}
