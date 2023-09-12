/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ride-sou <ride-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 11:47:29 by ccosta-c          #+#    #+#             */
/*   Updated: 2023/07/03 12:11:53 by ride-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "library.h"

void	*simulation(void *philo)
{
	t_philos	*copy;

	copy = (t_philos *)philo;
	while (1)
	{
		if (copy->data->nbr_philos == 1)
		{
			pthread_mutex_lock(copy->l_fork);
			ft_print(philo, "took the fork.");
			pthread_mutex_unlock(copy->l_fork);
			return (NULL);
		}
		if (copy->id % 2 == 0)
			usleep(4000);
		if (grab_forks(copy) == -1)
			break ;
		if (ft_eat(copy) == -1)
			break ;
		if (ft_sleep(copy) == -1)
			break ;
		ft_print(copy, "is thinking.");
	}
	return (NULL);
}

int	ft_eat(t_philos *philo)
{
	pthread_mutex_lock(&philo->data->verify);
	if (philo->data->died == 1
		|| (philo->data->all_ate == philo->data->nbr_philos))
	{
		pthread_mutex_unlock(&philo->data->verify);
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
		return (-1);
	}
	pthread_mutex_unlock(&philo->data->verify);
	pthread_mutex_lock(&philo->alive);
	ft_print(philo, "is eating.");
	philo->last_meal = get_time();
	pthread_mutex_lock(&philo->data->verify);
	philo->times_eaten++;
	if (philo->data->times_to_eat != -1)
		if (philo->times_eaten == philo->data->times_to_eat)
			philo->data->all_ate++;
	pthread_mutex_unlock(&philo->data->verify);
	pthread_mutex_unlock(&philo->alive);
	usleep(philo->data->time_eat * 1000);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
	return (0);
}

int	ft_sleep(t_philos *philo)
{
	pthread_mutex_lock(&philo->data->verify);
	if (philo->data->died == 1
		|| philo->data->all_ate == philo->data->nbr_philos)
	{
		pthread_mutex_unlock(&philo->data->verify);
		return (-1);
	}
	pthread_mutex_unlock(&philo->data->verify);
	ft_print(philo, "is sleeping.");
	usleep(philo->data->time_sleep * 1000);
	return (0);
}

int	grab_forks(t_philos *philo)
{
	pthread_mutex_lock(&philo->data->verify);
	if (philo->data->died == 1
		|| philo->data->all_ate == philo->data->nbr_philos)
	{
		pthread_mutex_unlock(&philo->data->verify);
		return (-1);
	}
	pthread_mutex_unlock(&philo->data->verify);
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->r_fork);
		ft_print(philo, "took the fork.");
		pthread_mutex_lock(philo->l_fork);
		ft_print(philo, "took the fork.");
	}
	else
	{
		pthread_mutex_lock(philo->l_fork);
		ft_print(philo, "took the fork.");
		pthread_mutex_lock(philo->r_fork);
		ft_print(philo, "took the fork.");
	}
	return (0);
}
