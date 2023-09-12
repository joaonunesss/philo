/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarinho <jmarinho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 12:44:29 by jmarinho          #+#    #+#             */
/*   Updated: 2023/09/06 17:23:19 by jmarinho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef  PHILO_H
# define PHILO_H

#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/time.h>
#include<pthread.h>

typedef struct s_philosophers
{
    int id;
    int l_fork;
    int r_fork;
    int eat_count;
    int last_time_eat;
    struct s_project *project;
    pthread_t thread;
}   t_philosophers;

typedef struct s_project
{
    int nbr_philos;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int times_must_eat;
    t_philosophers *philo;
    long start_time;
    int finish_flag;
    int is_full;
    pthread_mutex_t *fork_mutex;
    pthread_mutex_t print_mutex;
    pthread_mutex_t eat_mutex;
    pthread_mutex_t finish_mutex;
}   t_project;

void *start_philosophers(void *ptr);
void exit_error(char *msg, int clear, t_project *project);
long now(void);
int ft_atoi(char *str);
void	philo_monitoring(t_project *project);
void	finish_dinner(t_project *project);
void	destroy_padlocks(t_project *project);
int is_time_to_finish(t_philosophers *philosophers, int finish_order);
void	print_action(t_philosophers *philosophers, char *status);
void	advance_time(t_philosophers *philosophers, long stop);
int	is_someone_dead_or_full(t_philosophers *philosophers);

#endif