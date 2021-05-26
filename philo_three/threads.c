/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboutahr <aboutahr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 18:09:43 by aboutahr          #+#    #+#             */
/*   Updated: 2021/05/26 20:55:42 by aboutahr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static void	*supervisor(void *philo_v)
{
	t_philo	*philo;

	philo = (t_philo *)philo_v;
	while (philo->state->loop)
	{
		sem_wait(philo->mutex);
		if (!philo->is_eating && get_time() > philo->limit)
		{
			message(philo->state, philo, DEAD);
			sem_post(philo->mutex);
			sem_post(philo->state->somebody_dead_m);
			return (NULL);
		}
		sem_post(philo->mutex);
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
			sem_wait(state->philo[i++].eat_m);
		total++;
	}
	message(state, &state->philo[0], DONE);
	sem_post(state->somebody_dead_m);
	return ((void *)0);
}

static void	*cycle(void *philo_v)
{
	t_philo		*philo;
	pthread_t	tid;

	philo = (t_philo *)philo_v;
	philo->last_eat = get_time();
	philo->limit = philo->last_eat + philo->state->time_to_die;
	if (pthread_create(&tid, NULL, &supervisor, philo_v) != 0)
		return (NULL);
	while (philo->state->loop)
	{
		message(philo->state, philo, THINK);
		take_forks(philo->state, philo);
		eat(philo->state, philo);
		drop_forks(philo->state, philo);
	}
	return ((void *)0);
}

int	start_thread(t_state *state)
{
	pthread_t	tid;
	t_philo		*philo;
	int			i;

	state->start = get_time();
	if (state->must_eat != -1)
		if (pthread_create(&tid, NULL, &xcounter, (void *)state))
			return (1);
	i = 0;
	while (i < state->n)
	{
		philo = (&state->philo[i]);
		philo->pid = fork();
		if (philo->pid == 0)
		{
			cycle(philo);
			exit(0);
		}
		else if (philo->pid < 0)
			return (1);
		usleep(100);
		i++;
	}
	return (0);
}
