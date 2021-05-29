/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboutahr <aboutahr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 18:09:38 by aboutahr          #+#    #+#             */
/*   Updated: 2021/05/28 18:01:36 by aboutahr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static int	all_is_int(int argc, const char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (i < argc)
	{
		j = 0;
		if (ft_strlen(argv[i]) > 10)
			return (1);
		while (argv[i][j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

static int	arg_checker(int argc, const char **argv)
{
	if (argc < 5 || argc > 6)
		return (1);
	else if (all_is_int(argc, argv))
		return (1);
	if (ft_atoi(argv[1]) > 200)
		return (1);
	return (0);
}

static t_philo	*philo_init(t_state *state)
{
	int		i;
	t_philo	*philo;

	philo = malloc(sizeof(t_philo) * state->n);
	if (!philo)
		return (NULL);
	i = 0;
	while (i < state->n)
	{
		philo[i].id = i;
		philo[i].is_eating = 0;
		philo[i].rfork = (i + 1) % state->n;
		philo[i].lfork = i;
		philo[i].eat_count = 0;
		philo[i].state = state;
		philo[i].mutex = ft_sem_open(PHILOSEM, 1);
		philo[i].eat_m = ft_sem_open(EATSEM, 0);
		if (philo[i].mutex < 0 || philo[i].eat_m < 0)
			return (NULL);
		i++;
	}
	return (philo);
}

static int	parser(int argc, const char **argv, t_state *state)
{
	state->n = ft_atoi(argv[1]);
	state->time_to_die = ft_atoi(argv[2]);
	state->time_to_eat = ft_atoi(argv[3]);
	state->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		state->must_eat = ft_atoi(argv[5]);
	else
		state->must_eat = -1;
	state->loop = 1;
	state->philo = philo_init(state);
	if (!state->philo)
		return (1);
	if (init_semaphores(state))
		return (1);
	return (0);
}

int	main(int argc, const char **argv)
{
	t_state	state;
	int		i;

	if (arg_checker(argc, argv))
	{
		return (ft_error("ERROR:: bad arguments!!\n"));
	}
	state.philo = NULL;
	if (parser(argc, argv, &state))
	{
		return (ft_error("ERROR:: bad arguments!!\n"));
	}
	if (start_thread(&state))
	{
		return (ft_error("error :: cannot start thread\n"));
	}
	sem_wait(state.somebody_dead_m);
	sem_post(state.write_m);
	i = 0;
	while (i < state.n)
		kill(state.philo[i++].pid, SIGKILL);
	ft_exit(&state);
	return (0);
}
