/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_philosophers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarinho <jmarinho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 15:22:16 by jmarinho          #+#    #+#             */
/*   Updated: 2023/09/11 13:09:43 by jmarinho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int is_time_to_finish(t_philosophers *philosophers, int finish_order)
{
	pthread_mutex_lock(&philosophers->project->finish_mutex);
	if (finish_order == 1 || philosophers->project->finish_flag == 1)
	{
		if (finish_order)
			philosophers->project->finish_flag = 1;
		pthread_mutex_unlock(&philosophers->project->finish_mutex); //???
		return (1);
	}
	pthread_mutex_unlock(&philosophers->project->finish_mutex); // ???
	return (0);
}

void	print_action(t_philosophers *philosophers, char *status)
{
	long time;

	pthread_mutex_lock(&philosophers->project->print_mutex);
	if (!is_time_to_finish(philosophers, 0))
	{
		time = now() - philosophers->project->start_time;
		printf("%li %i %s\n", time, philosophers->id, status);
	}
	pthread_mutex_unlock(&philosophers->project->print_mutex);
	if (!status)
		printf("All philosophers ate enough!");
}

void	time_to_eat(t_philosophers *philosophers)
{
	if (philosophers->id % 2 == 0)
	{
		pthread_mutex_lock(&philosophers->project->fork_mutex[philosophers->l_fork]);
		pthread_mutex_lock(&philosophers->project->fork_mutex[philosophers->r_fork]);
	}
	else
	{
		pthread_mutex_lock(&philosophers->project->fork_mutex[philosophers->r_fork]);
		pthread_mutex_lock(&philosophers->project->fork_mutex[philosophers->l_fork]);
	}
	print_action(philosophers, "has taken a fork");
	print_action(philosophers, "has taken a fork");
	print_action(philosophers, "is eating");
	advance_time(philosophers, philosophers->project->time_to_eat);
	pthread_mutex_lock(&philosophers->project->eat_mutex);
	philosophers->eat_count++;
	philosophers->last_time_eat = now();
	pthread_mutex_unlock(&philosophers->project->eat_mutex);
	pthread_mutex_unlock(&philosophers->project->fork_mutex[philosophers->r_fork]);
	pthread_mutex_unlock(&philosophers->project->fork_mutex[philosophers->l_fork]);
}

int	lone_philosopher(t_project *project)
{
	print_action(&project->philo[0], "has taken a fork");
	advance_time(&project->philo[0], project->time_to_die);
	print_action(&project->philo[0], "died");
	is_time_to_finish(&project->philo[0], 1);
	return (0);
}

void *start_philosophers(void *ptr)
{
 	t_philosophers *philosophers;

	write(1,"flag0\n", 5);
	philosophers = (t_philosophers *)ptr;
	if (philosophers->id % 2 == 0)
		usleep(philosophers->project->time_to_eat * 1000);
	while (1)
	{
		if (philosophers->project->nbr_philos == 1)
		{
			lone_philosopher(philosophers->project);
			return (0);
		}
		if (is_time_to_finish(philosophers, 0))
			return (0);
		time_to_eat(philosophers);
		print_action(philosophers, "is sleeping");
		advance_time(philosophers, philosophers->project->time_to_sleep);
		print_action(philosophers, "is thinking");
		if (philosophers->project->nbr_philos % 2 != 0
			&& philosophers->project->nbr_philos <= 127)
			advance_time(philosophers, philosophers->project->time_to_eat);
	}	
	return (0);
}
/*
	1) start_philosophers function is the one being performed by the threads
		- first, we put the even philosophers to wait for their turn to eat
		- we then create a condition for when there is only one philosopher
		- we then check if we should end the simulation (one starved or all ate enough)
		- if not, we continue on with the philo tasks: eating, sleeping, thinking
		- lastly, we put the odd philosophers to wait for their turn to eat
	2) is_time_to_finish: used to check if the simulation should end
		- here we assign 1 to the end_flag if we want to end the simulation
		- we also return 1 if the simulation should end and 0 otherwise
	3) print_action: used to print the status of the philosopher
		- if we don't pass a string, it means that all philosophers have eaten
		  the number of times they should
	4) time_to_eat: this is the function where we simulate the philosopher eating
		- reminder: the philosopher can only eat if he has both forks

*/