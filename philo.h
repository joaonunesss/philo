/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarinho <jmarinho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 15:31:39 by jmarinho          #+#    #+#             */
/*   Updated: 2023/11/21 14:36:04 by jmarinho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

# define TRUE 1
# define FALSE 0

# define RED 	"\033[1;31m"
# define GREEN 	"\033[1;32m"
# define YELLOW 	"\033[1;33m"
# define BLUE 	"\033[1;34m"
# define PURPLE 	"\033[0;35m"
# define WHITE 	"\033[1;37m"
# define RESET 	"\033[0m"

# define ERR_PHILO "Error: There must be at least one philosopher\n"
# define ERR_TIME "Error: Time to die must be greater than 0\n"
# define ERR_EAT "Error: Time to eat must be greater than 0\n"
# define ERR_SLEEP "Error: Time to sleep must be greater than 0\n"
# define ERR_MUST_EAT "Error: Times must eat must be greater than 0\n"

typedef struct s_philo
{
	int					id;
	int					times_eaten;
	long long			last_meal;
	pthread_mutex_t		*fork_left;
	pthread_mutex_t		*fork_right;
	pthread_t			thread;
	struct s_project	*project;
}	t_philo;

typedef struct s_project
{
	int				nbr_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				times_must_eat;
	int				nbr_philo_full;
	int				should_end;
	long long		start_time;
	pthread_mutex_t	*mtx_fork;
	pthread_mutex_t	mtx_eating;
	pthread_mutex_t	mtx_surveillance;
	struct s_philo	*philo;
}	t_project;

void		check_args(int ac, char **av);
void		init_project(t_project *project, int ac, char **av);
void		init_mtxs(t_project *project);
void		init_philo(t_project *project);
void		init_thread(t_project *project);
void		*start_simulation(void *philo);
void		surveillance(t_project *d);
int			dead_or_full(t_philo *p);
int			should_simulation_end(t_philo *philo, int should_end);
void		print_status(t_philo *philo, char *str);
void		eat(t_philo *philo);
int			ft_atoi(char *str);
void		exit_error(char *str, t_project *project, int flag);
void		free_mtxs(t_project *project);
long long	get_current_time(void);
int			philo_grab_forks(t_philo *philo);
int			philo_is_eating(t_philo *philo);
int			philo_is_sleeping(t_philo *philo);
void		init_project_aux(t_project *project, int ac, char **av);

#endif
