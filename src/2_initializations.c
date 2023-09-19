/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_initializations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarinho <jmarinho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 15:31:48 by jmarinho          #+#    #+#             */
/*   Updated: 2023/09/19 15:48:19 by jmarinho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

/*
	here the struct variables are being initialized and the threads being created
	1) we initialize the project struct and check if the arguments are correct
	2) we initialize the mutexes that are in the project struct
	3) we initialize the philo struct
	4) we create the threads that make the program work
		- we create a thread for each philosopher with pthread_create
		- start_simulation is the function that each thread will execute
		- for each thread, we check if any philosopher starved or all ate enough
	5) the start_simulation function is the one being performed by the threads
		- first, we put the even philosophers to wait for their turn to eat
		- we then create a condition for when there is only one philosopher
		- we then check if we should end the simulation (one starved or all ate enough)
		- if not, we continue on with the philo tasks: eating, sleeping, thinking
		- lastly, we put the odd philosophers to wait for their turn to eat
*/

void	*start_simulation(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	if (philo->id % 2 == 0)
		usleep(philo->data->time_to_eat * 1000);
	while (1)
	{
		if (philo->data->n_philo == 1)
		{
			print_status(philo, "has taken a fork");
			usleep(philo->data->time_to_die * 1000);
			print_status(philo, "died");
			should_simulation_end(philo, TRUE);
		}
		if (should_simulation_end(philo, FALSE) == TRUE)
			return (NULL);
		eat(philo);
		print_status(philo, "is sleeping");
		usleep(philo->data->time_to_sleep * 1000);
		print_status(philo, "is thinking");
		if (philo->data->n_philo % 2 != 0)
			usleep(philo->data->time_to_eat * 1000);
	}
	return (NULL);
}

void	initialize_thread(t_project *project)
{
	int	i;

	i = -1;
	while (++i < project->n_philo)
	{
		if (pthread_create(&project->philo[i].thread, NULL,
				start_simulation, &project->philo[i]) != 0)
			exit_error("Error: Creation of the thread failed\n", project, 3);
	}
	surveillance(project);
	i = -1;
	while (++i < project->n_philo)
	{
		if (pthread_join(project->philo[i].thread, NULL) != 0)
			exit_error("Error: Joining of the thread failed\n", project, 3);
	}
}

void	initialize_mtxs(t_project *project)
{
	int	i;

	i = -1;
	project->mtx_fork = malloc(sizeof(pthread_mutex_t) * project->n_philo);
	if (!project->mtx_fork)
		exit_error("Error: Creation of the FORK MALLOC failed\n", project, 2);
	while (++i < project->n_philo)
	{
		if (pthread_mutex_init(&project->mtx_fork[i], NULL) != 0)
			exit_error("Error: Creation of the FORK MUTEX failed\n", project, 2);
	}
	if (pthread_mutex_init(&project->mtx_print, NULL))
		exit_error("Error: Creation of the PRINT MUTEX failed\n", project, 2);
	if (pthread_mutex_init(&project->mtx_eat, NULL))
		exit_error("Error: Creation of the EAT MUTEX failed\n", project, 2);
	if (pthread_mutex_init(&project->mtx_end, NULL))
		exit_error("Error: Creation of the END MUTEX failed\n", project, 2);
}

void	initialize_philo(t_project *project)
{
	int	i;

	i = 0;
	while (i < project->n_philo)
	{
		project->philo[i].id = i + 1;
		project->philo[i].fork_left = i;
		project->philo[i].fork_right = (i + 1) % project->n_philo;
		
		//VER PORQUE CRASHA COM ESTE IF\ELSE
		// if ((i + 1) != project->n_philo)
        //     project->philo[i].fork_right = i + 1;
        // else
        //     project->philo[i].fork_right = 1;
		
		project->philo[i].times_eaten = 0;
		project->philo[i].last_eaten = project->start_time;
		project->philo[i].data = project;
		i++;
	}
}

void	initialize_project(t_project *d, int ac, char **av)
{
	d->n_philo = ft_atoi(av[1]);
	d->time_to_die = ft_atoi(av[2]);
	d->time_to_eat = ft_atoi(av[3]);
	d->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		d->times_must_eat = ft_atoi(av[5]);
	else
		d->times_must_eat = 0;
	d->n_philo_full = 0;
	d->end_flag = 0;
	d->start_time = get_current_time();
	d->philo = malloc(sizeof(t_philo) * d->n_philo);
	if (!d->philo)
		exit_error("Error: Creation of the PHILO MALLOC failed\n", d, 1);
	if (d->n_philo < 1)
		exit_error("Error: There must be at least one philosopher\n", d, 1);
	if (d->time_to_die < 1 || d->time_to_eat < 1 || d->time_to_sleep < 1)
		exit_error("Error: Time arguments must be greater than 0\n", d, 1);
	if (ac == 6 && d->times_must_eat < 1)
		exit_error("Error: If it exists, the last arg must be > 0\n", d, 1);
}
