/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarinho <jmarinho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 12:34:19 by jmarinho          #+#    #+#             */
/*   Updated: 2023/09/06 17:35:34 by jmarinho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	advance_time(t_philosophers *philosophers, long stop)
{
	long	begin;

	begin = now();
	while (!is_time_to_finish(philosophers, 0) && (now() - begin) < stop)
		usleep(100);
}

long    now(void)
{
	struct timeval	timeval;

	gettimeofday(&timeval, NULL);
	return ((timeval.tv_sec * 1000) + (timeval.tv_usec / 1000));
}

void exit_error(char *msg, int clear, t_project *project)
{
    printf("%s", msg);
    if(clear == 1)
        free(project);
    else if(clear == 2)
    {
        free(project->philo);
        free(project->fork_mutex);
    }
    exit(EXIT_FAILURE);
}

int ft_atoi(char *str)
{
    int i;
    int nbr;
    int signal;

    i = 0;
    nbr = 0;
    signal = 1;
    if(str[0] == '-')
    {
        signal = -1;
        i = 1;
    }
    while(str[i])
    {
        if(str[i] >= '0' && str[i] <= '9')
        {
            nbr = nbr * 10 + str[i] - 48;
        }
        else
            return(-1);
        i++;
    }
    return(nbr * signal);   
}

void  destroy_mutexes(t_project *project)
{
    int	i;

	i = 1;
	while (i < project->nbr_philos)
		pthread_mutex_destroy(&project->fork_mutex[i++]);
	free(project);//diferente
	pthread_mutex_destroy(&project->print_mutex);
	pthread_mutex_destroy(&project->eat_mutex);
	pthread_mutex_destroy(&project->finish_mutex);
}
