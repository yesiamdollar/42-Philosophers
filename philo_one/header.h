/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboutahr <aboutahr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 18:09:30 by aboutahr          #+#    #+#             */
/*   Updated: 2021/05/26 20:46:48 by aboutahr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H

# define HEADER_H

# include <unistd.h>
# include <sys/time.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>

# define EAT 	0
# define SLEEP 1
# define FORK 	2
# define THINK	3
# define DEAD 	4
# define DONE 	5

typedef struct s_philo
{
	int				id;
	int				is_eating;
	int				lfork;
	int				rfork;
	int				limit;
	int				last_eat;

	pthread_mutex_t	mutex;
	pthread_mutex_t	eat_m;

	struct s_state	*state;
}				t_philo;

typedef struct s_state{
	int				n;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat;
	int				loop;

	int				start;

	pthread_mutex_t	*forks_m;
	pthread_mutex_t	write_m;
	pthread_mutex_t	somebody_dead_m;

	struct s_philo	*philo;
}					t_state;

/* PRIMARY FUNCS */
int		ft_error(const char *s);
size_t	ft_strlen(const char *s);
int		ft_atoi(const char *str);
int		init_mutexes(t_state *state);
int		start_thread(t_state *state);
int		get_time(void);
void	ft_putnbr_fd(int n, int fd);
void	ft_exit(t_state *state);

/* LIFE CYCLE */
void	eat(t_state *state, t_philo *philo);
void	take_forks(t_state *state, t_philo *philo);
void	drop_forks(t_state *state, t_philo *philo);
void	message(t_state *state, t_philo *philo, int type);
int		start_thread(t_state *state);

#endif