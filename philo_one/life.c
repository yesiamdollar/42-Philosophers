/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboutahr <aboutahr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 18:09:35 by aboutahr          #+#    #+#             */
/*   Updated: 2021/05/24 18:09:36 by aboutahr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	eat(t_state *state, t_philo *philo)
{
	pthread_mutex_lock(&philo->mutex);
	philo->is_eating = 1;
	philo->last_eat = get_time();
	philo->limit = philo->last_eat + state->time_to_die;
	message(state, philo, EAT);
	usleep(state->time_to_eat * 1000);
	philo->eat_count++;
	philo->is_eating = 0;
	pthread_mutex_unlock(&philo->mutex);
	pthread_mutex_unlock(&philo->eat_m);
}

void	take_forks(t_state *state, t_philo *philo)
{
	pthread_mutex_lock(&state->forks_m[philo->lfork]);
	message(state, philo, FORK);
	pthread_mutex_lock(&state->forks_m[philo->rfork]);
	message(state, philo, FORK);
}

void	drop_forks(t_state *state, t_philo *philo)
{
	message(state, philo, SLEEP);
	pthread_mutex_unlock(&state->forks_m[philo->lfork]);
	pthread_mutex_unlock(&state->forks_m[philo->rfork]);
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

	pthread_mutex_lock(&state->write_m);
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
	pthread_mutex_unlock(&state->write_m);
}
