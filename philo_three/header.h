/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboutahr <aboutahr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 18:09:30 by aboutahr          #+#    #+#             */
/*   Updated: 2021/05/28 14:12:06 by aboutahr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H

# define HEADER_H

# include <unistd.h>
# include <sys/time.h>
# include <stdlib.h>
# include <pthread.h>
# include <semaphore.h>
# include <signal.h>

# define EAT 	0
# define SLEEP 1
# define FORK 	2
# define THINK	3
# define DEAD 	4
# define DONE 	5

# define FORKSEM "forksem"
# define WRITESEM "writesem"
# define EATSEM "eatsem"
# define PHILOSEM "philosem"
# define DEADSEM "deadsem"
# define DEADWRITESEM "deadwritesem"

typedef struct s_philo
{
	int				id;
	int				is_eating;
	int				lfork;
	int				rfork;
	int				eat_count;
	int				limit;
	int				last_eat;

	pid_t			pid;

	sem_t			*mutex;
	sem_t			*eat_m;

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

	sem_t			*forks_m;
	sem_t			*write_m;
	sem_t			*dead_write_m;
	sem_t			*somebody_dead_m;

	struct s_philo	*philo;
}					t_state;

/* PRIMARY FUNCS */
int		ft_error(const char *s);
size_t	ft_strlen(const char *s);
int		ft_atoi(const char *str);
int		init_semaphores(t_state *state);
int		start_thread(t_state *state);
int		get_time(void);
void	ft_putnbr_fd(int n, int fd);
void	ft_exit(t_state *state);
sem_t	*ft_sem_open(char const *name, int value);

/* LIFE CYCLE */
void	eat(t_state *state, t_philo *philo);
void	take_forks(t_state *state, t_philo *philo);
void	drop_forks(t_state *state, t_philo *philo);
void	message(t_state *state, t_philo *philo, int type);
int		start_thread(t_state *state);

#endif