/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboutahr <aboutahr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 18:09:35 by aboutahr          #+#    #+#             */
/*   Updated: 2021/05/26 20:54:05 by aboutahr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	eat(t_state *state, t_philo *philo)
{
	sem_wait(philo->mutex);
	philo->is_eating = 1;
	philo->last_eat = get_time();
	philo->limit = philo->last_eat + state->time_to_die;
	message(state, philo, EAT);
	usleep(state->time_to_eat * 1000);
	philo->eat_count++;
	philo->is_eating = 0;
	sem_post(philo->mutex);
	sem_post(philo->eat_m);
}

void	take_forks(t_state *state, t_philo *philo)
{
	sem_wait(state->forks_m);
	message(state, philo, FORK);
	sem_wait(state->forks_m);
	message(state, philo, FORK);
}

void	drop_forks(t_state *state, t_philo *philo)
{
	message(state, philo, SLEEP);
	sem_post(state->forks_m);
	sem_post(state->forks_m);
	usleep(state->time_to_sleep * 1000);
}

static char	*get_message(int type)
{
	if (type == EAT)
		return (" is eating\n");
	else if (type == SLEEP)
		return (" is sleeping\n");
	else if (type == FORK)
		return (" has taken a fork\n");
	else if (type == THINK)
		return (" is thinking\n");
	else if (type == DONE)
		return ("must eat count reached\n");
	return (" died\n");
}

void	message(t_state *state, t_philo *philo, int type)
{
	static int	done = 0;

	sem_wait(state->write_m);
	sem_wait(state->dead_write_m);
	if (!done)
	{
		ft_putnbr_fd(get_time() - state->start, 1);
		write(1, "\t", 1);
		if (type != DONE)
			ft_putnbr_fd(philo->id + 1, 1);
		if (type >= DEAD)
			done = 1;
		write(1, get_message(type), ft_strlen(get_message(type)));
	}
	if (type < DEAD)
		sem_post(state->dead_write_m);
	sem_post(state->write_m);
}
