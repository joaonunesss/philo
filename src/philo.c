/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarinho <jmarinho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 12:44:37 by jmarinho          #+#    #+#             */
/*   Updated: 2023/09/11 13:22:03 by jmarinho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void    create_threads(t_project *project)
{
    int i;

    i = 1;
    while(i <= project->nbr_philos)
    {
        if(pthread_create(&project->philo[i].thread, NULL, start_philosophers, &project->philo[i]))
            exit_error("Couldn't create thread", , project);
        i++;
    }
}

void philos_init(t_project *project)
{
    int i;

    i = 1;
    while(i <= project->nbr_philos)
    {
        project->philo[i].id = i;
        project->philo[i].r_fork = i;
        if (i != project->nbr_philos)
            project->philo[i].l_fork = i + 1;
        else
            project->philo[i].l_fork = 1;
        project->philo[i].eat_count = 0;
        project->philo[i].last_time_eat = project->start_time;
        i++;
    }
}

void mutex_init(t_project *project)
{
    int i;

    i = 1;
    project->fork_mutex = malloc(sizeof(pthread_mutex_t) * project->nbr_philos);
    if(!project->fork_mutex)
        exit_error("Couldn't create the forks mutex\n", 2, project);
    while(i <= project->nbr_philos)
    {
        if(pthread_mutex_init(&project->fork_mutex[i++], NULL))
            exit_error("Couldn't init forks mutex\n", 2, project);
    }
    if (pthread_mutex_init(&project->print_mutex, NULL))
		exit_error("Couldn't init print mutex", 2, project);
	if (pthread_mutex_init(&project->eat_mutex, NULL))
		exit_error("Couldn't init eat mutex", 2, project);
	if (pthread_mutex_init(&project->finish_mutex, NULL))
		exit_error("Couldn't init finish mutex", 2, project);
}

void    project_init(t_project  *project, char *av[], int ac)
{
    project->nbr_philos = ft_atoi(av[1]);
    project->time_to_die = ft_atoi(av[2]);
    project->time_to_eat = ft_atoi(av[3]);
    project->time_to_sleep = ft_atoi(av[4]);
    if(ac == 6)
        project->times_must_eat = ft_atoi(av[5]);
    else
        project->times_must_eat = -1;
    if (project->nbr_philos < 1 || project->time_to_die < 1
		|| project->time_to_eat < 1 || project->time_to_sleep < -1
		    || (ac == 6 && project->times_must_eat == -1))
		exit_error("Invalid arguments\n", 0, NULL);
    project->philo = malloc(sizeof(t_philosophers) * project->nbr_philos);
    if(!project->philo)
        exit_error("Couldn't create the philosophers\n", 2, project);
    project->start_time = now();
    project->finish_flag = 0;
    project->is_full = 0;
}

int main(int ac, char *av[])
{
    t_project project;

    if(ac != 5 && ac != 6)
        exit_error("Invalid number of arguments\n", 0, NULL);
    project_init(&project, av, ac);
    mutex_init(&project);
    philos_init(&project);
    create_threads(&project);
    write(1,"okei\n", 4);
    philo_monitoring(&project);
}

/*
	main is the function that starts the program
	1) we check if the arguments are correct
		- there must be 4 or 5 arguments
	2) 	project_init is the function that initializes the struct t_project
	    - ft_atoi returns -1 if arguments are not numbers
        - if an error occurs it free project struct and exits
    3) mutex_init is the function that initializes mutexes in the struct t_project
        - if an error occurs it frees project struct and mutex struct and exits
	4) philo_init is the function that initializes the struct t_philosophers
        - if an error occurs it frees project struct and mutex struct and exits
    5) create_threads creats a thread for each philosopher
        - we create a thread for each philosopher with pthread_create
		- start_philosophers is the function that each thread will execute
		- for each thread, we check if any philosopher starved or all ate enough

*/