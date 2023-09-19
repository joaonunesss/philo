/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarinho <jmarinho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 15:31:39 by jmarinho          #+#    #+#             */
/*   Updated: 2023/09/19 15:40:01 by jmarinho         ###   ########.fr       */
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

typedef struct s_philo
{
	int				id;
	int				fork_left;
	int				fork_right;
	int				times_eaten;
	long long		last_eaten;
	struct s_project	*data;
	pthread_t		thread;

}	t_philo;

typedef struct s_project
{
	int				n_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				times_must_eat;
	int				n_philo_full;
	int				end_flag;
	long long		start_time;
	t_philo			*philo;
	pthread_mutex_t	*mtx_fork;
	pthread_mutex_t	mtx_print;
	pthread_mutex_t	mtx_eat;
	pthread_mutex_t	mtx_end;
}	t_project;

void		check_args(int ac, char **av);
void		initialize_project(t_project *project, int ac, char **av);
void		initialize_mtxs(t_project *project);
void		initialize_philo(t_project *project);
void		initialize_thread(t_project *project);
void		*start_simulation(void *philo);
void		surveillance(t_project *d);
int			dead_or_full(t_project *d, t_philo *p);
int			should_simulation_end(t_philo *philo, int should_end);
void		print_status(t_philo *philo, char *str);
void		eat(t_philo *philo);
int			ft_atoi(const char *str);
void		exit_error(char *str, t_project *project, int flag);
void		free_mtxs(t_project *project);
long long	get_current_time(void);

#endif
